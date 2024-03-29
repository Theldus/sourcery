/*
 * MIT License
 *
 * Copyright (c) 2020 Davidson Francis <davidsondfgl@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "srcry.h"
#include "dict.h"

#ifndef NOT_PTHREADS
#include <pthread.h>
#endif

#define OPTPARSE_IMPLEMENTATION
#define OPTPARSE_API static
#include "optparse.h"

/* States. */
#define HL_DEFAULT         0
#define HL_IDENTIFIER      1
#define HL_NUMBER          3
#define HL_CHAR            4
#define HL_STRING          5
#define HL_COMMENT_SINGLE  6
#define HL_COMMENT_MULTI   7
#define HL_PREPROCESSOR    8

/* Command line flags. */
#define CMD_ENABLE_SL 1 /* Enable single-line. */
#define CMD_ENABLE_ML 2 /* Enable multi-line.  */
#define CMD_ENABLE_ST 4 /* Enable strings.     */
#define CMD_ENABLE_ID 8 /* Enable identifiers. */
#define CMD_DISABLE  16 /* Disable checking.   */

/* Spell types. */
#define SPELL_STR   0 /* String spell.              */
#define SPELL_IDENT 1 /* Identifier spell.          */
#define SPELL_SLINE 2 /* Single-line comment spell. */
#define SPELL_MLINE 3 /* Multi-line comment spell.  */

/* Types. */
const char * const misspell_types[] = {
	"string", "identifier", "single-line comment",
	"multi-line comment"
};

/*
 * Is identifier character lookup table
 *
 * This is simple and faster than using isalnum(c) || c == '_',
 * so I'll use this instead.
 */
static const int is_ident[256] = {
	['0'] = 1, ['1'] = 1, ['2'] = 1, ['3'] = 1, ['4'] = 1, ['5'] = 1,
	['6'] = 1, ['7'] = 1, ['8'] = 1, ['9'] = 1, ['A'] = 1, ['B'] = 1,
	['C'] = 1, ['D'] = 1, ['E'] = 1, ['F'] = 1, ['G'] = 1, ['H'] = 1,
	['I'] = 1, ['J'] = 1, ['K'] = 1, ['L'] = 1, ['M'] = 1, ['N'] = 1,
	['O'] = 1, ['P'] = 1, ['Q'] = 1, ['R'] = 1, ['S'] = 1, ['T'] = 1,
	['U'] = 1, ['V'] = 1, ['X'] = 1, ['W'] = 1, ['Y'] = 1, ['Z'] = 1,
	['_'] = 1, ['a'] = 1, ['b'] = 1, ['c'] = 1, ['d'] = 1, ['e'] = 1,
	['f'] = 1, ['g'] = 1, ['h'] = 1, ['i'] = 1, ['j'] = 1, ['k'] = 1,
	['l'] = 1, ['m'] = 1, ['n'] = 1, ['o'] = 1, ['p'] = 1, ['q'] = 1,
	['r'] = 1, ['s'] = 1, ['t'] = 1, ['u'] = 1, ['v'] = 1, ['x'] = 1,
	['w'] = 1, ['y'] = 1, ['z'] = 1,
};

/*
 * My isdigit()... maybe someone could argue that I should rely
 * on libc instead of doing it myself, but... this is fast...
 * and I swear that I will only pass chars as indexes here =).
 */
static const int is_digit[256] = {
	['0'] = 1, ['1'] = 1, ['2'] = 1, ['3'] = 1, ['4'] = 1, ['5'] = 1,
	['6'] = 1, ['7'] = 1, ['8'] = 1, ['9'] = 1
};

/* Current flags. */
static int cmd_flags;
static struct optparse options;

/* Mutexes. */
#ifndef NOT_PTHREADS
static pthread_mutex_t queue_mutex  = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t stdout_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t file_avail    = PTHREAD_COND_INITIALIZER;
static pthread_t workers[NUM_WORKERS];
static int done;
static int nworkers;

/* File queue. */
struct file_queue
{
	char *path;
	struct file_queue *next;
};

/* File queue. */
struct file_queue *file_queue;
#endif

/**
 * @brief Add a single word misspelling into the output
 * buffer/stream @p stream.
 *
 * @param stream Output stream.
 * @param file Analyzed file.
 * @param type Misspelling type (string, comment...).
 * @param lineno Line number.
 * @param linecol Line column.
 * @param length Word length.
 * @param word Word pointer.
 *
 * @return Returns 0 if success and -1 otherwise.
 */
static inline int add_misspelling(FILE *stream, const char *file,
	unsigned type,
	unsigned lineno,
	unsigned linecol,
	unsigned length,
	char *word)
{
	return (fprintf(stream, "%s:%d:%d: %s (%.*s) may be wrong\n",
		file, lineno, linecol, misspell_types[type], length, word));
}

/**
 * @brief Dump the contents of @p buf in the stdout, i.e:
 * all the misspellings, already nicely formatted.
 *
 * @param buf Spellings buffer.
 * @param len Buffer size (in bytes).
 */
static void dump_misspellings(const char *buf, size_t len)
{
	size_t  twb; /* Total written bytes. */
	ssize_t  wb; /* Written bytes.       */
	int fd;      /* File number.         */

	twb = 0;
	wb  = 0;
	fd  = fileno(stdout);

	while (twb < len)
	{
		wb = write(fd, (buf + twb), (len - twb));
		if (wb == -1)
			break;
		twb += wb;
	}
}

/**
 * @brief Advances the buffer pointer until find
 * a next line. If none is found, sets buf to
 * the end of the buf.
 *
 * @param buf Buffer pointer to be advanced.
 * @param end End of the buffer pointer.
 */
static inline void skip_line(char **buf, char *end)
{
	char *t = strchr(*buf, '\n');
	if (t == NULL)
		t = end;
	*buf = t;
}

/**
 * @brief Searches for misspellings given a string that spans
 * through multiples lines.
 *
 * @param d Dictionary saved data.
 * @param stream Output stream.
 * @param file Analyzed file.
 * @param mslist Misspellings list.
 * @param lineno Line that starts the string.
 * @param colno Column that starts the string.
 * @param start Start position of the buffer (inclusive).
 * @param end End position of the buffer (inclusive).
 *
 * @return Returns 0 if success, a negative number otherwise.
 */
static int handle_multiline(struct dict_data *d,
	FILE *stream,
	const char *file,
	unsigned lineno,
	unsigned linecol,
	char *start,
	char *end)
{
	unsigned rem_bytes;
	unsigned w_size;
	unsigned l_size;
	unsigned s_col;
	unsigned off;
	char *l_end;
	unsigned l_count;

	l_count   = lineno;
	rem_bytes = (unsigned)LENGTH_PTR(end, start);
	s_col     = linecol + 1;

	/* Check for misspellings line by line. */
	do
	{
		l_end = memchr(start, '\n', rem_bytes);
		if (!l_end)
			l_end = end;

		l_size = (unsigned)LENGTH_PTR(l_end, start);

		/* Initialize the checker. */
		dict_check_line(d, start, l_size);

		while (dict_next_misspelling(d, &w_size, &off))
			add_misspelling(stream, file, SPELL_MLINE, l_count, s_col + off,
				w_size, start + off);

		rem_bytes -= l_size;
		start      = l_end+1;
		s_col      = 1;
		l_count++;

	} while (start < end);

	return (0);
}

/**
 * @brief Searches for misspellings on a identifier.
 *
 * This function first tries to match the complete identifier,
 * if fail, breaks into works and checks them individually.
 *
 * @param d Dictionary saved data.
 * @param stream Output stream.
 * @param file Analyzed file.
 * @param type Line type: comment, string or identifier.
 * @param lineno Line that starts the string.
 * @param linecol Column that starts the string.
 * @param start Start position of the buffer (inclusive).
 * @param end End position of the buffer (inclusive).
 *
 * @return Returns 0 if success, a negative number otherwise.
 */
static int handle_identifier(struct dict_data *d,
	FILE *stream,
	const char *file,
	unsigned lineno,
	unsigned linecol,
	char *start,
	char *end)
{
	unsigned w_size;
	unsigned l_size;
	unsigned off;

	l_size = (unsigned)LENGTH_PTR(end, start);

	/*
	 * In reverse mode, we always want to break the identifier,
	 * so we skip the 'if statement' if reverse mode enabled.
	 */

#ifndef CHECK_REVERSE
	/* Check entire word. */
	if (!dict_check_word(start, l_size))
#endif
	{
		/* Initialize the checker. */
		dict_check_line(d, start, l_size);

		/* Check for misspellings. */
		while (dict_next_misspelling(d, &w_size, &off))
			add_misspelling(stream, file, SPELL_IDENT, lineno, linecol + off,
				w_size, start + off);
	}

	return (0);
}

/**
 * @brief Searches for misspellings on a single line.
 *
 * @param d Dictionary saved data.
 * @param stream Output stream.
 * @param file Analyzed file.
 * @param type Line type: comment, string or identifier.
 * @param lineno Line that starts the string.
 * @param linecol Column that starts the string.
 * @param start Start position of the buffer (inclusive).
 * @param end End position of the buffer (inclusive).
 *
 * @return Returns 0 if success, a negative number otherwise.
 */
static int handle_line(struct dict_data *d,
	FILE *stream,
	const char *file,
	unsigned type,
	unsigned lineno,
	unsigned linecol,
	char *start,
	char *end)
{
	unsigned w_size;
	unsigned l_size;
	unsigned off;

	l_size = (unsigned)LENGTH_PTR(end, start);

	/* Initialize the checker. */
	dict_check_line(d, start, l_size);

	/* Check for misspellings. */
	while (dict_next_misspelling(d, &w_size, &off))
		add_misspelling(stream, file, type, lineno, linecol + off, w_size,
			start + off);

	return (0);
}

/**
 * @brief Spell check a single file.
 *
 * @param file File to be analyzed.
 *
 * @note Note that this function is not thread-safe.
 *
 * @return Returns 0 if success, -1 if error.
 */
static int spell_file(const char *file)
{
	unsigned saved_lineno;  /* Line number from last operation.   */
	unsigned saved_colno;   /* Column number from last operation. */
	char *keyword_start;    /* Keyword start pointer.             */
	struct dict_data d;     /* Dictionary data.                   */
	unsigned curr_line;     /* Current line.                      */
	unsigned curr_coll;     /* Current column.                    */
	size_t stream_len;      /* Output stream length.              */
	char *stream_buf;       /* Output stream buffer.              */
	FILE *stream;           /* Output stream.                     */
	char *endbuf;           /* End buffer marker.                 */
	char *fbuf;             /* Start buffer marker.               */
	char *buf;              /* Current buffer position.           */
	int state;              /* Current state.                     */
	long fz;                /* File size.                         */
	FILE *f;                /* File.                              */
	int ret;                /* Return value.                      */

	ret = -1;

	if ((f = fopen(file, "r")) == NULL)
		PANIC_GOTO(close0, "Error: cannot open file: %s\n", file);

	/* Seek to the end of the file */
	if (fseek(f, 0L, SEEK_END) != 0)
		PANIC_GOTO(close1, "Error: cannot fseek file: %s\n", file);

	/* Byte offset to the end of the file (size) */
	if ((fz = ftell(f)) < 0)
		PANIC_GOTO(close1, "Error: cannot obtain file (%s) size\n", file);
	rewind(f);

	/* Allocate memory. */
	if ((fbuf = malloc(fz+1)) == NULL)
		PANIC_GOTO(close1, "Error: cannot allocate %lu bytes\n", fz+1);

	/* Read file into buffer */
	if (fread(fbuf, 1, fz, f) != (size_t)fz)
		PANIC_GOTO(close2, "Error: cannot read %lu bytes of file\n", fz);
	fbuf[fz] = '\0';

	/* Stream/buffer list. */
	stream_len = 8192;
	if ((stream = open_memstream(&stream_buf, &stream_len)) == NULL)
		PANIC_GOTO(close2, "Unable to create stream buffer, file: %s\n", file);

	/* Setup buffers and clear everything. */
	state         = HL_DEFAULT;
	keyword_start = NULL;
	buf           = fbuf;
	endbuf        = fbuf + fz;
	curr_line     = 1;
	curr_coll     = 0;
	saved_lineno  = 0;
	saved_colno   = 0;

	dict_checker_init(&d);

	/*
	 * Iterate char by char and when encounters one of
	 * the valid (comments, strings or identifiers)
	 * check if there is some misspelling on it.
	 */
	while (buf < endbuf)
	{
		if (*buf == '\n')
		{
			curr_line++;
			curr_coll = 0;
		}
		else
			curr_coll++;

		switch (state)
		{
			/* Default state. */
			case HL_DEFAULT:
			{
				/*
				 * If potential identifier.
				 *
				 * A valid C identifier may contain numbers, but *not*
				 * as a suffix.
				 */
				if (is_ident[(int)*buf] && !is_digit[(int)*buf])
				{
					saved_lineno = curr_line;
					saved_colno  = curr_coll;
					keyword_start = buf;
					state = HL_IDENTIFIER;
				}

				/*
				 * If potential number.
				 *
				 * keyword_start can be dropped since we do not care
				 * about numbers.
				 *
				 * We just need to deal with numbers in order to not
				 * confuse identifiers with numbers, like: 123ULL, 123
				 * would be ignored, but ULL would be considered as
				 * identifier if not handled as part of number.
				 */
				else if (is_digit[(int)*buf])
					state = HL_NUMBER;

				/*
				 * If potential char.
				 *
				 * We also do not care about characters, but we need
				 * to recognize them in order to avoid being recognized
				 * as identifier too.
				 */
				else if (*buf == '\'')
					state = HL_CHAR;

				/* If potential string. */
				else if (*buf == '"')
				{
					saved_lineno  =  curr_line;
					saved_colno   = (curr_coll + 1);
					keyword_start = (buf + 1);
					state = HL_STRING;
				}

				/* Line or multi-line comment. */
				else if (*buf == '/' && buf+1 < endbuf)
				{
					/* If one of them. */
					if (*(buf + 1) == '/' && buf+2 < endbuf && *(buf + 2) != '\n')
					{
						state = HL_COMMENT_SINGLE;
						buf++;
						curr_coll++;
						keyword_start = (buf + 1);
						saved_lineno  = curr_line;
						saved_colno   = (curr_coll + 1);
					}

					/* Multi-line comments should be handled as usual. */
					else if (*(buf+1) == '*')
					{
						state = HL_COMMENT_MULTI;
						buf++;
						curr_coll++;
						keyword_start = (buf + 1);
						saved_lineno  = curr_line;
						saved_colno   = curr_coll;
					}
				}

				/* Preprocessor. */
				else if (*buf == '#')
				{
					keyword_start = buf;
					state = HL_PREPROCESSOR;
				}
			}
			break;

			/* Single-line comment. */
			case HL_COMMENT_SINGLE:
			{
				/* Skip line until \n or EOF. */
				skip_line(&buf, endbuf);

				if ((cmd_flags & CMD_ENABLE_SL) &&
					handle_line(&d, stream, file, SPELL_SLINE, saved_lineno,
					saved_colno, keyword_start, buf) < 0)
				{
					PANIC_GOTO(close3, "Error while reading a single-line comment,"
						"line: %u / col: %u\n", saved_lineno, saved_colno);
				}

				curr_line++;
				curr_coll = 0;
				state = HL_DEFAULT;
			}
			break;

			/* Multi-line comment. */
			case HL_COMMENT_MULTI:
			{
				if (*buf == '*' && buf+1 < endbuf && *(buf + 1) == '/')
				{
					if ((cmd_flags & CMD_ENABLE_ML) &&
						handle_multiline(&d, stream, file, saved_lineno, saved_colno,
						keyword_start, buf - 1) < 0)
					{
						PANIC_GOTO(close3, "Error while reading a multi-line comment,"
							"line: %u / col: %u\n", saved_lineno, saved_colno);
					}
					state = HL_DEFAULT;
					buf++;
				}
			}
			break;

			/* Identifier state. */
			case HL_IDENTIFIER:
			{
				/* End of identifier. */
				if (!is_ident[(int)*buf])
				{
					if ((cmd_flags & CMD_ENABLE_ID) &&
						handle_identifier(&d, stream, file, saved_lineno, saved_colno,
						keyword_start, buf - 1) < 0)
					{
						PANIC_GOTO(close3, "Error while reading a identifier,"
							"line: %u / col: %u\n", saved_lineno, saved_colno);
					}
					state = HL_DEFAULT;

					/*
					 * We still need to parse that character, so we rewind
					 * one char.
					 */
					if (!curr_coll)
						curr_line--;
					else
						curr_coll--;
					goto skip_increment;
				}
			}
			break;

			/*
			 * Number state.
			 *
			 * Although we do not check numbers, we should not ignore numbers,
			 * because things like 123ULL is valid and should not be handled
			 * as an identifier.
			 *
			 */
			case HL_NUMBER:
			{
				char c = tolower(*buf);

				/*
				 * Should we end the state?.
				 *
				 * Very important observation:
				 * Although the number highlight works fine for most (if not all)
				 * of the possible cases, it also assumes that the code is written
				 * correctly and the source is able to compile, meaning that:
				 *
				 * Numbers like: 123, 0xABC123, 12.3e4f, 123ULL....
				 * will be correctly identified and highlighted
				 *
				 * But, 'numbers' like: 123ABC, 0xxxxABCxx123, 123UUUUU....
				 * will also be considered as numbers.
				 *
				 * It also assumes that no identifier will start with a number
				 * and everything starting with a number (except inside strings or
				 * comments) will be a number.
				 */
				if (!is_digit[(int)c] && (c < 'a' || c > 'f') && c != 'b' &&
					c != 'x' && c != 'u' && c != 'l' && c != '.')
				{
					/* Just ignore and reset state, */
					state = HL_DEFAULT;

					/*
					 * We still need to parse that character, so we rewind
					 * one char.
					 */
					if (!curr_coll)
						curr_line--;
					else
						curr_coll--;
					goto skip_increment;
				}
			}
			break;

			/* Char state. */
			case HL_CHAR:
			{
				/*
				 * Should we end char state?, if so,
				 * just ignore and reset state.
				 */
				if (*buf == '\'' && buf+1 < endbuf && *(buf + 1) != '\'')
					state = HL_DEFAULT;
			}
			break;

			/* String state. */
			case HL_STRING:
			{
				/*
				 * Should we end string state?.
				 *
				 * Two conditions:
				 * a) If " and previous character is not \, i.e != \"
				 * (not inside a double quotes escape)
				 *
				 * b) If " and last two previous characters is \\, i.e == \\
				 * (inside a \ scape sequence)ç
				 */
				if (*buf == '"' &&
					(*(buf - 1) != '\\' ||
						(buf - 2 >= fbuf
							&& *(buf - 1) == '\\' &&
								*(buf - 2) == '\\')
					)
				)
				{
					if ((cmd_flags & CMD_ENABLE_ST) &&
						handle_line(&d, stream, file, SPELL_STR, saved_lineno, saved_colno,
						keyword_start, buf - 1) < 0)
					{
						PANIC_GOTO(close3, "Error while reading a string,"
							"line: %u / col: %u\n", saved_lineno, saved_colno);
					}
					state = HL_DEFAULT;
				}
			}
			break;

			/* Preprocessor. */
			case HL_PREPROCESSOR:
			{
				/* Skip line until \n or EOF. */
				skip_line(&buf, endbuf);
				curr_line++;
				curr_coll = 0;

				/*
				 * Check if have to ignore the next line or not.
				 *
				 * Note that this is not perfect, since a user may put spaces
				 * after '\', which is not usual and not recommended, but...
				 * who knows... users...
				 */
				if (*(buf - 1) != '\\')
					state = HL_DEFAULT;
			}
			break;

			default:
				break;
		}
		buf++;
skip_increment:;
	}

	dict_checker_finish(&d);

	/*
	 * Although printf is thread-safe, we need to ensure
	 * that only one thread dumps misspellings per time,
	 * otherwise, mixed lines from multiples files could
	 * be printed together.
	 */
#ifndef NOT_PTHREADS
pthread_mutex_lock(&stdout_mutex);
#endif

	fflush(stream);
	dump_misspellings(stream_buf, stream_len);

#ifndef NOT_PTHREADS
pthread_mutex_unlock(&stdout_mutex);
#endif

	ret = 0;
close3:
	fclose(stream);
	free(stream_buf);
close2:
	free(fbuf);
close1:
	fclose(f);
close0:
	return (ret);
}

/**
 * @brief Worker thread, fetches a new file to process
 * as soon as available.
 */
#ifndef NOT_PTHREADS
void *spell_worker(void *data)
{
	((void)data);
	struct file_queue *queue;

	while (1)
	{
		pthread_mutex_lock(&queue_mutex);
			while (file_queue->path == NULL)
			{
				if (done)
				{
					pthread_mutex_unlock(&queue_mutex);
					return (NULL);
				}
				pthread_cond_wait(&file_avail, &queue_mutex);
			}

			queue = file_queue;
			file_queue = file_queue->next;
		pthread_mutex_unlock(&queue_mutex);

		spell_file(queue->path);
		free(queue->path);
		free(queue);
	}
	return (data);
}
#endif

/**
 * @brief nftw() handler, called each time a new file
 * is discovered. This routine spells checker the
 * file if it is eligible (non-empty regular file that
 * and .c or .h extension).
 *
 * @param filepath File path to be analyzed.
 * @param info File path stat structure.
 * @param typeflag File path type.
 * @param pathinfo File path additional infos.
 *
 * @return Returns 0 if success, -1 otherwise.
 */
static int do_check_file(const char *filepath, const struct stat *info,
                const int typeflag, struct FTW *pathinfo)
{
	size_t len;
#ifndef NOT_PTHREADS
	struct file_queue *queue;
#endif

	/* Ignore everything that is not a file or is empty. */
	if (typeflag != FTW_F || !info->st_size)
		return (0);

	len = strlen(filepath);

	/* The files should have the extension .c or .h. */
	if (((len - pathinfo->base) >= 3 && filepath[len - 2] == '.') &&
		(filepath[len - 1] == 'c' || filepath[len - 1] == 'h'))
	{
#ifndef NOT_PTHREADS
		if (nworkers > 1)
		{
			queue = malloc(sizeof(struct file_queue));
			queue->path = strdup(filepath);

			pthread_mutex_lock(&queue_mutex);
				queue->next = file_queue;
				file_queue = queue;
				pthread_cond_signal(&file_avail);
			pthread_mutex_unlock(&queue_mutex);
    	}
		else
#endif
		{
			if (spell_file(filepath))
			{
				fprintf(stderr, "Error: Unable to check file %s\n", filepath);
				return (-1);
			}
		}
    }
    return (0);
}

/**
 * Spell checks recursively or a given file.
 */
static void do_check(void)
{
	struct stat path_stat; /* Path stat.     */
	char *input;           /* Current input. */
	int result;            /* NFTW output.   */

	input = optparse_arg(&options);

	/* If none input, check current directory and finish. */
	if (!input)
	{
		input = ".";
		if (stat(input, &path_stat) != 0)
			panic("Error: cannot stat file: %s\n", input);

		/* Recursive check. */
		result = nftw(input, do_check_file, MAX_FDS, FTW_PHYS|FTW_MOUNT);
		if (result != 0)
			panic("Error: Cannot traverse all the paths from: %s\n", input);

		return;
	}

	/* Multiples inputs, process each of them. */
	do
	{
		if (stat(input, &path_stat) != 0)
			panic("Error: cannot stat file: %s\n", input);

		/*
		 * Check if file or folder: if the former, do a normal check
		 * and we're done; if the latter, do a recursive check on
		 * the path informed.
		 *
		 * We purposely do not check symlinks.
		 */
		if (S_ISREG(path_stat.st_mode))
		{
			if (spell_file(input))
				panic("Error: Unable to check file: %s\n", input);
		}

		else if (S_ISDIR(path_stat.st_mode))
		{
			/* Recursive check. */
			result = nftw(input, do_check_file, MAX_FDS, FTW_PHYS|FTW_MOUNT);
			if (result != 0)
			{
				panic("Error: Cannot traverse all the paths from: %s\n",
					input);
			}
		}

		/* Error, we only check regular files and directories. */
		else
			panic("Error: Parameter (%s) is not a regular file or directory!",
				input);

	} while ((input = optparse_arg(&options)) != NULL);
}

/**
 * Shows the usage.
 *
 * @param prgname Program name.
 */
static void usage(const char *prgname)
{
	fprintf(stderr, "Usage: %s [OPTIONS] [PATH]\n", prgname);
	fprintf(stderr, "\n   Searches for misspellings on files and paths recursively\n\n");
	fprintf(stderr, "Example: \n");
	fprintf(stderr, "   srcry file.c -s                 (only strings)\n");
	fprintf(stderr, "   srcry file1.c file2.c           (default)\n");
	fprintf(stderr, "   srcry path1/ a.c b.c c.c d.c -a (all)\n");
	fprintf(stderr, "   (and etc)\n\n");
	fprintf(stderr, "Options: \n");
	fprintf(stderr, "   -l Enable single-line (//) comments analysis\n");
	fprintf(stderr, "   -m Enable multi-line (/* */) comments analysis\n");
	fprintf(stderr, "   -s Enable strings analysis\n");
	fprintf(stderr, "   -i Enable identifiers analysis (beware: high rate of false positives)\n");
	fprintf(stderr, "   -a Enable all above (-lmsi)\n");
	fprintf(stderr, "   -h Shows this help\n\n");
	fprintf(stderr, "If OPTIONS omitted, options -l, -m and -s are used.\n\n");
	fprintf(stderr, "Obs:\n");
	fprintf(stderr, "PATH can be one or multiples filenames/paths (for recursive* analysis).\n");
	fprintf(stderr, "If omitted, the current directory is used.\n");
	fprintf(stderr, "* Recursive analysis only checks for .c and .h files.\n\n");
	fprintf(stderr, "Debug options:\n");
	fprintf(stderr, "   -n Disables all analysis (only parses the input)\n");
	exit(EXIT_FAILURE);
}

/**
 * Parse the command-line arguments.
 *
 * @param argv Argument list.
 *
 * @return Returns 0 if success or abort otherwise.
 */
static int parse_args(char **argv)
{
	((void)optparse_long);

	int c; /* Current arg. */
	optparse_init(&options, argv);
	while ((c = optparse(&options, "lmsianh")) != -1)
	{
		switch (c)
		{
			case 'l':
				cmd_flags |= CMD_ENABLE_SL;
				break;
			case 'm':
				cmd_flags |= CMD_ENABLE_ML;
				break;
			case 's':
				cmd_flags |= CMD_ENABLE_ST;
				break;
			case 'i':
				cmd_flags |= CMD_ENABLE_ID;
				break;
			case 'a':
				cmd_flags |= (CMD_ENABLE_SL|CMD_ENABLE_ML|CMD_ENABLE_ST|
					CMD_ENABLE_ID);
				break;
			case 'n':
				cmd_flags |= CMD_DISABLE;
				break;
			case 'h':
				usage(argv[0]);
				break;
			case '?':
				fprintf(stderr, "%s: %s\n", argv[0], options.errmsg);
				usage(argv[0]);
				break;
			default:
				usage(argv[0]);
				break;
		}
	}

	/* Enable default flags if none is set. */
	if (!cmd_flags)
		cmd_flags = (CMD_ENABLE_SL|CMD_ENABLE_ML|CMD_ENABLE_ST);

	return (0);
}

/**
 * Main routine.
 */
int main(int argc, char **argv)
{
	((void)argc);
	COMPILE_TIME_ASSERT(sizeof(char) == 1);

	parse_args(argv);
	dict_init();

#ifndef NOT_PTHREADS
	file_queue = calloc(1, sizeof(struct file_queue));
	nworkers = (int)sysconf(_SC_NPROCESSORS_ONLN);
	nworkers = (nworkers > NUM_WORKERS) ? NUM_WORKERS : nworkers;

	/* Spawn. */
	for (int i = 0; i < nworkers; i++)
		if (pthread_create(&workers[i], NULL, &spell_worker, NULL))
			panic("Cannot create thread #%d\n", i);
#endif

	do_check();

#ifndef NOT_PTHREADS
	pthread_mutex_lock(&queue_mutex);
		done = 1;
		pthread_cond_broadcast(&file_avail);
	pthread_mutex_unlock(&queue_mutex);

	/* Join =). */
	for (int i = 0; i < nworkers; i++)
		if (pthread_join(workers[i], NULL))
			panic("Error while joining thread #%d\n", i);

	free(file_queue);
#endif

	dict_finish();
	return (0);
}
