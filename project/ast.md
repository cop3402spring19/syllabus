## AST Nodes for Parsing

### Declarations

    TranslationUnit:
      block: Block
      
    Block:
      vardecls: TypedIdentList
      funcdecls: FuncDeclList
      statement: Statement
      
    FuncDecl:
      identifier: string
      formals: TypedIdentList
      has_return: bool
      return_type: Token
      block: Block
      
    TypedIdent:
      identifier: string
      type: Token
      
    TypedIdentList: list
    
    FuncDeclList: list
    
### Statements

    StatementList: list
    
    Statement:
      union:
        AssignStatement
        CallStatement
        ReturnStatement
        CompoundStatement
        IfStatement
        WhileStatement
        ReadStatement
        WriteStatement
          
    AssignStatement:
      assign_variable: string
      assign_expression: Expression
      
    CallStatement:
      call_function: string
      call_parameters: ExpressionList
      
    ReturnStatement:
      return_expression: Expression
      
    CompoundStatement:
      compound_statement: StatementList
      
    IfStatement:
      if_condition: Expression
      if_branch: Statement
      if_elsebranch: Statement
      
    WhileStatement:
      while_condition: Expression
      while_body: Statement
      
    ReadStatement:
      read_variable: string
      
    WriteStatement:
      write_expression: Expression

### Statements

    ExpressionList: list
    
    Expression:
      union:
        BinaryExpression
        UnaryExpression
        NumberFactor
        BooleanFactor
        VariableFactor
        FunctionFactor
          
    BinaryExpression:
      binary_op: Token
      binary_left: Expression
      binary_right: Expression
      
    UnaryExpression:
      unary_op: Token
      unary_expression: Expression
      
    NumberFactor:
      number_value: int
      
    BooleanFactor:
      boolean_value: bool
      
    VariableFactor:
      variable: string
      
    FunctionFactor:
      function_name: string
      function_parameters: ExpressionList

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

## Union Nodes

Union nodes are tagged unions containing a `kind` field and a
anonymous union containing anonymous structs.

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


## List Nodes

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

