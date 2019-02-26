# Type Specification (Static Semantics)

## Declarations

Declarations notify the compiler about symbols used in the program and their type, i.e., their set of values and operations on their values.  The _scope_ of variable defines the region of the program in which the symbol is valid.  Our language has _static scoping_, also know as lexical scoping.  Static scoping in our language means that the region in which a symbol is valid corresponds to the region in which a function is defined and can be determined at compile-time.

- `vardecl` (TypedIdent) - add each variable to the current scope in the symbol table (addVariable)

- `funcdecl` (FuncDecl) - add each function to the current scope in the symbol table (addFunction), then create a new scope and visit the function's block.  Be sure to add the function to the current scope _before_ creating a new scope. Also, be sure to restore the state once the function is processed.

- `formals` (TypedIdent) - save each formal parameter's declaration node in the new scope created for the function.  Function parameters are local to the function.

## Expressions

- binary - the `binary_left` and `binary_right` expressions must be the same type.  The types of the expressions must also match the operation, `binary_op`.  The following shows the types of the operands for each operation as well as the resulting type of each operation.  The type notation, e.g., `(int, int) -> bool`, means the operation takes two integer parameters, enclosed in parentheses, and produces a Bool result, notated by an arrow followed by the resulting type.
  - `PLUS`, `MINUS`, `MULT`, `DIV`, `MOD` are `(int, int) -> int`
  - `LT`, `LTE`, `GT`, `GTE` are `(int, int) -> bool`
  - `AND` and `OR` are `(bool, bool) -> bool`
  - `EQ` and `NEQ` are `(a, a) -> bool`, i.e., both operands must be the same type `a` (integer or Boolean), while the result is always Boolean.
- unary - the `unary_expression` type must match the operation used, `unary_op`.  `MINUS` is `(int) -> int`, while `NOT` is `(bool) -> bool`
- number factors are defined to be the integer type
- Boolean factors are defined to be the Boolean type
- variable factors must be symbols defined as variables, i.e., primitive types, and not as functions.  The type of the variable factor expression is the declared type of the variable found by querying the symbol table (`searchSymbol`).
- function factors must be symbols defined as functions (`isFuncType`).   The type of the `function_parameters` must match the type of the formal arguments as the defined function found by querying the symbol table (`searchSymbol`).  The type of the function factor expression is the return type of the function declaration found.

### Ershov Numbering

(The dragon book, section 8.10 goes through this algorithm carefully.)

    static void visitExpression(struct Expression *node);

For each subtree, we compute how many registers are needed to avoid
storing intermediate results to memory.  This number is the Ershov
number.  It is computed via a tree traversal as follows:

- Leaves are 1, since they only need to store their own value
  (`NUMBERFACTOR`, `BOOLEANFACTOR`, `VARIABLEFACTOR`, and
  `FUNCTIONFACTOR`).
- An inner node with only one child (`UNARYEXPRESSION`) has the same
  number as the child.
- An inner node with two children (`BINARYEXPRESSION`) depends on the values of its children:
  - If both children have the same Ershov numbers, itgets the same
  number plus 1.
  - If the two children have different numbers, it gets the larger of
  the two.

Notes

- `FUNCTIONFACTOR` only has an Ershov number of 1.  This is because it
pushes any used registers onto the stack before evaluating the
function parameter expressions.)

## Statements

- assignment - type of `assign_variable` and `assign_expression` must match.
- call - `call_function` must be declared as a function and it's actual parameter types must match it's formal parameter types.  `call_function`'s return value may be any type; if it is not void, the return value wlil be ignore.
- return - type of `return_expression` must match the return type of the function containing the return statment. look up the `current_scope->name` in the parent scope to find the current function's return type.  you can get the function symbol's type with the `datatype` field and the return type from `datatype->return_type`.
- if - `if_expression` must be Boolean.
- while - `while_expression` must be Boolean.
- read - ensure that given symbol is a variable, i.e., a primitive type
- write - no restrictions on type.  Print whatever representation used by the VM for integers and Booleans.
