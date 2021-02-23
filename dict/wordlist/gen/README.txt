README
------
The file rev_wordlist.txt was based from scripts/spelling.txt from the
Linux kernel, which has GPL-2.0 license. Therefore, all files derived
from it are also GPL-2.0, namely: rev_wordlist.c and rev_hash_wordlist.c.

If you want to use Sourcery in something gpl-incompatible, please compile
_without_ reverse checking support, i.e. without: "make CHECK=reverse".
Sourcery by default _does not_ use reverse checking.

A careful eye should note that license header has been removed, since
gen.c does not support comments on parsing. This README serves as a
substitute for this and also as an alert to the implications of the
license.

If this approach is not correct or appropriate, please let me know.

The original spelling.txt header follows below:

# Originally from Debian's Lintian tool. Various false positives have been
# removed, and various additions have been made as they've been discovered
# in the kernel source.
#
# License: GPLv2
#
# The format of each line is:
# mistake||correction
#
