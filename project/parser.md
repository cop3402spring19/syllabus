## Parser

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

### Debugging

If the parser is hanging, you may have a while loop without a `next()`.

When you have a while loop, you have to use `next()` at the end in order for the test to check the next element, but once the while loop is done, call `previous()` to put the unneeded token back.

While there are many ways to write the same parser, I use this convenient invariant about the nonterminals' recursive descent functions:

  1. precondition, i.e., at its begnning, each recursive descent function needs to first call next() to "see" its first symbol
  2. postcondition, i.e., by the end of the function, each recursive descent function should not consume any tokens that aren't part of it's production. this means you may have to call previous() to restore a token (see the example for vardecls).

For lists - use _*List_, _new*List_, and _add*(*List...)_ (see pattern in vardecls).

Be sure to only use `next()` before calling `ensure_token()` or `is_token()`, NOT before calling another grammar nonterminal.  This preserve the invariants above.

Once the token is no longer what the nonterminal expects, e.g., in
vardecls when finding that next token is not `VAR`, push the token
back into the stream with `previous()`.


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
