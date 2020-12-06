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

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Main
 */
int main(int argc, char **argv)
{
	ssize_t nread; /* Amount of characters read. */
	size_t len;    /* Line size.                 */
	char *line;    /* Current line.              */
	FILE *f;       /* Current file.              */

	/* We need a file. */
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <file-name>\n", argv[0]);
		return (1);
	}

	line  = NULL;
	len   = 0;
	f     = fopen(argv[1], "r");

	/* Check if opened. */
	if (f == NULL)
	{
		fprintf(stderr, "Unable to open %s!\n", argv[1]);
		return (1);
	}

	printf("/* Auto-generated file by %s, please do not edit manually!. */\n",
		argv[0]);

	puts("struct words {\n\tconst char *w;\n\tint len;\n} words_tbl[] = {");

	/* Read each line and mounts our struct/array. */
	while ((nread = getline(&line, &len, f)) != -1)
	{
		if (line[nread - 1] == '\n')
		{
			line[nread - 1] = '\0';
			nread--;
		}

		/* Skip empty lines. */
		if (nread)
			printf("\t{\"%s\", %d},\n", line, (int)(nread));
	}

	puts("\t{0, 0}\n};");
	puts("int words_tbl_len = sizeof(words_tbl)/sizeof(words_tbl[0]);");
	free(line);
	fclose(f);
}
