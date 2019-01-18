lexer.c is the only file you need to edit for the first project  
each project you have only one file to edit (see them in overview.md)  
project/lexer.md: tips how to implement the lexer  
for all the project, you don’t need to use malloc at all. if you are doing that, you are doing harder than you need to do. but you still need to know how to deal with pointers.  
ask your questions on the discussion board (piazza)  
  
static scoping rules. global scope vs function scope  
in PL0, you only have global scope and function scope  
in PL0, you have nested functions  
instead of curly braces in C, we have other items of the programming language to define where the nesting happens  
  
```  
var b : bool  
var x : int  
function f(x:int): bool -> this x here is the local variable for f  
    function g(x:int): int -> this x here is the local variable for g  
        begin  
            return x + 1 -> g’s local variable x  
        end  
    begin  
        return g(x) > 5 -> f’s local variable x  
    end  
# main method  
begin  
    x:=4 -> under global scope  
    write f(5) -> we cannot call g function here, bacause it is nested inside f function, so we cannot use it globally  
end  
```  
  
g is not defined in global scope, hence, it cannot be called from main  
if we define a variable inside function f, we cannot use in main  
  
  
We can rename these global and local variables to make it less confusing  
  
```  
var b : bool  
var global_x : int  
function f(f_x:int): bool  
    function g(g_x:int): int  
        begin  
            return g_x + 1  
        end  
    begin  
        return g(f_x) > 5  
    end  
# main method  
begin  
    global_x:=4  
    write f(5)  
end  
```  
  
the order of declarations/definitions matters just like C (look at the grammar)  
  
pass a variable to a function will pass by value (not pass by reference)  
  
all white spaces are removed/ignored (you will see in lexer)  
  
we start running on main entrance point  
until you call a function, it does not get executed  
  
play with the syllabus/project/tests: lots of test cases and all outputs  
  
`3 + 3 + 2` is not allowed in PL0 : “parse error on PLUS”  
however, (3+3)+2 is allowed: will be 8  
you only have pairs of operations, you can't have multiple operations at the same precedence, you need to explicity give parenthesis: just to make the parsing easier  
  
## regular expressions  
what is regular expression?  
regular expression is a powerful tool for pattern matching  
it is like a simple programming language to search pattern in text  
we do use programming languages instead of assembly because it is easier for humans to understand, readable  
how to process this human-defined language? how to specify?  
thanks to compiler, we can write in language that human could understand. it translates it to a language that machine could understand  
in order to do that, we first define what a language is  
we need to find group of characters that makes sense to use  
so we need to find the words which match a pattern  
regular expressions are used in first part of the compiler: lexical analysis  
machine stores text as sequence of bytes. we need abstraction  
  
`od -x filename.txt` : how file is stored in machine level. 1’s and 0’s as hex. it is nothing but just a bunch of numbers.  
  
by lexical analysis, we pick out words. this is the stage where whitespace goes away. whitespace has no meaning for PL0  
lexer: transform from text to tokens (sequence of words)  
  
demo on regular expressions: `egrep -R "malloc"`: to search where malloc is called (space followed by malloc)  
also, we could search for calloc calls: `egrep -R "calloc"`  
some more fancy regular expression syntax, `egrep -R "(c|m)alloc`: look for c or look for m, then for alloc. it will bring both malloc and calloc  
`egrep -R "(c|m|xm)alloc"`: calloc, malloc,xmalloc  
`egrep -R "(m|xm)alloc"` : malloc, xmalloc  
examples: regular expressions could be used to find phone numbers or website urls  
  
lexeme is the sequence of characters: the actual strings in the language  
token is the name for this group of characters  
  
regular expressions to define number: `(0|1|2|3|4|5|6|7|8|9|0)`  
we can also find two digit numbers:  `(0|1|2|3|4|5|6|7|8|9|0)(0|1|2|3|4|5|6|7|8|9|0)`  
`egrep -R " (0|1|2|3|4|5|6|7|8|9|0)(0|1|2|3|4|5|6|7|8|9|0) "` : matches two digit numbers with whitespaces around  
  
in our lexer, we don't want to cover every possible number, we want to abstract, pack them as token: NUMBER  
  
formal languages are defined over a set of characters called alphabet (it could include any symbol, but finite set of symbols)  
a `string` over an alphabet is a finite sequence of symbols  
we also define empty strings: epsilon, a special symbol which means no character  
a language is a potentially infinite set over an alphabet  
numbers are technically infinite. the set of integers is infinite  
to define them, we use some operations: union, concatenation, kleene-closure, positive-closure  
languages are set of strings  
union -> this or that  
concatenation of two languages: for each set of strings, for each pair, we concatenate them  
kleene-closure: take language L and take every concatenation of language L: epsilon, L, LL, LLL…  
those three operations (union, concatenation, kleene-closure) are sufficient to define any regular languages  
  
  
E(sigma, alphabet) = { a, b }  
`a | b` : this language contains two strings. strings are: { a, b }  
  
`ab | b` : contains two strings. strings are: { ab, b }, equiliviant to saying `(ab) | b`  
  
`a (b | b)` : containts one string: { ab }  
  
`epsilon a epsilon`: one string { a }  
  
`epsilon | a` : { a }  
  
`a*` = { epsilon, a, aa, aaa, aaaa, …… }: infinite set of strings  
  
-----------  
  
`D = (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 )`  
define integers by using D:  
`D*` = zero or more D  = epsilon | D | DD | DDD | …..  
every possible sequence: { epsilon, 0, 1, 2, … , 9, 00, 01, 02, … }: inifinite  
  
-----------  
  
`DD` = | { 00, 01 .., 10, 11, .. 98, 99 } | = 100  
one digit followed by another digit. numbers from 00 to 99  
empty string is not contained in this set  
we cant match the empty string with regular expression `DD`  
  
  
-----------  
  
`DD` contains all two digit numbers. what if we want to define 1, 2, 3, ... so that we do not have the redundant digits  
  
`Z = (1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 )`  
  
`ZD` we have numbers from 10 to 99, without redundant leading 0s. 90 numbers. does not cover 1,2,3, .. 9  
  
------------  
  
`Z’` = (epsilon | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 )  
  
`Z’D` we have numbers from 0 to 99, without redundant leading 0s. 100 numbers.  
  
------------  
  
`DD | D`: we have 00, 01, 02, .., 09, 10, .. 99, 0, 1, 2, .., 9  
  
`ZD | D`: we have 10, 11, 12, .. 98, 99, 0, 1, 2, 3 .. , 9. so we have all 100 numbers from 0 to 99.  
  
------------  
  
no intersection operator in regular expression.   
  
Different notations:  
`[A- Z]` : { A, B, C, …, Y, Z }  
  
`[^0]`: all characters that are not zero  
  
------------  
  
`D*`: infinite set of digits = {0, 1, 2, .., 00, 01, … , 000, 001, … }  
  
`ZD* | 0`: infinite set of integers without leading 0s = {0 , 1 , 2 , … , 99, 100, .., 999, 1000, ... }  
00 is not in this language  
  
  
let’s define a new alphabet to define language including floating point numbers  
E = { 0-9, ‘.’ }  
  
floating point numbers: integer dot integer  
  
`(ZD* | 0) . (ZD* | 0)`: this does not cover floating numbers like 1.0001. we need leading zeros after period  
  
`( ZD* | 0 ) . D*` : all possible floating point numbers  
1.000 is a part of the language: design decision  
  
syllabus/project/grammar.md: we have lexical specification for project 1  
IDENT and NUMBER are simply regular expressions  
the format is EBNF, which is equilivant to regular expressions  
`{ }` : zero or more repetitions  
`[ ]` : optional
