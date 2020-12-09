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

#ifndef SPELL_H
#define SPELL_H

	/* Enable nftw(). */
	#define _XOPEN_SOURCE 700
	#define _LARGEFILE64_SOURCE
	#define _FILE_OFFSET_BITS 64

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <ctype.h>
	#include <limits.h>
	#include <errno.h>
	#include <stddef.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <unistd.h>
	#include <ftw.h>

	/* Always inline. */
#	if defined(__GNUC__) || defined(__GNUG__) || defined(__clang__)
#		define INLINE  __attribute__((always_inline)) inline
#	else
#		define INLINE inline
#	endif

	/* Panic that goto to a position for clean up. */
	#define PANIC_GOTO(label, str, ...) \
		do {\
			fprintf(stderr, str, __VA_ARGS__); \
			goto label; \
		} while (0)

	/* Panic and abort. */
	#define panic(...) \
		do {\
			fprintf(stderr, __VA_ARGS__); \
			exit(EXIT_FAILURE); \
		} while (0)

	/* Get length ptr. */
	#define LENGTH_PTR(e,s) \
		(((ptrdiff_t)((e) - (s)))+1)

	/* Max FDS for usage on nftw(). */
	#define MAX_FDS 7

	/* Num max worker threads. */
	#define NUM_WORKERS 8

	/**
	 * Checks if the given character belongs to a valid identifier
	 * or not.
	 *
	 * @param c Character to be checked.
	 *
	 * @return Returns 1 if the character belongs to a valid
	 * identifier, 0 otherwise.
	 */
	INLINE static int is_char_identifier(char c)
	{
		return (isalnum(c) || c == '_');
	}

	/* Our keyword table. */
	extern const char * const keywords_tbl[];
	extern int keywords_tbl_len;

#endif /* SPELL_H */
