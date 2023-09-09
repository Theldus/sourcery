README
------
The file rev_wordlist.txt contains words from:

a) Linux kernel
Based from scripts/spelling.txt from the which has GPL-2.0 license.
Therefore, all files derived from it are also GPL-2.0, namely:
rev_wordlist.c and rev_hash_wordlist.c.

b) codespell/Wikipedia
It also contains words from the codespell project (another
spell-checker, made in Python). The words in it were derived
from the English Wikipedia and are licensed: CC BY-SA 3.0.

---

Please note that each source has its specific license, and if you
want to use Sourcery with rev_wordlist.txt, you need to bear them
in mind!, since each of them might have specific limitations and
requirements.

If these licenses are incompatible with your use-case, please do
a normal build, without reverse check, as in:
  $ make clean
  $ make


Note:
If you don't want me to use the above wordlists, please contact me
and I'll revert the commits.


Resource links:
- GPL-2.0: https://www.gnu.org/licenses/old-licenses/gpl-2.0.html.en

- CC-BY SA 3.0: https://creativecommons.org/licenses/by-sa/3.0/

- scripts/spelling.txt: https://github.com/torvalds/linux/blob/master
/scripts/spelling.txt

- dictionary.txt: https://github.com/codespell-project/codespell/blob
/master/codespell_lib/data/dictionary.txt
