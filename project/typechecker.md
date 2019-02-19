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


### Union Nodes

Union nodes are tagged unions containing a `kind` field and a
anonymous union containing anonymous structs.  The following is an example of the union fields will be accessed during the codegen phase of the compiler.

    static void visitStatement(struct Statement *node) {
      // given
      switch (node->kind) {
      case ASSIGNSTATEMENT:
        visitAssignStatement(node);
      // etc
    }

    static void visitAssignStatement(struct Statement *node) {
      struct Symbol *symbol = node->assign_symbol;
      int assigned_reg = visitExpression(node->assign_expression, 0);

      setVariable(symbol, assigned_reg);
    }


### List Nodes

List nodes have `head` and `tail` fields that point to elements
containing `node` and `next` fields.

For instance, to traverse a TypedIdentList, use the following code:

    static void visitVarDecls(struct TypedIdentList *list) {
      struct TypedIdentListElement *cur = list->head;
      while (NULL != cur) {
        visitVarDecl(cur->node);
        cur = cur->next;
      }
    }


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

`struct Symbol *addVariable(struct Scope *scope, char *name, struct TypedIdent *node);`  return NULL if the symbol exists already.

`struct Symbol *addFunction(struct Scope *scope, char *name, struct FuncDecl *node)`  returns NULL if the symbol exists already.

`struct Symbol *searchSymbol(struct Scope *scope, char *name);`
recursively searches scopes starting from the current one.  Returns
NULL if no variable found even after reaching the global scope.

### Error handling

Call `type_error()` with one of the given error string macros.  See `visitUnaryExpression()` for an example.
