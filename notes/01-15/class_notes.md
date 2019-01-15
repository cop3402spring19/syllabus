# Class Notes: 01/15/19  

Programming languages are human made languages: compiler takes human designed language and translates it into a language machine could run.  

We are going to learn how compiler works internally and build a compiler.  

Interpreter works differently. Directly takes the instructions and executes these instructions. In other words, evaluates the instructions and produces the output. Example interpreted programming languages: python, java.  

Hybrid compiler: both a compiler and an interpreter. Java is the classic example. Instead of your machine, it compiles to a virtual machine, which always has the same instruction set. Same exact compiler for every machine, which is the virtual machine. Each hardware needs its own virtual machine.  

We are going to follow the same strategy(hybrid compiler) for the project. We will write a compiler, then write a very simple virtual machine.  

Compiler has lots of pieces:
 - Front-end: lexer, parser, semantic analyzer.
 - Back-end: code generation, optimizer

Each of the compiling phases involves fundamentals of computer science such as tree traversal, recursion.  

PL0 is the programming language we are going to be developing a compiler for.  

syllabus/project folder contains bunch of files and a readme: documentation for the whole programming project. Documentation is in order of programming projects.  

Grammar is the descriptor of the syntax of the language. Take a look at grammar.md file, which specifies the grammar and the syntax of PL0.  

The grammar for PL0 is like English language. A written program yields a tree.  

Start the project by looking at the test cases. Each part of the project that you will code will have a different output. First step is to look at pl0 files to understand PL0 language.  

How do we know if `(5 * 2) / 7` evaluates to 1 or 1.42? For C, it will be 1. However, for PL0, what will it be? We need definition! Hence, the general answer is: depends on the language. The designers design what the language means. You could even use `q` for multiplication instead of `*` - although it would be less intuitive.. It depends on the convention the language use.  

In PL0, everything is an integer - no floating point numbers. The virtual machine will also only do integers. Hence, the PL0 statement `write (5 * 2) / 7` will write 1.  

Language C does not have boolean type. However, it is possible to have it with type definitions or importing some headers. Internally, booleans will be represented with 0 and non-zero values.  

The hardware does not directly support some concepts but the programming language does. Hence, we need compiler for the translation.  

In PL0, `write` just takes a number or expression.  

### How to run compiler and vm

Following command translates the PL0 program test.pl0 to machine code and writes out the machine code to standard output – you will see it on your terminal:  

```./compiler test.pl0```

Standard output redirection `>`: following will write the machine code to the file test.pcode:

```./compiler test.pl0 > test.pcode```

If you want to kill the debugging output, use `2> /dev/null`, so that, it will not be written on the terminal:  

```./compiler test.pl0 > test.pcode 2>/dev/null```

Following command runs the machine code test.pcode on the virtual machine – which you will code later:  
```./vm test.pcode 2>/dev/null```

In PL0, comments are done by using `#` 

### Compound statement

Example code with useful comments:  
```
# var nameofthevariable : typeofthevariable
var x : int

# begin BUNCH_OF_STATEMENTS end: compound statement
# if you want to use more than one statement, cover them in begin-end
begin

# Assignment. Not “=” but “:=”. Different than C
x := 7

# writes 7
write x

# end of compound list. Close “begin” by “end”
end
```

Block takes a single statement. If you want to use more than a single statement inside block, use compound statement: `begin BUNCH_OF_STATEMENTS end`

There are no strings in PL0.

Read variables by using `read`. It takes a single variable. Waits for the user to put the value to the standard input. Type the value, then, use ctrl+d: which means the input is over.  

Static scoping. We will learn about where variables are defined.  

`atoi()` function in C: converts string representation to integer representation. The character '1' is not the integer 1.  

Indentation is not important for pl0: just to read easier. We can ignore whitespace as a problem: will see in lexical analysis.  

No switch statements, goto statements, bitwise operations, semi-columns in PL0.  

`<>` means not equal, which is `!=` in C.

We will understand how recursion is implemented/simulated in this class. There is no explicit recursion in machine language.  

Equivalence between programming languages: Turing completeness. Programming languages are equally powerful.  

Function definitions could be either void or with type:  
 - `function f(x: int)` is void
 - `function f(x: int): bool` has return type boolean
 - `function f(x: int): int` has return type int

Technically, we can write infinitely many different programs.  

### Static scoping

```
var b : bool
var x : int
function f(x : int) : bool
  begin
    return x> 5
  end
begin
  # following assignment changes the value of global variable x
  x:=1
  # following call will set the variable x's value to 10 in function f
  write f(10)
end
```
We have two `x`s but they are different variables


### Nested scope

```
var b : bool
var x : int
function f(x : int) : bool
  function g(x : int) : int
    begin
      return x + 1
    end
  begin
    return g(x) > 5
  end
begin
  x := 4
  write f(5)
end
```

Trace the above program: the output is true because 6 > 5.  

Understanding nested functions is important. Lots of PL0 examples: have a look at nested.pl0.  

All of the declarations are at the top like C
