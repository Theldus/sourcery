# Dictionaries abstraction
Sourcery provides a certain 'abstraction layer' for dictionaries (note that here
I'm calling spell checkers and dictionaries of the same thing) and uses this
abstraction for a smooth and transparent implementation for the rest of the code.
Therefore, the dict/ folder contains everything that is needed for porting new
spell checkers into Sourcery, just follow the API described below.

## API
The Sourcery dictionary API consists of the definition of 7 functions, 1 struct
and a macro, namely:

### Functions
```c
int dict_init(void);
```
Initializes the entire global state of the spell checker (such as variables and
specific functions) and that will be maintained until the end of the program.
Should return 0 on success, -1 otherwise.

```c
int dict_finish(void);
```
Finalizes the entire global state of the spell checker, will be invoked when the
program terminates, and therefore must deallocate all resources obtained during
runtime. Should return 0 on success, -1 otherwise.

```c
int dict_checker_init(struct dict_data *d);
```
Initializes all data to be used during checking a file, this function is especially
useful for multi-threaded implementations and therefore need local data during the
execution of a thread. If your implementation does not support multi-threaded (such
as Aspell), leave it empty. Should return 0 on success, -1 otherwise.

```c
int dict_checker_finish(struct dict_data *d);
```
Counterpart of `dict_checker_init`: finalizes all data initialized by `dict_checker_init`,
is invoked once per file. Should return 0 on success, -1 otherwise.

```c
int dict_check_word(const char *str, int size);
```
Checks whether a given word _str_ of size _size_ is valid or not. Must return 1 if
correct, and 0 otherwise.

```c
int dict_check_line(struct dict_data *d, const char *line,
		int size);
```
Initializes line checking, note that this function should not return whether
the line/phrase is correct or not, but only initialize the data contained in
`struct dict_data d`. Returns 0 if successful, -1 otherwise.

```c
int dict_next_misspelling(struct dict_data *d, unsigned *len,
		unsigned *off);
```
Evaluates whether the previously initialized line (possibly in struct dict_data) is
correct or not. Note that here this function must go through each word in the line
and for each new error, it must be interrupted and set the word size and the offset
relative to the beginning of the line, by the parameters _len_ and _off_ respectively.
The function should return 1 if new errors are found and 0 otherwise.

### Struct
The `struct dict_data` structure must be defined in a header specific to the new
dictionary in question and must contain all the data that needs to be thread-safe,
that is, not global. The existence of this struct is due to the `dict_next_misspelling`
routine that needs to keep track of the positions in which it advances on the line and
that is called by multiple threads.

Take the Wordlist structure as an example:
```c
#ifndef WORDLIST_DICT_H
#define WORDLIST_DICT_H

	/* Thread-safe data from wordlist. */
	struct dict_data
	{
		const char *line_start;
		const char *line_end;
		const char *buf;
	};

#endif /* WORDLIST_DICT_H */
```
### Macro
Each dictionary must also define a macro (such as `DICT_ASPELL` or` DICT_WORDLIST`) so that
dict/dict.h can include the appropriate header. Check the root Makefile to define the macros.

----
In any doubt, check the Aspell and Wordlist implementations, they are very straightforward and
not difficult to understand.
