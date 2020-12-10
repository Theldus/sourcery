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

/* Predefined keywords and commons words. */
const char * const keywords_tbl[] =
{
	/* Types. */
	"double"  , "int"   , "long",
	"char"    , "float" , "short",
	"unsigned", "signed",

	/* Common typedefs. */
	"int8_t"  , "uint8_t"  ,
	"int16_t" , "uint16_t" ,
	"int32_t" , "uint32_t" ,
	"int64_t" , "uint64_t" ,

	"size_t", "ssize_t", "off_t",
	"int8_t", "NULL"   , /* Why not NULL?. */

	/* Other keywords. */
	"auto"  , "struct"  , "break"  ,
	"else"  , "switch"  , "case"   ,
	"enum"  , "register", "typedef",
	"extern", "return"  , "union"  ,
	"const" , "continue", "for"    ,
	"void"  , "default" , "goto"   ,
	"sizeof", "volatile", "do"     ,
	"if"    , "static"  , "while",

	/* Doxygen words. */
	"addindex",
	"addtogroup",
	"arg",
	"callergraph",
	"callgraph",
	"cond",
	"copybrief",
	"copydetails",
	"copydoc",
	"defgroup",
	"diafile",
	"dir",
	"docbookonly",
	"dontinclude",
	"dotfile",
	"elseif",
	"endcode",
	"endcond",
	"enddocbookonly",
	"enddot",
	"endif",
	"endinternal",
	"endlatexonly",
	"endlink",
	"endmanonly",
	"endmsc",
	"endparblock",
	"endrtfonly",
	"endsecreflist",
	"endverbatim",
	"enduml",
	"enum",
	"fn",
	"headerfile",
	"hidecallergraph",
	"hidecallgraph",
	"hiderefby",
	"hiderefs",
	"hideinitializer",
	"htmlinclude",
	"htmlonly",
	"idlexcept",
	"ifnot",
	"includedoc",
	"includelineno",
	"ingroup",
	"latexinclude",
	"latexonly",
	"li",
	"mainpage",
	"maninclude",
	"manonly",
	"memberof",
	"msc",
	"mscfile",
	"namespace",
	"nosubgrouping",
	"param",
	"parblock",
	"privatesection",
	"protectedsection",
	"publicsection",
	"refitem",
	"relatedalso",
	"relatesalso",
	"retval",
	"rtfinclude",
	"rtfonly",
	"sa",
	"secreflist",
	"showinitializer",
	"showrefby",
	"showrefs",
	"skipline",
	"snippetdoc",
	"snippetlineno",
	"startuml",
	"subpage",
	"subsubsection",
	"todo",
	"tparam",
	"verbinclude",
	"vhdlflow",
	"weakgroup",
	"xmlinclude",
	"xmlonly",
	"xrefitem",

	/* Format specifiers. */
	"hu",
	"ld",
	"li",
	"lu",
	"lx",
	"lf",
	"le",
	"lli",
	"lld",
	"llu",
	"llo",
	"llx",
	"hhd",
	"hhi",
	"hhu",
	"hho",
	"hhx",
	"jd",
	"ji",
	"ju",
	"jo",
	"jx",
	"zd",
	"zi",
	"zu",
	"zo",
	"zx",
	"td",
	"tu",
	"tx",
	"PRId",
	"PRId",
	"PRId",
	"PRId",
	"PRIdLEAST",
	"PRIdLEAST",
	"PRIdLEAST",
	"PRIdLEAST",
	"PRIdFAST",
	"PRIdFAST",
	"PRIdFAST",
	"PRIdFAST",
	"PRIi",
	"PRIi",
	"PRIi",
	"PRIi",
	"PRIiLEAST",
	"PRIiLEAST",
	"PRIiLEAST",
	"PRIiLEAST",
	"PRIiFAST",
	"PRIiFAST",
	"PRIiFAST",
	"PRIiFAST",
	"PRIo",
	"PRIo",
	"PRIo",
	"PRIo",
	"PRIoLEAST",
	"PRIoLEAST",
	"PRIoLEAST",
	"PRIoLEAST",
	"PRIoFAST",
	"PRIoFAST",
	"PRIoFAST",
	"PRIoFAST",
	"PRIu",
	"PRIu",
	"PRIu",
	"PRIu",
	"PRIuLEAST",
	"PRIuLEAST",
	"PRIuLEAST",
	"PRIuLEAST",
	"PRIuFAST",
	"PRIuFAST",
	"PRIuFAST",
	"PRIuFAST",
	"PRIx",
	"PRIx",
	"PRIx",
	"PRIx",
	"PRIxLEAST",
	"PRIxLEAST",
	"PRIxLEAST",
	"PRIxLEAST",
	"PRIxFAST",
	"PRIxFAST",
	"PRIxFAST",
	"PRIxFAST",
	"PRIX",
	"PRIX",
	"PRIX",
	"PRIX",
	"PRIXLEAST",
	"PRIXLEAST",
	"PRIXLEAST",
	"PRIXLEAST",
	"PRIXFAST",
	"PRIXFAST",
	"PRIXFAST",
	"PRIXFAST",
	"PRIdMAX",
	"PRIiMAX",
	"PRIoMAX",
	"PRIuMAX",
	"PRIxMAX",
	"PRIXMAX",
	"PRIdPTR",
	"PRIiPTR",
	"PRIoPTR",
	"PRIuPTR",
	"PRIxPTR",
	"PRIXPTR",
	"SCNd",
	"SCNdLEAST",
	"SCNdFAST",
	"SCNdFAST",
	"SCNdFAST",
	"SCNi",
	"SCNiLEAST",
	"SCNiFAST",
	"SCNiFAST",
	"SCNiFAST",
	"SCNu",
	"SCNuLEAST",
	"SCNuFAST",
	"SCNuFAST",
	"SCNuFAST",
	"SCNo",
	"SCNoLEAST",
	"SCNoFAST",
	"SCNoFAST",
	"SCNoFAST",
	"SCNx",
	"SCNxLEAST",
	"SCNxFAST",
	"SCNxFAST",
	"SCNxFAST",
	"SCNdMAX",
	"SCNiMAX",
	"SCNoMAX",
	"SCNuMAX",
	"SCNxMAX",
	"SCNdPTR",
	"SCNiPTR",
	"SCNoPTR",
	"SCNuPTR",
	"SCNxPTR",

	/* Common C functions. */
	"DTTOIF",
	"IFTODT",
	"WCOREDUMP",
	"WEXITSTATUS",
	"WIFEXITED",
	"WIFSIGNALED",
	"WIFSTOPPED",
	"WSTOPSIG",
	"WTERMSIG",
	"acos",
	"acosf",
	"acosfN",
	"acosfNx",
	"acosh",
	"acoshf",
	"acoshfN",
	"acoshfNx",
	"acoshl",
	"acosl",
	"addmntent",
	"addseverity",
	"adjtime",
	"adjtimex",
	"alloca",
	"alphasort",
	"alphasort",
	"asctime",
	"asin",
	"asinf",
	"asinfN",
	"asinfNx",
	"asinh",
	"asinhf",
	"asinhfN",
	"asinhfNx",
	"asinhl",
	"asinl",
	"asprintf",
	"atan",
	"atan",
	"atan",
	"atan",
	"fN",
	"atan",
	"fNx",
	"atan",
	"atanf",
	"atanfN",
	"atanfNx",
	"atanh",
	"atanhf",
	"atanhfN",
	"atanhfNx",
	"atanhl",
	"atanl",
	"atexit",
	"atof",
	"atoi",
	"atol",
	"backtrace",
	"basename",
	"bcmp",
	"bcopy",
	"brk",
	"bsearch",
	"btowc",
	"bzero",
	"cabsf",
	"cabsfN",
	"cabsfNx",
	"cabsl",
	"cacos",
	"cacosf",
	"cacosfN",
	"cacosfNx",
	"cacosh",
	"cacoshf",
	"cacoshfN",
	"cacoshfNx",
	"cacoshl",
	"cacosl",
	"calloc",
	"canonicalize",
	"canonicalizef",
	"canonicalizefN",
	"canonicalizefNx",
	"canonicalizel",
	"carg",
	"cargf",
	"cargfN",
	"cargfNx",
	"cargl",
	"casin",
	"casinf",
	"casinfN",
	"casinfNx",
	"casinh",
	"casinhf",
	"casinhfN",
	"casinhfNx",
	"casinhl",
	"casinl",
	"catan",
	"catanf",
	"catanfN",
	"catanfNx",
	"catanh",
	"catanhf",
	"catanhfN",
	"catanhfNx",
	"catanhl",
	"catanl",
	"catclose",
	"catgets",
	"catopen",
	"cbrt",
	"cbrtf",
	"cbrtfN",
	"cbrtfNx",
	"cbrtl",
	"ccos",
	"ccosf",
	"ccosfN",
	"ccosfNx",
	"ccosh",
	"ccoshf",
	"ccoshfN",
	"ccoshfNx",
	"ccoshl",
	"ccosl",
	"ceil",
	"ceilf",
	"ceilfN",
	"ceilfNx",
	"ceill",
	"cexp",
	"cexpf",
	"cexpfN",
	"cexpfNx",
	"cexpl",
	"cfgetispeed",
	"cfgetospeed",
	"cfmakeraw",
	"cfsetispeed",
	"cfsetospeed",
	"cfsetspeed",
	"chdir",
	"chmod",
	"chown",
	"cimag",
	"cimagf",
	"cimagfN",
	"cimagfNx",
	"cimagl",
	"clearenv",
	"clearerr",
	"fN",
	"fNx",
	"clogf",
	"clogfN",
	"clogfNx",
	"clogl",
	"closedir",
	"closelog",
	"confstr",
	"conjf",
	"conjfN",
	"conjfNx",
	"conjl",
	"copysign",
	"copysignf",
	"copysignfN",
	"copysignl",
	"cosf",
	"cosfN",
	"cosfNx",
	"coshf",
	"coshfN",
	"coshfNx",
	"coshl",
	"cosl",
	"cpow",
	"cpowf",
	"cpowfN",
	"cpowfNx",
	"cpowl",
	"cproj",
	"cprojf",
	"cprojfN",
	"cprojfNx",
	"cprojl",
	"creal",
	"crealf",
	"crealfN",
	"crealfNx",
	"creall",
	"creat",
	"creat",
	"csin",
	"csinf",
	"csinfN",
	"csinfNx",
	"csinh",
	"csinhf",
	"csinhfN",
	"csinhfNx",
	"csinhl",
	"csinl",
	"csqrt",
	"csqrtf",
	"csqrtfN",
	"csqrtfNx",
	"csqrtl",
	"ctan",
	"ctanf",
	"ctanfN",
	"ctanfNx",
	"ctanh",
	"ctanhf",
	"ctanhfN",
	"ctanhfNx",
	"ctanhl",
	"ctanl",
	"ctermid",
	"ctime",
	"cuserid",
	"daddl",
	"dcgettext",
	"dcngettext",
	"ddivl",
	"dgettext",
	"difftime",
	"dirfd",
	"dirname",
	"dmull",
	"dngettext",
	"drand",
	"drem",
	"dremf",
	"dreml",
	"dsubl",
	"dup",
	"dup",
	"ecvt",
	"endfsent",
	"endgrent",
	"endhostent",
	"endmntent",
	"endnetent",
	"endnetgrent",
	"endprotoent",
	"endpwent",
	"endservent",
	"endutent",
	"endutxent",
	"erand",
	"erf",
	"erfc",
	"erfcf",
	"erfcfN",
	"erfcfNx",
	"erfcl",
	"erff",
	"erffN",
	"erffNx",
	"erfl",
	"errx",
	"execl",
	"execle",
	"execlp",
	"execv",
	"execve",
	"execvp",
	"fN",
	"fNx",
	"fN",
	"fNx",
	"expf",
	"expfN",
	"expfNx",
	"expl",
	"expm",
	"expm",
	"expm",
	"fN",
	"expm",
	"fNx",
	"expm",
	"fMaddfN",
	"fMaddfNx",
	"fMdivfN",
	"fMmulfN",
	"fMmulfNx",
	"fMsubfN",
	"fMxaddfN",
	"fMxmulfN",
	"fabs",
	"fabsf",
	"fabsfN",
	"fabsfNx",
	"fabsl",
	"fadd",
	"faddl",
	"fchdir",
	"fchmod",
	"fchown",
	"fclose",
	"fcloseall",
	"fcntl",
	"fcvt",
	"fdatasync",
	"fdim",
	"fdimf",
	"fdimfN",
	"fdimfNx",
	"fdiml",
	"fdiv",
	"fdivl",
	"fdopen",
	"fdopendir",
	"fegetenv",
	"fegetmode",
	"fegetround",
	"feof",
	"feraiseexcept",
	"ferror",
	"fesetenv",
	"fesetmode",
	"fesetround",
	"feupdateenv",
	"fexecve",
	"fflush",
	"fgetc",
	"fgetgrent",
	"fgetpos",
	"fgetpos",
	"fgetpwent",
	"fgets",
	"fgetwc",
	"fgetws",
	"fileno",
	"finitef",
	"finitel",
	"flockfile",
	"floorf",
	"floorfN",
	"floorfNx",
	"floorl",
	"fma",
	"fmaf",
	"fmafN",
	"fmafNx",
	"fmal",
	"fmax",
	"fmaxf",
	"fmaxfN",
	"fmaxfNx",
	"fmaxl",
	"fmaxmag",
	"fmaxmagl",
	"fmemopen",
	"fmin",
	"fminf",
	"fminfN",
	"fminfNx",
	"fminl",
	"fminmag",
	"fminmagf",
	"fminmagfN",
	"fminmagl",
	"fmod",
	"fmodf",
	"fmodfN",
	"fmodfNx",
	"fmodl",
	"fmtmsg",
	"fmul",
	"fmull",
	"fnmatch",
	"fopen",
	"fopen",
	"fopencookie",
	"forkpty",
	"fpathconf",
	"fpclassify",
	"fprintf",
	"fputc",
	"fputs",
	"fputwc",
	"fputws",
	"fread",
	"freopen",
	"freopen",
	"frexp",
	"frexpf",
	"frexpfN",
	"frexpfNx",
	"frexpl",
	"fromfp",
	"fromfpf",
	"fromfpl",
	"fromfpx",
	"fscanf",
	"fseek",
	"fseeko",
	"fseeko",
	"fsetpos",
	"fsetpos",
	"fstat",
	"fstat",
	"fsub",
	"fsubl",
	"fsync",
	"ftell",
	"ftello",
	"ftello",
	"ftruncate",
	"ftruncate",
	"ftrylockfile",
	"ftw",
	"ftw",
	"funlockfile",
	"futimes",
	"fwide",
	"fwprintf",
	"fwrite",
	"fwscanf",
	"gammaf",
	"gammal",
	"gcvt",
	"getauxval",
	"getc",
	"getchar",
	"getcontext",
	"getcpu",
	"getcwd",
	"getdate",
	"getdelim",
	"getdents",
	"getdomainnname",
	"getegid",
	"getentropy",
	"getenv",
	"geteuid",
	"getfsent",
	"getfsfile",
	"getfsspec",
	"getgid",
	"getgrent",
	"getgrgid",
	"getgrnam",
	"getgrouplist",
	"getgroups",
	"gethostbyname",
	"gethostbyname",
	"gethostent",
	"gethostid",
	"gethostname",
	"getitimer",
	"getline",
	"getloadavg",
	"getlogin",
	"getmntent",
	"getnetbyname",
	"getnetent",
	"getnetgrent",
	"getopt",
	"getpagesize",
	"getpass",
	"getpayload",
	"getpayloadf",
	"getpayloadfN",
	"getpayloadl",
	"getpeername",
	"getpgid",
	"getpgrp",
	"getpid",
	"getppid",
	"getpriority",
	"getprotoent",
	"getpt",
	"getpwent",
	"getpwnam",
	"getpwuid",
	"getrandom",
	"getrlimit",
	"getrlimit",
	"getrusage",
	"getservbyname",
	"getservbyport",
	"getservent",
	"getsid",
	"getsockname",
	"getsockopt",
	"getsubopt",
	"gettext",
	"gettid",
	"gettimeofday",
	"getuid",
	"getumask",
	"getutent",
	"getutid",
	"getutline",
	"getutmp",
	"getutmpx",
	"getutxent",
	"getutxid",
	"getutxline",
	"getw",
	"getwc",
	"getwchar",
	"getwd",
	"globfree",
	"globfree",
	"gmtime",
	"grantpt",
	"gsignal",
	"gtty",
	"hasmntopt",
	"hcreate",
	"hdestroy",
	"hsearch",
	"htonl",
	"htons",
	"hypot",
	"hypotf",
	"hypotfN",
	"hypotfNx",
	"hypotl",
	"iconv",
	"ilogb",
	"ilogbf",
	"ilogbfN",
	"ilogbfNx",
	"ilogbl",
	"imaxabs",
	"imaxdiv",
	"initgroups",
	"initstate",
	"innetgr",
	"isalnum",
	"isalpha",
	"isascii",
	"isatty",
	"isblank",
	"iscanonical",
	"iscntrl",
	"isdigit",
	"iseqsig",
	"isfinite",
	"isgraph",
	"isgreater",
	"isgreaterequal",
	"isinf",
	"isinff",
	"isinfl",
	"isless",
	"islessequal",
	"islessgreater",
	"islower",
	"isnan",
	"isnanf",
	"isnanl",
	"isnormal",
	"isprint",
	"ispunct",
	"issignaling",
	"isspace",
	"issubnormal",
	"isunordered",
	"isupper",
	"iswalnum",
	"iswalpha",
	"iswblank",
	"iswcntrl",
	"iswctype",
	"iswdigit",
	"iswgraph",
	"iswlower",
	"iswprint",
	"iswpunct",
	"iswspace",
	"iswupper",
	"iswxdigit",
	"isxdigit",
	"iszero",
	"fN",
	"fNx",
	"fN",
	"fNx",
	"jn",
	"jnf",
	"jnfN",
	"jnfNx",
	"jnl",
	"jrand",
	"killpg",
	"lcong",
	"ldexp",
	"ldexpf",
	"ldexpfN",
	"ldexpl",
	"ldiv",
	"lfind",
	"lgamma",
	"lgammaf",
	"lgammafN",
	"lgammafNx",
	"lgammal",
	"linkat",
	"llabs",
	"lldiv",
	"llogb",
	"llogbf",
	"llogbfN",
	"llogbfNx",
	"llogbl",
	"llrint",
	"llrintf",
	"llrintfN",
	"llrintfNx",
	"llrintl",
	"llround",
	"llroundf",
	"llroundfN",
	"llroundfNx",
	"llroundl",
	"localeconv",
	"localtime",
	"fN",
	"fNx",
	"pfN",
	"pfNx",
	"fN",
	"fNx",
	"logb",
	"logbf",
	"logbfN",
	"logbfNx",
	"logbl",
	"logf",
	"logfN",
	"logfNx",
	"logl",
	"logwtmp",
	"longjmp",
	"lrand",
	"lrint",
	"lrintf",
	"lrintfN",
	"lrintfNx",
	"lrintl",
	"lround",
	"lroundf",
	"lroundfN",
	"lroundfNx",
	"lroundl",
	"lsearch",
	"lseek",
	"lseek",
	"lstat",
	"lstat",
	"lutimes",
	"madvise",
	"makecontext",
	"mallinfo",
	"malloc",
	"mallopt",
	"mblen",
	"mbrlen",
	"mbrtowc",
	"mbsinit",
	"mbsrtowcs",
	"mbstowcs",
	"mbtowc",
	"mcheck",
	"memalign",
	"memccpy",
	"memchr",
	"memcmp",
	"memcpy",
	"memfrob",
	"memmem",
	"memmove",
	"mempcpy",
	"memrchr",
	"memset",
	"mkdir",
	"mkdtemp",
	"mkfifo",
	"mknod",
	"mkstemp",
	"mktemp",
	"mktime",
	"mlock",
	"mlock",
	"mlockall",
	"mmap",
	"mmap",
	"modf",
	"modff",
	"modffN",
	"modffNx",
	"modfl",
	"mprobe",
	"mprotect",
	"mrand",
	"mremap",
	"msync",
	"mtrace",
	"munlock",
	"munlockall",
	"munmap",
	"muntrace",
	"nan",
	"nanf",
	"nanfN",
	"nanfNx",
	"nanl",
	"nanosleep",
	"nearbyint",
	"nearbyintf",
	"nearbyintfN",
	"nearbyintl",
	"nextafter",
	"nextafterf",
	"nextafterl",
	"nextdown",
	"nextdownf",
	"nextdownl",
	"nexttoward",
	"nexttowardf",
	"nexttowardl",
	"nextup",
	"nextupf",
	"nextupfN",
	"nextupl",
	"nftw",
	"nftw",
	"ngettext",
	"notfound",
	"nrand",
	"ntohl",
	"ntohs",
	"offsetof",
	"opendir",
	"openlog",
	"openpty",
	"pathconf",
	"pclose",
	"perror",
	"popen",
	"powf",
	"powfN",
	"powfNx",
	"powl",
	"pread",
	"pread",
	"preadv",
	"preadv",
	"preadv",
	"preadv",
	"printf",
	"psignal",
	"ptsname",
	"putc",
	"putchar",
	"putenv",
	"putpwent",
	"pututline",
	"pututxline",
	"putw",
	"putwc",
	"putwchar",
	"pwrite",
	"pwrite",
	"pwritev",
	"pwritev",
	"pwritev",
	"pwritev",
	"qecvt",
	"qfcvt",
	"qgcvt",
	"qsort",
	"rawmemchr",
	"readdir",
	"readdir",
	"readlink",
	"readv",
	"realloc",
	"reallocarray",
	"realpath",
	"recv",
	"recvfrom",
	"regcomp",
	"regerror",
	"regexec",
	"regfree",
	"remainderf",
	"remainderfN",
	"remainderfNx",
	"remainderl",
	"rewinddir",
	"rindex",
	"rint",
	"rintf",
	"rintfN",
	"rintfNx",
	"rintl",
	"rmdir",
	"roundeven",
	"roundevenf",
	"roundevenfN",
	"roundevenl",
	"roundf",
	"roundfN",
	"roundfNx",
	"roundl",
	"rpmatch",
	"sbrk",
	"scalb",
	"scalbf",
	"scalbl",
	"scalbln",
	"scalblnf",
	"scalblnl",
	"scalbn",
	"scalbnf",
	"scalbnfN",
	"scalbnl",
	"scandir",
	"scandir",
	"scanf",
	"seekdir",
	"semctl",
	"semget",
	"semop",
	"semtimedop",
	"sendto",
	"setbuf",
	"setbuffer",
	"setcontext",
	"setdomainname",
	"setegid",
	"setenv",
	"seteuid",
	"setfsent",
	"setgid",
	"setgrent",
	"setgroups",
	"sethostent",
	"sethostid",
	"sethostname",
	"setitimer",
	"setjmp",
	"setlinebuf",
	"setlocale",
	"setlogmask",
	"setmntent",
	"setnetent",
	"setnetgrent",
	"setpayload",
	"setpayloadf",
	"setpayloadfN",
	"setpayloadl",
	"setpayloadsig",
	"setpayloadsigf",
	"setpayloadsigl",
	"setpgid",
	"setpgrp",
	"setpriority",
	"setprotoent",
	"setpwent",
	"setregid",
	"setreuid",
	"setrlimit",
	"setrlimit",
	"setservent",
	"setsid",
	"setsockopt",
	"setstate",
	"settimeofday",
	"setuid",
	"setutent",
	"setutxent",
	"setvbuf",
	"sigaction",
	"sigaddset",
	"sigaltstack",
	"sigblock",
	"sigdelset",
	"sigemptyset",
	"sigfillset",
	"siginterrupt",
	"sigismember",
	"sigmask",
	"signbit",
	"significand",
	"significandf",
	"significandl",
	"sigpause",
	"sigpending",
	"sigsetjmp",
	"sigsetmask",
	"sigstack",
	"sigsuspend",
	"sincos",
	"sincosf",
	"sincosfN",
	"sincosfNx",
	"sincosl",
	"sinf",
	"sinfN",
	"sinfNx",
	"sinh",
	"sinhf",
	"sinhfN",
	"sinhfNx",
	"sinhl",
	"sinl",
	"snprintf",
	"socketpair",
	"sprintf",
	"sqrt",
	"sqrtf",
	"sqrtfN",
	"sqrtfNx",
	"sqrtl",
	"srand",
	"srand",
	"srandom",
	"sscanf",
	"ssignal",
	"stime",
	"stpcpy",
	"stpncpy",
	"strcasecmp",
	"strcasestr",
	"strcat",
	"strchr",
	"strchrnul",
	"strcmp",
	"strcoll",
	"strcpy",
	"strcspn",
	"strdup",
	"strdupa",
	"strerror",
	"strfmon",
	"strfromd",
	"strfromf",
	"strfroml",
	"strfry",
	"strftime",
	"strlen",
	"strncat",
	"strncmp",
	"strncpy",
	"strndup",
	"strndupa",
	"strnlen",
	"strpbrk",
	"strptime",
	"strrchr",
	"strsep",
	"strsignal",
	"strspn",
	"strstr",
	"strtod",
	"strtof",
	"strtofN",
	"strtofNx",
	"strtoimax",
	"strtok",
	"strtol",
	"strtold",
	"strtoll",
	"strtoq",
	"strtoul",
	"strtoull",
	"strtoumax",
	"strtouq",
	"strverscmp",
	"strxfrm",
	"stty",
	"swapcontext",
	"swprintf",
	"swscanf",
	"symlink",
	"syscall",
	"sysconf",
	"syslog",
	"tanf",
	"tanfN",
	"tanfNx",
	"tanh",
	"tanhf",
	"tanhfN",
	"tanhfNx",
	"tanhl",
	"tanl",
	"tcdrain",
	"tcflow",
	"tcflush",
	"tcgetattr",
	"tcgetsid",
	"tcsendbreak",
	"tcsetattr",
	"tdelete",
	"tdestroy",
	"telldir",
	"tempnam",
	"textdomain",
	"tfind",
	"tgamma",
	"tgammaf",
	"tgammafN",
	"tgammafNx",
	"tgammal",
	"tgkill",
	"timegm",
	"timelocal",
	"tmpfile",
	"tmpfile",
	"tmpnam",
	"toascii",
	"tolower",
	"totalorder",
	"totalorderf",
	"totalorderfN",
	"totalorderfNx",
	"totalorderl",
	"totalordermag",
	"totalordermagf",
	"totalordermagl",
	"toupper",
	"towctrans",
	"towlower",
	"towupper",
	"trunc",
	"truncf",
	"truncfN",
	"truncfNx",
	"truncl",
	"tryagain",
	"tsearch",
	"ttyname",
	"twalk",
	"tzset",
	"ufromfp",
	"ufromfpf",
	"ufromfpfN",
	"ufromfpl",
	"ufromfpx",
	"ulimit",
	"umask",
	"umount",
	"umount",
	"uname",
	"unavail",
	"ungetc",
	"ungetwc",
	"unlink",
	"unlockpt",
	"unsetenv",
	"updwtmp",
	"utime",
	"utimes",
	"utmpname",
	"utmpxname",
	"valloc",
	"vasprintf",
	"verr",
	"verrx",
	"versionsort",
	"versionsort",
	"vfork",
	"vfprintf",
	"vfscanf",
	"vfwprintf",
	"vfwscanf",
	"vlimit",
	"vprintf",
	"vscanf",
	"vsprintf",
	"vsscanf",
	"vswprintf",
	"vswscanf",
	"vsyslog",
	"vtimes",
	"vwarn",
	"vwarnx",
	"vwprintf",
	"vwscanf",
	"waitpid",
	"warnx",
	"wcpcpy",
	"wcpncpy",
	"wcrtomb",
	"wcscasecmp",
	"wcscat",
	"wcschr",
	"wcschrnul",
	"wcscmp",
	"wcscoll",
	"wcscpy",
	"wcscspn",
	"wcsdup",
	"wcsftime",
	"wcslen",
	"wcsncat",
	"wcsncmp",
	"wcsncpy",
	"wcsnlen",
	"wcspbrk",
	"wcsrchr",
	"wcsrtombs",
	"wcsspn",
	"wcsstr",
	"wcstod",
	"wcstof",
	"wcstofN",
	"wcstofNx",
	"wcstoimax",
	"wcstok",
	"wcstol",
	"wcstold",
	"wcstoll",
	"wcstombs",
	"wcstoq",
	"wcstoul",
	"wcstoull",
	"wcstoumax",
	"wcstouq",
	"wcswcs",
	"wcsxfrm",
	"wctob",
	"wctomb",
	"wctrans",
	"wctype",
	"wmemchr",
	"wmemcmp",
	"wmemcpy",
	"wmemmove",
	"wmempcpy",
	"wmemset",
	"wordexp",
	"wordfree",
	"wprintf",
	"writev",
	"wscanf",
	"CPU_CLR",
	"CPU_ISSET",
	"CPU_SET",
	"CPU_ZERO",
	"FD_CLR",
	"FD_ISSET",
	"FD_SET",
	"FD_ZERO",
	"SUN_LEN",
	"S_ISBLK",
	"S_ISCHR",
	"S_ISDIR",
	"S_ISFIFO",
	"S_ISLNK",
	"S_ISREG",
	"S_ISSOCK",
	"S_TYPEISMQ",
	"S_TYPEISSEM",
	"S_TYPEISSHM",
	"TEMP_FAILURE_RETRY",
	"_Exit",
	"__fbufsize",
	"__flbf",
	"__fpending",
	"__fpurge",
	"__freadable",
	"__freading",
	"__fsetlocking",
	"__fwritable",
	"__fwriting",
	"__va_copy",
	"_exit",
	"_flushlbf",
	"_tolower",
	"_toupper",
	"aio_cancel",
	"aio_cancel64",
	"aio_error",
	"aio_error64",
	"aio_fsync",
	"aio_fsync64",
	"aio_init",
	"aio_read",
	"aio_read64",
	"aio_return",
	"aio_return64",
	"aio_suspend",
	"aio_suspend64",
	"aio_write",
	"aio_write64",
	"aligned_alloc",
	"argp_error",
	"argp_failure",
	"argp_help",
	"argp_parse",
	"argp_state_help",
	"argp_usage",
	"argz_add",
	"argz_add_sep",
	"argz_append",
	"argz_count",
	"argz_create",
	"argz_create_sep",
	"argz_delete",
	"argz_extract",
	"argz_insert",
	"argz_next",
	"argz_replace",
	"argz_stringify",
	"asctime_r",
	"assert_perror",
	"backtrace_symbols",
	"backtrace_symbols_fd",
	"bind_textdomain_codeset",
	"call_once",
	"canonicalize_file_name",
	"clearerr_unlocked",
	"clock_getres",
	"clock_gettime",
	"clock_settime",
	"cnd_broadcast",
	"cnd_destroy",
	"cnd_init",
	"cnd_signal",
	"cnd_timedwait",
	"cnd_wait",
	"copy_file_range",
	"crypt_r",
	"ctime_r",
	"drand48_r",
	"ecvt_r",
	"envz_add",
	"envz_entry",
	"envz_get",
	"envz_merge",
	"envz_remove",
	"envz_strip",
	"erand48_r",
	"error_at_line",
	"explicit_bzero",
	"fcvt_r",
	"feof_unlocked",
	"ferror_unlocked",
	"fflush_unlocked",
	"fgetc_unlocked",
	"fgetgrent_r",
	"fgetpwent_r",
	"fgets_unlocked",
	"fgetwc_unlocked",
	"fgetws_unlocked",
	"fileno_unlocked",
	"fputc_unlocked",
	"fputs_unlocked",
	"fputwc_unlocked",
	"fputws_unlocked",
	"fread_unlocked",
	"fwrite_unlocked",
	"get_avphys_pages",
	"get_current_dir_name",
	"get_nprocs",
	"get_nprocs_conf",
	"get_phys_pages",
	"getc_unlocked",
	"getchar_unlocked",
	"getdate_r",
	"getgrent_r",
	"getgrgid_r",
	"getgrnam_r",
	"gethostbyaddr_r",
	"gethostbyname2_r",
	"gethostbyname_r",
	"getmntent_r",
	"getnetgrent_r",
	"getopt_long",
	"getopt_long_only",
	"getpwent_r",
	"getpwnam_r",
	"getpwuid_r",
	"getutent_r",
	"getutid_r",
	"getutline_r",
	"getwc_unlocked",
	"getwchar_unlocked",
	"gmtime_r",
	"hcreate_r",
	"hdestroy_r",
	"hsearch_r",
	"iconv_close",
	"iconv_open",
	"if_freenameindex",
	"if_indextoname",
	"if_nameindex",
	"if_nametoindex",
	"inet_addr",
	"inet_aton",
	"inet_lnaof",
	"inet_makeaddr",
	"inet_netof",
	"inet_network",
	"inet_ntoa",
	"inet_ntop",
	"inet_pton",
	"initstate_r",
	"jrand48_r",
	"lcong48_r",
	"lgamma_r",
	"lgammafN_r",
	"lgammafNx_r",
	"lgammaf_r",
	"lgammal_r",
	"lio_listio",
	"lio_listio64",
	"localtime_r",
	"login_tty",
	"lrand48_r",
	"memfd_create",
	"mrand48_r",
	"mtx_destroy",
	"mtx_init",
	"mtx_lock",
	"mtx_timedlock",
	"mtx_trylock",
	"mtx_unlock",
	"nl_langinfo",
	"nrand48_r",
	"ntp_adjtime",
	"ntp_gettime",
	"obstack_1grow",
	"obstack_1grow_fast",
	"obstack_alignment_mask",
	"obstack_alloc",
	"obstack_base",
	"obstack_blank",
	"obstack_blank_fast",
	"obstack_chunk_alloc",
	"obstack_chunk_free",
	"obstack_chunk_size",
	"obstack_copy",
	"obstack_copy0",
	"obstack_finish",
	"obstack_free",
	"obstack_grow",
	"obstack_grow0",
	"obstack_init",
	"obstack_int_grow",
	"obstack_int_grow_fast",
	"obstack_next_free",
	"obstack_object_size",
	"obstack_printf",
	"obstack_ptr_grow",
	"obstack_ptr_grow_fast",
	"obstack_room",
	"obstack_vprintf",
	"on_exit",
	"open_memstream",
	"parse_printf_format",
	"pkey_alloc",
	"pkey_free",
	"pkey_get",
	"pkey_mprotect",
	"pkey_set",
	"posix_fallocate",
	"posix_fallocate64",
	"posix_memalign",
	"printf_size",
	"printf_size_info",
	"pthread_atfork",
	"pthread_attr_destroy",
	"pthread_attr_getdetachstate",
	"pthread_attr_getinheritsched",
	"pthread_attr_getschedparam",
	"pthread_attr_getschedpolicy",
	"pthread_attr_getscope",
	"pthread_attr_getsigmask_np",
	"pthread_attr_init",
	"pthread_attr_setdetachstate",
	"pthread_attr_setinheritsched",
	"pthread_attr_setschedparam",
	"pthread_attr_setschedpolicy",
	"pthread_attr_setscope",
	"pthread_attr_setsigmask_np",
	"pthread_cancel",
	"pthread_cleanup_pop",
	"pthread_cleanup_pop_restore_np",
	"pthread_cleanup_push",
	"pthread_cleanup_push_defer_np",
	"pthread_clockjoin_np",
	"pthread_cond_broadcast",
	"pthread_cond_clockwait",
	"pthread_cond_destroy",
	"pthread_cond_init",
	"pthread_cond_signal",
	"pthread_cond_timedwait",
	"pthread_cond_wait",
	"pthread_condattr_destroy",
	"pthread_condattr_init",
	"pthread_create",
	"pthread_detach",
	"pthread_equal",
	"pthread_exit",
	"pthread_getattr_default_np",
	"pthread_getschedparam",
	"pthread_getspecific",
	"pthread_join",
	"pthread_key_create",
	"pthread_key_delete",
	"pthread_kill",
	"pthread_kill_other_threads_np",
	"pthread_mutex_destroy",
	"pthread_mutex_init",
	"pthread_mutex_lock",
	"pthread_mutex_trylock",
	"pthread_mutex_unlock",
	"pthread_mutexattr_destroy",
	"pthread_mutexattr_getkind_np",
	"pthread_mutexattr_init",
	"pthread_mutexattr_setkind_np",
	"pthread_once",
	"pthread_rwlock_clockrdlock",
	"pthread_rwlock_clockwrlock",
	"pthread_self",
	"pthread_setattr_default_np",
	"pthread_setcancelstate",
	"pthread_setcanceltype",
	"pthread_setschedparam",
	"pthread_setspecific",
	"pthread_sigmask",
	"pthread_testcancel",
	"pthread_timedjoin_np",
	"pthread_tryjoin_np",
	"ptsname_r",
	"putc_unlocked",
	"putchar_unlocked",
	"putwc_unlocked",
	"putwchar_unlocked",
	"qecvt_r",
	"qfcvt_r",
	"rand_r",
	"random_r",
	"readdir64_r",
	"readdir_r",
	"register_printf_function",
	"sched_get_priority_max",
	"sched_get_priority_min",
	"sched_getaffinity",
	"sched_getparam",
	"sched_getscheduler",
	"sched_rr_get_interval",
	"sched_setaffinity",
	"sched_setparam",
	"sched_setscheduler",
	"sched_yield",
	"secure_getenv",
	"seed48_r",
	"sem_clockwait",
	"sem_close",
	"sem_destroy",
	"sem_getvalue",
	"sem_init",
	"sem_open",
	"sem_post",
	"sem_timedwait",
	"sem_trywait",
	"sem_unlink",
	"sem_wait",
	"setstate_r",
	"shm_open",
	"shm_unlink",
	"sigabbrev_np",
	"sigdescr_np",
	"srand48_r",
	"srandom_r",
	"strerror_r",
	"strerrordesc_np",
	"strerrorname_np",
	"strtok_r",
	"sysv_signal",
	"thrd_create",
	"thrd_current",
	"thrd_detach",
	"thrd_equal",
	"thrd_exit",
	"thrd_join",
	"thrd_sleep",
	"thrd_yield",
	"tmpnam_r",
	"tss_create",
	"tss_delete",
	"tss_get",
	"tss_set",
	"ttyname_r",
	"twalk_r",
	"va_arg",
	"va_copy",
	"va_end",
	"va_start",

	/* Licenses. */
	"sublicense",
	"MERCHANTABILITY",
	"NONINFRINGEMENT",

	/* Email providers. */
	"gmail",
	"protonmail",
	"outlook",
	"hotmail",
	"yahoo",
	"zoho",
	"aol",
	"mail",
	"gmx",
	"icloud",
	"yandex",
};

/* Size. */
int keywords_tbl_len = sizeof(keywords_tbl)/sizeof(keywords_tbl[0]);
