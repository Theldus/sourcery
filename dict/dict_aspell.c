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

#include <aspell.h>
#include "spell.h"

AspellSpeller *speller;
AspellDocumentChecker *checker;

/**
 * @brief Initializes Aspell dictionary
 *
 * @return Returns if success, -1 otherwise.
 */
int dict_init(void)
{
	AspellCanHaveError *ret;
	AspellConfig *config;
	int i;

	/* Initialize Aspell with en_US. */
	config = new_aspell_config();
	aspell_config_replace(config, "lang", "en_US");
	ret = new_aspell_speller(config);
	delete_aspell_config(config);

	/* Check if error. */
	if (aspell_error(ret) != 0)
	{
		fprintf(stderr, "Aspell error: %s\n", aspell_error_message(ret));
		delete_aspell_can_have_error(ret);
		return (-1);
	}

	speller = to_aspell_speller(ret);
	config  = aspell_speller_config(speller);

	/* Initialize document checker. */
	ret = new_aspell_document_checker(speller);
	if (aspell_error(ret) != 0)
	{
		fprintf(stderr, "Aspell error: %s\n", aspell_error_message(ret));
		return (-1);
	}
	checker = to_aspell_document_checker(ret);

	/*
	 * Fill our session dictionary with some new words, in order to reduce
	 * the false positive rate.
	 */
	for (i = 0; i < keywords_tbl_len; i++)
		aspell_speller_add_to_session(speller, keywords_tbl[i], -1);

	return (0);
}

/**
 * @brief Finishes all the data structures from Aspell.
 *
 * @return Returns always 0.
 */
int dict_finish(void)
{
	delete_aspell_speller(speller);
	delete_aspell_document_checker(checker);
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
	return (aspell_speller_check(speller, str, size) != 0);
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
int dict_check_line(const char *line, int size)
{
	aspell_document_checker_process(checker, line, size);
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
int dict_next_misspelling(unsigned *len, unsigned *off)
{
	AspellToken token;
	token = aspell_document_checker_next_misspelling(checker);
	*len = token.len;
	*off = token.offset;
	return (token.len != 0);
}
