# 🧙 sourcery
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](https://opensource.org/licenses/MIT)

A simple but very fast recursive source code spell checker made in C

## Introduction
Sourcery is a simple source code spelling checker written in C that aims to be
somewhat intelligent about the analysis it does, that is: Sourcery does not only
perform a 'tokenization' of words but manages to identify where they belong, and
thus, it is able to classify into four types of categories:
- Single line comments (//)
- Multi-line comments (/* */)
- Strings
- Identifiers

In this way, Sourcery makes available four types of filters (which can be
interleaved) for the analysis of the source code, and that allows more
selective analysis of the source code.

## Features
In addition to the four types of filters available, Sourcery performs recursive
directory analysis and has support (easily expandable) to two spell checkers at
the moment: Aspell and Wordlist.

GNU Aspell, as many of you may know, is a famous spell checker available in both
program and library format is quite robust and well tested, it is a good addition
to Sourcery.

Wordlist is a handmade spell checker/dictionary for Sourcery that has more than
126k words, including many libc functions and C language keywords. Unlike Aspell,
Wordlist has multithread support and can analyze the entire Linux src tree in
0.52s*.

Its options/command-line arguments are as follows:
```text
Usage: srcry [OPTIONS] [PATH]

   Searches for misspellings on files and paths recursively

Example:
   srcry file.c -s                 (only strings)
   srcry file1.c file2.c           (default: -lms)
   srcry path1/ a.c b.c c.c d.c -a (all)
   (and etc)

Options:
   -l Enable single-line (//) comments analysis
   -m Enable multi-line (/* */) comments analysis
   -s Enable strings analysis
   -i Enable identifiers analysis (beware: high rate of false positives)
   -a Enable all above (-lmsi)
   -h Shows this help

If OPTIONS omitted, options -l, -m, and -s are used.

Obs:
PATH can be one or multiples filenames/paths (for recursive* analysis).
If omitted, the current directory is used.
* Recursive analysis only checks for .c and .h files.

Debug options:
   -n Disables all analysis (only parses the input)

```

**Notes:**

_* When built with GCC v10.2, using Sourcery's -s option (strings only) and with
cached source code._

## Comparison with other tools
There aren't many options for command-line tools that do spell analysis in source
code, but two that stand out and are worth comparing with Sourcery are:
[pyspellcode (#5a7212f)](https://github.com/louis-langholtz/pyspellcode) and
[scspell (#00ed694)](https://github.com/myint/scspell).

### Features
The table below illustrates the features that I consider most important for a
source code spell checker:

| Feature                                              |          sourcery          |       pyspellcode      | scspell |
|------------------------------------------------------|:--------------------------:|:----------------------:|:-------:|
| Analyze single-line comments                         |             Yes            |           Yes          |   Yes   |
| Analyze multi-line comments                          |             Yes            |           Yes          |   Yes   |
| Analyze strings                                      |             Yes            |           No           |   Yes   |
| Analyze identifiers                                  |             Yes            |           No           |   Yes   |
| Only single-line comments                            |             Yes            |           No           |    No   |
| Only multi-line comments                             |             Yes            |           No           |    No   |
| Only strings                                         |             Yes            |           No           |    No   |
| Only identifiers                                     |             Yes            |           No           |    No   |
| Recursive                                            |             Yes            |           No           |    No   |
| Support other languages (C++, Java...)               |            Yes*            |   No (only C and C++)  |   Yes   |
| Requires external dependencies (libraries, programs) | No (libaspell is optional) | Yes (clang + hunspell) |    No   |
| Easily portable                                      |             Yes            |           No           |   Yes   |
| Interactive                                          |             No             |           No           |   Yes   |
| Non-interactive                                      |             Yes            |           Yes          |   Yes   |
| Suggests alternatives                                |             No             |           No           |    No   |
| Show line number                                     |             Yes            |           Yes          |   Yes   |
| Show column number                                   |             Yes            |           No           |    No   |

**Notes:**

_* Support for other languages as long as they have a C-like syntax for comments,
strings, and identifiers._

### Performance
Performance is something that may or may not be important depending on the user's
needs, but it is one of the main concerns of Sourcery. The following table
summarizes the analysis of the three spell checkers for three different files
and different sizes: small, medium, and huge.

#### File analysis
| File      | lines of code | sourcery | pyspellcode | scspell                 |
|-----------|---------------|----------|-------------|-------------------------|
| [test.c](https://github.com/Theldus/sourcery/blob/80f09701031d5229cf774f4f740788adae329dc0/tests/test.c) | 72   | 0.3 ms (± 0.1 ms) | 154.8 ms (± 16.9 ms) | 122.6 ms (± 23.4 ms) |
| [ws.c](https://github.com/Theldus/wsServer/blob/aad4c429504df7275481ff1b32c0230d6a41904d/src/ws.c)       | 1095 | 0.6 ms (± 0.2 ms) | 980.2 ms (± 39.2 ms) | 291.1 ms (± 20.7 ms) |
| [sqlite3.c](https://gist.github.com/Theldus/1c9b7d59b3da7ed02533871bc98b8eff/raw/2f27e4d391ef53078753a3dc3bfc54e0aeb8700a/sqlite3.c) | 133611 | 75.9 ms (± 8.4 ms) | 258 s (± 9.29 s) | -- (canceled after 39 m) |

**Note:** All tests were run on [`hyperfine`](https://github.com/sharkdp/hyperfine),
with 3 warmup runs and 10 runs in a row, the results are the average times. All outputs
were redirected to /dev/null since only the processing time was important here. Sourcery,
pyspellcode, and scspell were executed with the parameters: `-lms`, `-a`, and `--report-only`,
respectively.

#### Recursive analysis
Unfortunately, there is no way to test the recursive analysis in the other tools.
However, the results below illustrate the times for some large projects in
Sourcery:

| Project                                               | Files amount (.c + .h) | Time                |
|-------------------------------------------------------|------------------------|---------------------|
| [Git (#3cf5978)](https://github.com/git/git)          | 712                    |  11.1 ms (± 0.7 ms) |
| [Qemu (#1758428)](https://github.com/qemu/qemu)       | 4906                   |  48.0 ms (± 1.6 ms) |
| [Linux (#270315b)](https://github.com/torvalds/linux) | 50887                  | 522.4 ms (± 2.5 ms) |

**Note:**

**a)** Sourcery was invoked with the `-s` (strings-only) option and all output
was redirected to /dev/null. The result is the average time of multiples
executions, cached source code.

**b)** All performance tests were performed in the following environment:
Slackware 14.1, x86_64, GCC v10.2, Python 2.7.12 on an i7 2600.
Sourcery has been compiled with Wordlist and pthreads support enabled.

## Building/Installing
Sourcery only requires a POSIX-like environment and a c99 compiler; optionally, if
desired, libaspell is required if the user wants to use Aspell instead of Wordlist
(default).

The selection of the spell checker is done by the environment variable 'DICT':
`aspell` or `wordlist`, if nothing is specified, wordlist will be used, therefore:

### Wordlist
```bash
# Build with Wordlist support
make         # (or make DICT=wordlist)
make install # (PREFIX and DESTDIR may be set in order to change the paths (default: /usr/local/))
```

#### Reverse check
Sourcery also is capable to do reverse checking, that is: given a list of misspellings, it issues
errors in stdout for each misspelling found in the file. It works in exactly the same way as
Linux's checkpatch.pl spell checker, but _much_ faster:
```bash
# Build with Wordlist + Reverse check support
make CHECK=reverse # (or make DICT=wordlist CHECK=reverse)
make install       # (PREFIX and DESTDIR may be set in order to change the paths)
```

### Aspell
```bash
# Build with Aspell support
make DICT=aspell
make install # (PREFIX and DESTDIR may be set in order to change the paths (default: /usr/local/))
```
Please note that Aspell and Wordlist support are mutually exclusive, that is, it is
not possible to support both in a single build. In case of doubt, use Wordlist,
which does not require dependencies.

## Why 'sourcery'?
'Sourcery' is just a play on the words _source, sorcery, spell_... got it? =).

## Contributing
Sourcery is always open to the community and willing to accept contributions,
whether with issues, documentation, testing, new features, bugfixes, typos, and
etc. Welcome aboard.

## License and Authors
Sourcery is licensed under MIT License. Written by Davidson Francis and
(hopefully) other
[contributors](https://github.com/Theldus/sourcery/graphs/contributors).
