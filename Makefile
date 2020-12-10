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

#===================================================================
# Paths
#===================================================================

INCLUDE = $(CURDIR)/include/ -I $(CURDIR)/dict/
SRC     = $(CURDIR)/

#===================================================================
# Flags
#===================================================================

CC          ?= gcc
CFLAGS      += -Wall -Wextra -O3
CFLAGS      += -I $(INCLUDE) -std=c99 -pedantic
USE_PTHREAD ?= yes

#
# Spell checkers currently available:
# - aspell
# - wordlist
#
# Aspell do not need explanations.
#
# Wordlist is a hand-made spell checker that uses minimal perfect
# hashing to reduce the lookup times. It's wordlist have a fairly
# amount of words (124k) extracted directly from aspell:
#     aspell -d en dump master | aspell -l en expand > words.txt
# and preprocessed later (lowercase, sort, remove duplicates).
#
# Wordlist also have a great performance (up to 2x faster than
# Aspell) and do not requires any dependencies.
#
DICT ?= wordlist

ifeq ($(DICT), aspell)
	CFLAGS  += -DDICT_ASPELL -DNOT_PTHREADS
	LDFLAGS += -laspell
else
	CFLAGS  += -DDICT_WORDLIST
	ifeq ($(USE_PTHREAD), yes)
		LDFLAGS += -pthread
	else
		CFLAGS += -DNOT_PTHREADS
	endif
endif

#===================================================================
# Rules
#===================================================================

# Sources
C_SRC = $(wildcard $(SRC)/dict/$(DICT)/*.c) \
		$(wildcard $(SRC)/*.c)

# Objects
OBJ = $(C_SRC:.c=.o)

# Build objects rule
%.o: %.c
	$(CC) $< $(CFLAGS) -c -o $@

# All
all: spell

# Main program
spell: $(OBJ)
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -o $@

# Generate wordlist.c and hash_wordlist.c
gen:
	$(MAKE) -C dict/wordlist/gen/ all

# General
clean:
	rm -f $(SRC)/*.o
	rm -f $(SRC)/spell
	rm -f $(SRC)/dict/$(DICT)/*.o
	$(MAKE) -C dict/wordlist/gen/ clean
