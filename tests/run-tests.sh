#!/usr/bin/env bash

#
# MIT License
#
# Copyright (c) 2020 Davidson Francis <davidsondfgl@gmail.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

# Fancy colors =)
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

# Folders
export CURDIR="$(cd "$(dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd)"
export SPELL_FOLDER=$(readlink -f $CURDIR/..)
pushd . > /dev/null

cd "$CURDIR/"

echo ""
echo "(These tests are made for 'Wordlist', not Aspell."
echo " Please make sure that you're running against a"
echo " Wordlist build)"
echo ""

echo -n "Tests..."

# Run
../spell test.c -a > outputs/test_out_wordlist_run

if [ $? -eq 0 ]
then
	if cmp -s outputs/test_out_wordlist_run outputs/test_out_wordlist_exp
	then
		echo -e " [${GREEN}PASSED${NC}]"

		if [ -x "$(command -v valgrind)" ]
		then
			echo -n "Valgrind tests..."

			valgrind\
				--leak-check=full\
				--errors-for-leak-kinds=all\
				--error-exitcode=1\
				../spell test.c -a &> /dev/null

			if [ $? -eq 0 ]
			then
				echo -e " [${GREEN}PASSED${NC}]"
			else
				echo -e " [${RED}NOT PASSED${NC}] (memory leaks)"
				pushd > /dev/null
				exit 1
			fi
		fi
	else
		echo -e " [${RED}NOT PASSED${NC}] (output differs from expected)"
		pushd > /dev/null
		exit 1
	fi
else
	echo -e " [${RED}NOT PASSED${NC}] (execution error)"
	pushd > /dev/null
	exit 1
fi

pushd > /dev/null
