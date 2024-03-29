# MIT License
#
# Copyright (c) 2020-2023 Davidson Francis <davidsondfgl@gmail.com>
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
PREFIX ?= /usr/local
BINDIR  = $(PREFIX)/bin

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

	ifeq ($(CHECK), reverse)
		WLST = rev_
		CFLAGS += -DCHECK_REVERSE
	endif
endif

#===================================================================
# Rules
#===================================================================

# Conflicts
.PHONY: tests

# Sources
C_SRC = $(SRC)/dict/$(DICT)/dict_wordlist.c \
		$(SRC)/dict/$(DICT)/$(WLST)hash_wordlist.c \
		$(SRC)/dict/$(DICT)/$(WLST)wordlist.c \
		srcry.c

# Objects
OBJ = $(C_SRC:.c=.o)

# Build objects rule
%.o: %.c
	$(CC) $< $(CFLAGS) -c -o $@

# All
all: srcry

# Main program
srcry: $(OBJ)
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -o $@

# Generate wordlist.c and hash_wordlist.c
gen:
	$(MAKE) -C dict/wordlist/gen/ all WLST=$(WLST)

# Tests
tests:
	$(MAKE) -C tests/ all WLST=$(WLST)

# Install rules
install: all
	install -d $(DESTDIR)$(BINDIR)
	install -m 755 srcry $(DESTDIR)$(BINDIR)

# Uninstall rules
uninstall:
	rm -f $(DESTDIR)$(BINDIR)/srcry

# General
clean:
	rm -f $(SRC)/*.o
	rm -f $(SRC)/srcry
	rm -f $(SRC)/dict/$(DICT)/*.o
	$(MAKE) -C dict/wordlist/gen/ clean WLST=$(WLST)
