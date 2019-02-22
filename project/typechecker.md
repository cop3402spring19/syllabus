## Overview

In this project, you will be managing two pieces of state: the symbol
table and the AST annotations.  While traversing the tree, variable
and function declarations will have their symbols entered into the
symbol (`addVariable` and `addFunction`) and annotated on the tree
with their symbols (the return values of return values of
`addVariable` and `addFunction`).  These function's construct a
`DataType` struct automatically for you from the given AST subtree for
the declaration.  See `datatype.h` for the definitions.  Note the
fields for each kind of datatype, variables, tuples (lists of function
parameters), and function types (tuples for the parameters and the
return type), as these will be used later when actually checking that
types match.

Make sure you read `type_specification.md` carefully.  This defines
the typing rules of our language.

Start with the variable and function declarations and make sure the
symbol table output looks right.  When entering a function
declaration, add it to the `current_scope` before process its
children.  Make sure to first save the previous `current_scope` so
that you can restore it once you've typechecked all the function
declaration's children.

Then typecheck expressions.  For expression nodes, keep the invariant:
set each expression's `datatype` before returning.  This way, you can
use a postorder traversal to recursively check the entire expression
subtree.  Number and Boolean factors just set the `datatype` field and
that's it, since we know the types of these nodes.  Variable and
function factors require a table lookup.  Don't forget to set the
symbol annotations for these as well (look at ast.yml for the actual
field names).

Then typecheck statements.  The specification has more detail, but in
most cases, you will recursively typecheck whatever expressions the
statement uses, then check that the expressions are used
appropriately.

For the return statement, you need the current function's return type.
Get this by searching the symbol table for the function's name (taken
from the current scope) and looking in the parent scope (also taken
from the current_scope).  See `symtab.h` for the field names for
scopes.  Don't forget the set the symbol annotation fields (see
`ast.yml` for the field names.).

## AST Traversal

The type checker is using both pre- and post-order processing of the tree:

- declarations are preorder:

  - create symbol table entries as you encounter declarations
  - save/restore the scope as you enter/leave nested functions

- checking types is postorder:

    - move the type value up the tree via a post-order traversal (akin to expression evaluation)
    - expression tree leaves create types (axioms)
    - check types for binary/unary operations against the operator (inference rules)
    - check types for each expression used in statements

Use `printXXX` functions to help with debugging, e.g,

    printExpression(stderr, node, 0);  // 0 is the indent level

Be sure to set all the `datatype`, `symbol`, and `scope` fields.  See
ast.yml for which nodes have them.  These record symbol table entries
directly into the tree for use in code generation.

## AST Attributes for Type Checking

    TranslationUnit:
      scope: Scope
      
    FuncDecl:
      scope: Scope
      symbol: Symbol
      
    TypedIdent:
      symbol: Symbol

    AssignStatement:
      assign_symbol: Symbol
      
    CallStatement:
      call_symbol: Symbol
      
    ReturnStatement:
      function_symbol: Symbol
      
    ReadStatement:
      read_symbol: Symbol
          
    Expression:
      datatype: DataType
      ershov: int
      
    VariableFactor:
      variable_symbol: Symbol
      
    FunctionFactor:
      function_symbol: Symbol

## APIs

### Data Types

From datatype.h

`bool isPrimitiveType(struct DataType *datatype);` checks whether the type is a primitive type (not a function type)

`bool isFuncType(struct DataType *datatype);` checks whether the type is a function type.

`bool isInt(struct DataType *datatype);` checks whether the type is integer.

`bool isBool(struct DataType *datatype);` checks whether the type is boolean.

`bool equalTypes(struct DataType *a, struct DataType *b);` checks whether two types are equals or not.


### Symbol Table

From symtab.h

`struct Scope *addScope(char *name, struct Scope *parent);` adds a new scope given the parent scope.

`struct Scope *getParentScope(struct Scope *scope);`  returns NULL is scope is the global scope.

`struct Symbol *addVariable(struct Scope *scope, char *name, struct TypedIdent *node);`  return NULL if the symbol exists already.  this function takes the typedident subtree and automatically determines the type for you in the symbol table.  use the return value to annotate the tree with the symbol table.

`struct Symbol *addFunction(struct Scope *scope, char *name, struct FuncDecl *node)`  returns NULL if the symbol exists already.  this function takes the funcdecl subtree and automatically determines the type for you in the symbol table.  use the return value to annotate the tree with the symbol table.

`struct Symbol *searchSymbol(struct Scope *scope, char *name);`
recursively searches scopes starting from the current one.  Returns
NULL if no variable found even after reaching the global scope.

### Error handling

Call `type_error()` with one of the given error string macros.  See `visitUnaryExpression()` for an example.
