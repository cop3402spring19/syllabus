## AST Nodes for Parsing

### Syntax-Directed Definition

    // declarations
    program      - TranslationUnit(block)
    block        - Block(vardecls, funcdecls, statement)
    vardecls     - TypedIdentList(TypedIdent(identfier, type), TypedIdent(identifer, type), ...)
    funcdelcs    - FuncDeclList(FuncDecl(identifier, formals, has_return, return_type, block), ...)
    formals      - TypedIdentList(TypedIdent(identfier, type), TypedIdent(identifer, type), ...)
    type         - Token

    // statements
    statement    - AssignStatement(assign_variable, assign_expression)
                 | CallStatement(call_function, call_parameters)
                 | ReturnStatement(return_expression)
                 | CompoundStatement(compound_statement)
                 | IfStatement(if_condition, if_branch, else_branch)
                 | WhileStatement(while_condition, while_statement)
                 | ReadStatement(read_variable)
                 | WriteStatement(write_expression)
    exprlist     - ExpressionList(expression, expression, ...)

    // expressions
    expr         - BinaryExpression(binary_op, binary_left, binary_right) or just passes through simpleexpr's return value
    simpleexpr   - BinaryExpression(binary_op, binary_left, binary_right) or just passes through term's return value
    term         - BinaryExpression(binary_op, binary_left, binary_right) or just passes through factor()'s return value
    factor       - VariableFactor(variable) for IDENT
                 | FunctionFactor(function_name, function_parameters) for 'IDENT LPAREN exprlist RPAREN'
                 | UnaryExpression(unary_op, unary_expression) for 'NOT factor' or 'MINUS factor'
                 | NumberFactor(number_value) for NUMBER
                 | BooleanFactor(boolean_value) for TRUE or FALSE

    // check token for type of operation
    is_relop        ::= bool
    is_termop       ::= bool
    is_factorop     ::= bool


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
