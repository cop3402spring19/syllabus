## Parser

The job of the parser is two-fold:

1. check that the input program is valid according to the language's grammar
2. construct an abstract syntax tree (AST) representation of that program

These tasks are implemented simultaneously in the parsing functions.  Our parser is a predictive recursive descent parser.  This just means that (i) we implement each grammar production as a function, where the name is the nonterminal and the body is the production's right-hand side and (ii) we can look at the next token in the input to tell us what production we are matching, e.g., if we see a VAR we know we are in the vardecls production.

For validating according to the grammar, the parser takes a list of tokens from the lexer.  `next()` and `previous()` move a pointer forwards and backwards one token in this list.  The pointer is initially set to the space before the first token, i.e., `program` first calls `next()` to see the first token in the list.  I recommend tackling each parsing function largely individually.  Make sure the parsing is implemented correctly before constructing the AST.

For constructing the AST, look at the specification of it in ast.md.  This tells you, for each production, what AST node is constructed and what fields should be set.  As a general rule, each nonterminal is turned into an AST node, punctuation is not preserved on the AST, and { ... } productions are turned into lists.  Use any tokens encountered during parsing to populate the AST, e.g., the vardecl's identifier and the token from `type()` goes into the `TypedIdent` node. 

### AST Attributes for Type-Checking

Don't worry about the Symbol, Scope, DataType, and ershov attributes
on the AST, as these are for later typechecking and code generation
phases.  The AST printer will not display these after parsing.

### Expression Limitations

The expression grammar is limited for simplicity of parsing.  For instance,

    5 * 2 * 7
    
yields a parse error.  Instead, it can be written as

    (5 * 2) * 7

This is because the expression productions only permit a single
expression on either side of the operator.  It is left as an optional
exercise to extend the grammar and parser to accept such expressions.
The AST need not change.

### Precondition and Postcondition Invariants

While there are many ways to write the same parser, I use this convenient invariant about the nonterminals' recursive descent functions:

  1. precondition, i.e., at its begnning, each recursive descent function needs to first call next() to "see" its first symbol
  2. postcondition, i.e., by the end of the function, each recursive descent function should not consume any tokens that aren't part of it's production. this means you may have to call previous() to restore a token (see the example for vardecls).

For lists - use _*List_, _new*List_, and _add*(*List...)_ (see pattern in vardecls).

Be sure to only use `next()` before calling `ensure_token()` or `is_token()`, NOT before calling another grammar nonterminal.  This preserve the invariants above.

Once the token is no longer what the nonterminal expects, e.g., in
vardecls when finding that next token is not `VAR`, push the token
back into the stream with `previous()`.

### Debugging

If the parser is hanging, you may have a while loop without a `next()`.

When you have a while loop, you have to use `next()` at the end in order for the test to check the next element, but once the while loop is done, call `previous()` to put the unneeded token back.

If you get a segfault, check whether this is during AST printing, rather than parsing.  If so, this means your parser has not yet completed constructing the AST node that still contains a NULL.

A parse error on token likely means you are advancing the tokens too far.  Double-check that the invariants are met, i.e., when you finish parsing a production, you are on the last token of that production (or the previous token if it was empty).  Confirm this using `print_token(stdout, token());`.  There is a chance it means you have not advanced the tokens, i.e., a parsing function is incomplete.

Don't be afraid to write your own test cases.  In fact, I strongly encourage it, as it is good practice.  Try to write small test cases that exercise just the suspicious or unfinished portion of code.  Trace through the code by hand to make sure it does what you want it to do.  Use `printf` to confirm or investigate.

Remember: the AST is _abstract_.  it is not an exact parse tree.  The
names of the grammar nonterminals need not be the same as the AST
nodes.  The AST nodes may have different names and removes unnecessary
details of the grammar, e.g., operator precedence encoded in grammar
and punctuation.

For actuals, look at how formals are treated, but use ExpressionList instead.

For procdecls, look at vardecls.  It is more complicated, since you
have to parse `formals()` and check whether `COLON` and type are given
for that particular function.

To figure out where a parse error happened, get the stack trace with gdb (the Makefile compiles with `-g` by default):

    gdb compiler
    # inside  gdb
    # break on exit
    break exit
    # run in
    r --parse fib.pl0
    # get stack trace (backtrace)
    bt

Be sure to return the created node from each nonterminal function so
that the child node can be added to the parent node.

### Error handling

Use `ensure_token()` to check that the current token is what is
expected.  It will automatically throw a parse error.  See `program()` and `vardecls()` for examples.  

Call `parse_error()` if an unexpected token is found.  See `type()`
for an example of using it in conjunction with `is_token()` to check
for the correct tokens.
