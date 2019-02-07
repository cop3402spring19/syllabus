# Grammar Specification

The following is the grammar specification for a variant of PL/0, specified in [EBNF notation](https://en.wikipedia.org/wiki/Extended_Backus%E2%80%93Naur_form).

The lexical specification defines the tokens of the language and their
respective lexemes.  The EBNF notation for each token is equivalent to
a regular expression.

The grammar defines the syntax of the language.  Tokens are
represented in all caps, e.g., IDENT.  The parser takes as input a
stream of tokens and produces an AST according to the grammar, with
tokens as the leaves of the tree.

## Grammar

    // EBNF notation tips
    lowercase symbols are nonterminals
    UPPERCASE symbols are terminals (tokens from your lexer)
    ::= denotes a production
    { } means 0 or more
    [ ] means 0 or 1
    ( ) just groups symbols
    
    // declarations
    program      ::= block
    block        ::= vardecls funcdecls statement
    vardecls     ::= { VAR IDENT COLON type }
    funcdelcs    ::= { FUNC IDENT LPAREN [ formals ] RPAREN [ COLON type ] block }
    formals      ::= IDENT COLON type { COMMA IDENT COLON type }
    type         ::= INT | BOOL

    // statements
    statement    ::= [ IDENT ASSIGN expr
                     | IDENT LPAREN exprlist RPAREN
                     | RETURN expr
                     | BEGIN { statement } END
                     | IF expr THEN statement [ELSE expr]
                     | WHILE expr DO statement
                     | READ IDENT
                     | WRITE expr
                     ]
    exprlist     ::= [ expr { COMMA expr } ]

    // expressions
    expr         ::= simpleexpr [ relop simpleexpr ]
    simpleexpr   ::= term [ termop term ]
    term         ::= factor [ factorop factor ]
    factor       ::= IDENT [ LPAREN exprlist RPAREN ] | NUMBER | TRUE | FALSE | LPAREN expr RPAREN | NOT factor | MINUS factor

    // operations at each precedence of the expression
    relop        ::= LT | LTE | GT | GTE | EQ | NEQ
    termop       ::= PLUS | MINUS | OR
    factorop     ::= MULT | DIV | MOD | AND

## Lexical Specification

    // reserved words
    VAR     ::= "var"
    FUNC    ::= "function"
    INT     ::= "int"
    BOOL    ::= "bool"
    RETURN  ::= "return"
    BEGIN   ::= "begin"
    END     ::= "end"
    IF      ::= "if"
    THEN    ::= "then"
    ELSE    ::= "else"
    WHILE   ::= "while"
    DO      ::= "do"
    READ    ::= "read"
    WRITE   ::= "write"
    TRUE    ::= "true"
    FALSE   ::= "false"
    OR      ::= "or"
    AND     ::= "and"
    NOT     ::= "not"

    // punctuation
    EQ      ::= "="
    COMMA   ::= ","
    COLON   ::= ":"
    ASSIGN  ::= ":="
    PLUS    ::= "+"
    MINUS   ::= "-"
    MULT    ::= "*"
    DIV     ::= "/"
    MOD     ::= "%"
    LPAREN  ::= "("
    RPAREN  ::= ")"
    LT      ::= "<"
    LTE     ::= "<="
    GT      ::= ">"
    GTE     ::= ">="
    NEQ     ::= "<>"

    // tokens with lexemes
    IDENT   ::= ( letter | "_" ) { ( letter | digit | "_" ) }
    NUMBER  ::= digit { digit }

    // language definitions for lexemes
    letter  ::= [A-Za-z]
    digit   ::= [0-9]

## Comments

Comments are indicated by a hash `#` symbol and extend from the symbol
to the end of the line.  Comments are implemented for you already.
