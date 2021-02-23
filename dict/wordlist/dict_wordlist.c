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
#include "dict_wordlist.h"
#include <strings.h>

/* External functions and variables. */
extern int hash(const unsigned char *key, int len); /* MPH hash function. */
extern struct words {
	const char *w;
	int len;
} words_tbl[];

/**
 * @brief Check if a given key @p k of length @P l
 * belongs to the hashtable.
 *
 * @param k Key to be checked.
 * @param l Key size.
 *
 * @return Returns 1 if found and 0 otherwise.
 */
static inline int contains(const char *k, int l)
{
	struct words *w;
	int size;
	int h;

	size = (l == -1) ? (int)strlen(k) : l;
	h = hash((unsigned char*)k, size);

	/* Key not found: mostly due length out of range. */
	if (h == -1)
		return (0);

	/*
	 * We can avoid strlen by storing all the key
	 * lengths.
	 */
	w = &words_tbl[h];
	if (w->len != size)
		return (0);

	return (strncasecmp(w->w, k, size) == 0);
}

/**
 * @brief Gets the next word [A-Za-z]+ of current buffer
 * and advances its pointer.
 *
 * @param start Current buffer pointer.
 * @param end Points to the last valid buffer position.
 *
 * @param Returns the start of the next word or, if not found,
 * @p end pointer.
 */
static const char* next_word(const char **start, const char *end)
{
	const char *p = *start;
	const char *w_start;

	/* Skip non-word (i.e, different than [A-z]) chars. */
	while (p <= end && !isalpha(*p))
		p++;

	w_start = p;

	/* SKip word characters. */
	while (p <= end && isalpha(*p))
		p++;

	*start = p;
	return (w_start);

}

/**
 * @brief Initializes Wordlist dictionary
 *
 * @return Returns 0 if success, -1 otherwise.
 */
int dict_init(void){return (0);}

/**
 * @brief Finishes all the data structures from Wordlist.
 *
 * @return Returns always 0.
 */
int dict_finish(void){return (0);}

/**
 * @brief Initializes the checker for Wordlist dictionary
 *
 * @return Returns 0 if success, -1 otherwise.
 */
int dict_checker_init(struct dict_data *d)
{
	d->line_start = 0;
	d->line_end   = 0;
	d->buf        = 0;
	return (0);
}

/**
 * @brief Finishes the checker from Wordlist.
 *
 * @return Returns always 0.
 */
int dict_checker_finish(struct dict_data *d)
{
	((void)d);
	return (0);
}

/**
 * @brief Check a single word per time.
 *
 * @param str Word to be checked.
 * @param size Word size, or -1 to be inferred.
 *
 * @return Returns 1 if @p str is correct and 0 otherwise.
 */
int dict_check_word(const char *str, int size)
{
#ifdef DEBUG
	printf("checking word: (%.*s)\n", size, str);
#endif

#ifndef CHECK_REVERSE
	return (contains(str, size));
#else
	return (!contains(str, size));
#endif
}

/**
 * @brief Evaluates the current line and prepares to find
 * misspellings.
 *
 * @param line Line to be evaluated: can span to multiples lines and have
 * multiples words.
 *
 * @param size Line size (in bytes).
 *
 * @return Returns always 0.
 *
 * @note In order to check misspellings on lines, this function
 * *must* be called _before_ dict_next_misspelling().
 */
int dict_check_line(struct dict_data *d, const char *line, int size)
{
	d->line_start = line;
	d->line_end   = line + size;
	d->buf        = line;
	return (0);
}

/**
 * @brief Obtains the next misspelled word from a previous
 * processed line (via dict_check_line()).
 *
 * @param len Misspelled word length pointer.
 * @param off Offset (from the begging of the line) for the
 *            misspelled word.
 *
 * @return Returns 1 if theres a misspelling and 0 otherwise.
 *
 * @note This function should be called only *after* a single
 * call the dict_check_line().
 */
int dict_next_misspelling(struct dict_data *d, unsigned *len, unsigned *off)
{
	const char *p; /* Word pointer. */
	int size;      /* Word size.    */

	while ((p = next_word(&d->buf, d->line_end)) < d->line_end)
	{
		size  = (int)LENGTH_PTR(d->buf - 1, p);
		if (dict_check_word(p, size) == 0)
		{
			*len = size;
			*off = ((unsigned)LENGTH_PTR(p, d->line_start)) - 1;
			return (1);
		}
	}
	return (0);
}
