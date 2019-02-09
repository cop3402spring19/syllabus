# Overview

## Command-Line Usage

    compiler --lex       file.pl0 > file.tokens
    compiler --parse     file.pl0 > file.ast
    compiler --typecheck file.pl0 > file.types
    compiler             file.pl0 > file.pcode

    vm file.pcode < file.vmin > file.vmout 2> file.vmtrace

## Example Usage

First build your project

    cd /path/to/your/project
    make

This will run the lexer

    ./compiler --lex /path/to/syllabus/project/tests/fib_series.pl0 > fib_series.tokens

This will run the parser

    ./compiler --parse /path/to/syllabus/project/tests/fib_series.pl0 > fib_series.ast
    # to also save parser errors that go to stderr do this
    ./compiler --parse /path/to/syllabus/project/tests/fib_series.pl0 > fib_series.ast 2>&1

This will run the typechecker

    ./compiler --typecheck /path/to/syllabus/project/tests/fib_series.pl0 > fib_series.types

This will run the code generator

    ./compiler /path/to/syllabus/project/tests/fib_series.pl0 > fib_series.pcode

This will run the vm (after running your code generation step)

    ./vm fib_series.pcode > fib_series.vmout 2> fib_series.vmtrace

This will compile and run the fibonacci series program:

    ./compiler /path/to/syllabus/project/tests/fib_series.pl0 > fib_series.pcode
    ./vm fib_series.pcode

To prevent the VM from printing out the state, redirect to `/dev/null`:

    ./vm fib_series.pcode 2>/dev/null

To enter number when prompted by a `read`, e.g., in the following:

    ./compiler /path/to/syllabus/project/tests/fib.pl0 > fib.pcode
    ./vm fib.pcode 2>/dev/null

`vm` will wait for user input.  Enter a number and then hit `Ctrl-D`
to send the input to `vm`.

You can also redirect the input from a file:

    ./vm fib.pcode 2>/dev/null < /path/to/syllabus/project/tests/fib.vmin

### Programming Assignment Skeletons

    lexer.c - project 1
    parser.c - project 2
    typechecker.c - project 3
    vm_impl.c - project 4
    codegen.c - project 5 and 6

Search for `TODO`s in the source files for hints on completing the
projects.

Type `make` to compile your program.

## Using Given Object Files for Previous Phases

Later projects depend on earlier projects, e.g., a correct parser
depends on a correct lexer.  `binaries.tar` contains the fully
implemented compiler, with its compilation units.  To use an existing
implementation of a phase, do the following, filling in the paths on
your own machine.  First extract the binaries:

    cd PATH/TO/BINARIES
    tar -xvf binaries.tar

Then go to your own project an copy whichever phases you'd like to
use.  For instance, if you are working on the type checker, copy over
the lexer and parser:

    cd PATH/TO/PROJECT
    make
    cp PATH/TO/BINARIES/{lexer,parser}.o ./
    make

The output of the second `make` should show the compiler running
again.

You will be graded only on your `.c` source code files.  Be sure to
avoid accidentally copying the compiler phase you are currently
working on, which could lead you to believe your code is correct.
Note that any changes to the source code of a previous phase will
overwrite the copied binary.  Recopy the binary in case this happens.

## Input/Output File Types

    .pl0 - PL/0 source code
    .tokens - tokenized PL/0 source code
    .ast - abstract syntax tree of PL/0 source code
    .types - type checker report
    .pcode - p-code
    .vmin - vm input
    .vmout - vm output
    .vmtrace - vm debugging output

## Documentation

View `doc/html/annotated.html` in a browser to see diagrams of all the
data structures used in the project.

## Source Files

    ast.{c,h} AST library
    ast.py - AST library generatory
    ast.yml - AST description file
    codegen.{h,c} - code generation phase
    codegen_tools.c - supporting functions for code generator
    compiler.c - compiler main program
    datatype.{c,h} - library for representing data types
    lexer.{c,h} - lexer phase files
    lexer_reserved.{gperf,c} - hash table for reserved words
    Makefile - builds the compiler and vm, generating files as eneded
    parser.{c,h} - the parsing phase
    parser_tools.c - supporting functions for parsing
    symtab.{c,h} - symbol table data structures and library
    token.{c,h} - token data structures and library
    typechecker.{c,h} - type checking phase
    typechecker_tools.c - supporting functions for type checking
    vm_main.c - vm main program
    vm.h - vm declarations
    vm_impl.c - vm implementation
    vm_ops.{c,gperf} - hash table of vm op names
