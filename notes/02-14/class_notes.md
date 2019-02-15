We finished parsing  

If you couldn’t do a part of the project, use late submission: try to have it complete at the end of the term  
Next week we will have Q&A on debugging  

While implementing a function, focus on that part, implement that part, assume that the remaining is complete. It makes programming much easier.  

Today, we will talk about typechecking  

Lexer: stream of characters -> stream of tokens  
Parser: stream of tokens -> tree structure, which presents the grammatical structure of the language  

```
function f(x: int)
    begin
        x := x + 1
    end
write 2 + f
```

The above program is grammaticaly and syntactically correct: parser does not complain about anything  
However, what does this program mean? What is the semantics?  
What is the value of f? What does it mean to have f that there?  
`write 2 + f` is meaningless  
Even `write 2 + f(2)` is meaningless since f does not return anything  
This should not be a legal program  

Plus operator is only for integers  
Typechecking does the restrictions and checks programs against these rules  

The errors sometimes are syntactic for instance missing `;` and sometimes are semantic errors which are like you are not allowed to add boolean and integer.  

You cannot add strings and integers with booleans..  
With the typesystem, we enforce meanings to symbols (ex: `+` does addition of integers)  
Typechecker takes the semantics we define and enforces that semantics on the program  
For example, it guarantees that the only legal programs that compiler allow are that plus symbol is used on integers  
Types of errors can vary: syntax error, semantics error. Here, we catch semantics errors  

Grammar has no distinction on types, therefore, checks done with parser are not enough to check semantics  
Typechecks rules out any illegal usage according to our type specification  

Why use types?  
We use types to prevent errors during runtime  

A type can be defined as a set of values and operations on those values  

Untyped languages to do that check: LISP, assembly..  
Runtime errors could be:  
 - Trapped: caught and terminated by machine  
 - Untrapped: Program continues, that won’t halt the program. You will have some undefined behivour because of that error.  

You could do both static and dynamic checking. Examples: C does at compile time (static) and Python does at run time (dynamic). In python you don’t need to declare the variable types.  

Weakly typed vs strongly typed  
Strongly checked: all legal programs have good behaviour  
Weakly checked: Some programs may violate safety (C is weakly typed)  

Floating point numbers are represented different than integers in the machine  
Floating point numbers have precision problems  

Floating point addition and integer addition are different things although the same symbol `+` is used  


`10 * ( float(1)/10 + float(2)/10 )` outputs 3.00000004  
`10 * ( 1/10 + 2/10 )` outputs 0  

`10(1/10 + 2/10)`  
TypeError: int is not callable.  
You cannot do function call on a variable.  

Symbol table will keep these information about symbols and their types.  

We will implement a static type checker  
While traversing the AST, we will make sure that operations are used the way they are supposed to be.  

Typechecker is post order tree traversal of the AST of any program  

```
        BinaryExpression
        /     |         \
NumFactor     +       VarFactor
   2                      f
```

Remember the above piece of code. Using our symbol table, we will check the type of VarFactor f. It is a function, hence, error! (integer + function is not vaid)  

```
        BinaryExpression
        /     |         \
NumFactor     +       VarFactor
   2                      x
```
Say that x is a variable of type integer. Above AST will be valid.  


(int, int) -> int means that + is a function that takes two integers and returns an integer  

Homework of next week will have questions related to typechecking  

In C, compiler inserts invisible casts for operations between integers and floats.  
All code examples are on github repo.  

By using pointers in C, we can trick the program to interpret a floating point number as integer without doing a cast operation (see unsafe.c example on repo)  

How do we specify the type behaviour formally?  
We can use mathematical expressions to formally specify type.  

Type soundness: If it passes all of the checks, it is true that the program is type safe.  
C typechecker is unsound while Java typechecker is sound  

Symbol tables are used for storing types  
Check syllabus/project/typechecker.md  

We have static scoping in our language.   
Whenever you have a function, you can define your local variables that you can use only in that scope.  
Scope is literally seeing: where you can see that variable  
Hardware does not know anything about scopes: it is language design problem which can be handled differently.  

```
function f(x: int) : int
    begin
        return x + 1
    end
write 2 + f(2)
```

Above program prints 5. We will see how typechecking is done by using that example.  

Check: [typechecker_ast_traversal.pdf](typechecker_ast_traversal.pdf)  

Typechecker uses two pieces of data: symbol table and AST  
Symbol table keeps track of: name, type and scope of the symbols  

We have helper functions in the project for creating type field of a symbol  
There is a global variable called currentScope. When we start program, it will be initialized to GLOBAL. Our program will have GLOBAL scope at beginning.  
You should save the scope of a symbol by using the currentScope. This will allow us to implement static scoping.  
Everytime we see a function, we will create a new scope. Notice that functions are under a scope and have their own scopes.  
You can think formals as the local variables of the scope we are inside.  
Given the current scope and name of the variable, we can do a lookup using the symbol table.  

You are given the possible type errors. You will figure out which type error to use where.  

You can think of + as a function defined globally, which takes two integers and returns an integer. Not in symbol table. Hardcoded.  

For return statements inside functions, we check if the child of the node "return" is compatible with the return type of the function  

Implementing typechecker is easier than doing the parsing  

Just like the parser, you have a function for each of the AST nodes  
visitASTNODENAME(). Examples: visitTranslationUnity(), visitFunctionFactor() etc.  
Look at the code on your own - API is given and some of the parts are already implemented  
getSymbol and checkSymbole to work with symbol table.  

If you cannot find the variable in the symbol table, it is an error. If the type of variable doesn’t match, it is an error.  

Check typechecker.md to get to know the API and how to use it: addVariable(), addFunction() etc.  

typespecifications.md: The type specifications of the language PL0  
typechecker.md: The explanation of all the function you will need  

Typechecker’s output:  
- Symbol table  
- The AST where scope and symbol fields are filled. These will make the code generation step easier: we won’t need to do any other lookups but will use these fields  
OR
- Type error  

Ershov numbering is useful for code generation. We will talk about it the next time.  
