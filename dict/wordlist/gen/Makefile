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
# Flags
#===================================================================

CC      ?= gcc
CFLAGS  += -Wall -Wextra -std=c99 -pedantic -O2
SRC      = gen.c
OBJ      = $(SRC:.c=.o)
WL_DIR   = $(abspath $(CURDIR)/../)

#===================================================================
# Rules
#===================================================================

# Build objects rule
%.o: %.c
	$(CC) $< $(CFLAGS) -c

# Build gen
all: $(WL_DIR)/$(WLST)wordlist.c $(WL_DIR)/$(WLST)hash_wordlist.c
	$(info $(^F) generated with success!)

# Generate wordlist.c
gen: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Generate hash_wordlist.c
mph/mph:
	git submodule update --init
	$(MAKE) -C mph/

.tmp_$(WLST)wordlist.txt: $(WLST)wordlist.txt
	@cat "$(WLST)wordlist.txt" | tr '[:upper:]' '[:lower:]' | sort |\
		sort -u > .tmp_$(WLST)wordlist.txt
	@cp .tmp_$(WLST)wordlist.txt $(WLST)wordlist.txt

$(WL_DIR)/$(WLST)wordlist.c: .tmp_$(WLST)wordlist.txt gen
	@./gen .tmp_$(WLST)wordlist.txt > $(WL_DIR)/$(WLST)wordlist.c

$(WL_DIR)/$(WLST)hash_wordlist.c: .tmp_$(WLST)wordlist.txt mph/mph
	@./mph/mph < .tmp_$(WLST)wordlist.txt | ./mph/emitc -nlsi > $(WL_DIR)/$(WLST)hash_wordlist.c

# Clean
clean:
	@rm -f *.o
	@rm -f gen
	rm -f .tmp_$(WLST)wordlist.txt
