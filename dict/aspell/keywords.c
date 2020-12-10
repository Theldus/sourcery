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
};

/* Size. */
int keywords_tbl_len = sizeof(keywords_tbl)/sizeof(keywords_tbl[0]);
