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

#include <stdio.h> /* Includes are not analyzed. */
#include <stdlib.h>
#include <inttypes.h>

#define tini_macro_single_line 0 /* Nor macros definitions. */
#define big_macr_multi_line(x) \
    do {\
        for (int indx = 0; indx < (x); indx++)\
        {\
            if (indx % 2 == 0)\
                printf("even\n");\
            else\
                printf("odd\n");\
        }\
    } while(0)

int my_age = tini_macro_single_line; // I wont tell youu

/**
 * @brief Document multi-line comment without any purpose
 *
 * @param argc Argument count.
 * @param argv Arguments.
 *
 * @return Returns always 0.
 *
 * @note Thix is a error.
 */
int main(int argc, char **argv)
{
    big_macr_multi_line(10);
    printf("Format specifiers works as well: %d %lld %" PRIx64 "\n",
        /* Orshouldbe, right? */ 1, 1LL, 1ULL);

    // Alone coment.

    /*
     * Identifier that is valid as a complete word 'aligned_alloc'
     * but not individually since 'alloc' alone is not a valid word.
     *
     * Also note that this only occurs for identifiers, for comments
     * and strings we always to word-splitting.
     */
    void *ptr = aligned_alloc(8, 1024);
    free(ptr);

    return (0);
}
