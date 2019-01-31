Today, we will talk about how to go from string to a parse tree that matches with a language.  
Then, we will talk about how to write and run a program to do matching.  

Reminder: Lexer takes a stream of characters, turns them into stream of tokens, which are words in our language (PL0).  
Regular languages are not enough to capture structural aspect of languages. Therefore, we use context free languages.  

Syntax analyzer takes a stream of tokens from the lexer and produces a parse tree.  
Given some grammar, a parser is supposed to take a string and check if it matches the grammar.  

A context free grammar is defined by:  
- terminals: can’t be broken down anymore, terminate the expression of the grammar  
- non-terminals: everything on the left hand side of the productions, can be broken down into smaller pieces  
- productions: non-terminals on the left hand side, some list of terminals and non-terminals. the rules of the language. describes how to break down the non-terminals into pieces. denoted by `->`  
- starting symbol  

There are different kinds of notations for context free grammars. You could figure out the notation if you know the four things written above. 

You can prove that any regular language is also context-free language. There is a mapping between regular languages and context free languages (the mapping from regular expression operations (concat, union, closure) to context free grammar operations.)

Analogy: linked-lists and trees.  
All linked lists are trees where each node has one child only.  
However, not every trees are linked-lists.  

Conversion from regular expression to context free grammar:  
Concatenation `ab`: `A -> a b`  
Union `a | b`:  
```A -> a
A -> b```  
Closure `a*`:
`A->Aa`  
`A->epsilon` (it cannot be `A->a` because `*` means zero or more)  

If you write a valid C program, it is just one string included in the C language.  
Ambiguity is property of the grammar. It means that there exists some string that you can have more than one derivation (parse tree).  
In other words, if you have more than one parse tree for the same string, the grammar is ambiguous.  
Ambiguity is not inherent from languages. It is a design choice. It depends on the grammar itself.  
For example, FORTRAN will work like a desk calculator while evaluating expressions: design choice (while evaluating `id+id*id`, it will first do addition, then multiplication). It is just a human-designed language.  

For modern programming languages, we have other precedence rules.  

__Example (an unambiguous grammar):__  
```
E -> E + T
E -> T
T -> T * F
T -> F
F -> 0 | 1
```  








__String__: `1 + 0 * 1`  

__Parse tree__:
```
           E
       /   |   \
     E      +   T
   /         /  |  \
 T           T  *   F
 |           |      |
 F           F      1
 |           |
1            0
```

We will write an algorithm to do creation of parse tree automatically, which compilers do.  

The grammar just describes the syntax.  

Recognizers: Tells if a string is a part of the language or not.  
Parsers: Constructs some tree out of a string. Also recognizes it.  

Two types of parsers: top-down or bottom-up  
Top-down: Start from starting symbol (tricky, you can’t see the future)  
Bottom-up: Start from the terminals of the language, try to figure out what productions are applied up to the root.  

Top-down parsing algorithms:  
- Recursive descent (just takes the grammar and converts it to a set of recursive functions)  
- Table-driven top-down parsing (we are not going to cover this much)  


Recursive descent
Each non-terminals is a function.
Each terminal of the language matches an input character (or, input token)
Productions are the bodies of the functions (non-terminal functions)
The problem: left-most recursion  
```
E -> E + T | T
T -> T * F | F
T -> 0 | 1
```  
If we convert the above grammar into functions, we end up infinite recursion! `(E -> E.. )`  

To resolve this issue, we can rewrite the grammar (left recursion elimination or left factoring).  

Another grammar that recognizes the exactly same language:  
```
E  -> T E’
E’ -> + T E’ | epsilon
T  -> F T’
T’ -> * F T’ | epsilon
F  -> 0 | 1
```
Having right recursion is okay, but left recursion is dangerous(possibly infinite recursion).  

Parse tree for string `1 + 0 * 1` with the new grammar:  
```
            E
         /        \
       T           E’
    /  |       /   |    \
   F   T’    +     T     E’
  |    |           |  \    \
 1    eps          F   T’   eps
                  /  / | \  
                 0  *  F  T’
                       |    \
                       1    eps
```  

There are engineering trade-offs to use different algorithms
Recursive descent is more easy and will make you practice tree traversal and recursion  

In this class, we are going to use predictive parsing  
Backtracking is expensive while predictive parsing is linear time  

__Writing a recursive descent parser__:  

For each non-terminal, you create a function.  
If we have two options for the production of that terminal we have to check the next character of the input string.  
Don’t forget to consume the character!  
It is better to have the tree to have a better sense about the traversal.  
If you see the trace of function calls it will be just like the trees. If you understand tree traversal, you will understand recursion easier.  

__The output of parser example from class__:  
!(parser_example.png)[parser_example.png]  

`assert()` function in C: it terminates the program if the given parameter is false (0).  

If you look at grammar.md, the grammar for PL0 is written in EBNF format. It is basically context free grammar + regular expressions.  
`{ }` means zero or more  
`[ ]` means optional (zero or one)  

The skeleton code is given for the parser assignment.  
