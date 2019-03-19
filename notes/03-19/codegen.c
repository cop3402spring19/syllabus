#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <error.h>
#include <assert.h>

#include "ast.h"
#include "symtab.h"
#include "codegen.h"
#include "vm_types.h"

// declarations
static void visitTranslationUnit(struct TranslationUnit *node);
static void visitBlock(struct Block *node);
static void visitVarDecls(struct TypedIdentList *list);
static void visitFuncDecls(struct FuncDeclList *list);
static void visitFuncDecl(struct FuncDecl *node);
static void visitFormals(struct TypedIdentList *list);

// statements
static void visitStatement(struct Statement *node);
static void visitAssignStatement(struct Statement *node);
static void visitCallStatement(struct Statement *node);
static void visitReturnStatement(struct Statement *node);
static void visitCompoundStatement(struct Statement *list);
static void visitIfStatement(struct Statement *node);
static void visitWhileStatement(struct Statement *node);
static void visitReadStatement(struct Statement *node);
static void visitWriteStatement(struct Statement *node);

// expressions
static int visitExpression(struct Expression *node, int reg_base);
static int visitBinaryExpressionInt(struct Expression *node, int reg_base);
static int visitUnaryExpressionInt(struct Expression *node, int reg_base);
static int visitBinaryExpressionBool(struct Expression *node, int reg_base);
static int visitUnaryExpressionBool(struct Expression *node, int reg_base);
static int visitNumberFactor(struct Expression *node, int reg_base);
static int visitBooleanFactor(struct Expression *node, int reg_base);
static int visitVariableFactor(struct Expression *node, int reg_base);
static int visitFunctionFactor(struct Expression *node, int reg_base);

// common functions for statements and expressions
static void setVariable(struct Symbol *symbol, int reg);
static void setupFunctionCall(struct Symbol *fsymbol, struct ExpressionList *parameters, int reg);

// helper functions for emitting ops
static int emit(Instruction instr);
static void backpatch(int branch_instruction_address, int new_disp);

static Instruction code[CODE_SIZE];
static int code_index;

static struct Scope *current_scope = NULL;

// helper macros for special registers
#define FP 12
#define SP 13
#define LN 14
#define IP 15

// stack frame offsets
#define OFFSET_FIRST_PARAM -4
#define OFFSET_RET_VAL -3
#define OFFSET_STATIC_LINK -2
#define OFFSET_RET_ADDR -1
#define OFFSET_FIRST_LOCAL 1 

#include "codegen_tools.c"

void codegen(struct TranslationUnit *ast) {
  for (int i = 0; i < CODE_SIZE; i++) {
    code[i].op = OP_HLT;
    code[i].arg1 = 0;
    code[i].arg2 = 0;
    code[i].arg3 = 0;
  }
  code_index = 0;
  visitTranslationUnit(ast);
}

static void visitTranslationUnit(struct TranslationUnit *node) {
  current_scope = node->scope;
  visitBlock(node->block);
  code[code_index++] = VM_HLT();
}

static void visitBlock(struct Block *node) {
  // classroom exercise
  visitVarDecls(node->vardecls);

  // skip past function definitions, since we want to start running the current function body
  int saved_jump = emit(VM_BR(0));
  visitFuncDecls(node->funcdecls);

  // code_index is now the body of the function (or main)
  int entry_point = code_index;
  backpatch(saved_jump, code_index - saved_jump); // backpatch
  visitStatement(node->statement);
}

static void visitVarDecls(struct TypedIdentList *list) {
  // given skeleton
  struct TypedIdentListElement *cur = list->head;
  int num_vars = 0;
  while (NULL != cur) {
    // TODO: create space for each var and and update its stack frame offset

    cur = cur->next;
  }
}

static void visitFuncDecl(struct FuncDecl *node) {
  struct Symbol *fsymbol = node->symbol;

  // TODO: setup the function address and stack frame
}

static void visitFormals(struct TypedIdentList *list) {
  // given skeleton
  int num_formals = 0;
  struct TypedIdentListElement *cur = list->head;
  while (NULL != cur) {
    struct TypedIdent *node = cur->node;

    // TODO: parameters are pushed in reverse order and space for the
    // return value is made by the caller before the stack frame, so
    // update the address of each parameter accordingly.
    
    cur = cur->next;
  }
}

static void visitFuncDecls(struct FuncDeclList *list) {
  // given
  struct FuncDeclListElement *cur = list->head;
  while (NULL != cur) {
    visitFuncDecl(cur->node);
    cur = cur->next;
  }
}

static void visitStatement(struct Statement *node) {
  // given
  switch (node->kind) {
  case ASSIGNSTATEMENT:
    visitAssignStatement(node);
    break;
  case CALLSTATEMENT:
    visitCallStatement(node);
    break;
  case RETURNSTATEMENT:
    visitReturnStatement(node);
    break;
  case COMPOUNDSTATEMENT:
    visitCompoundStatement(node);
    break;
  case IFSTATEMENT:
    visitIfStatement(node);
    break;
  case WHILESTATEMENT:
    visitWhileStatement(node);
    break;
  case READSTATEMENT:
    visitReadStatement(node);
    break;
  case WRITESTATEMENT:
    visitWriteStatement(node);
    break;
  default:
    error(0, 0, "unknown option");
    exit(1);
    break;
  }
}

static void setVariable(struct Symbol *symbol, int reg) {
  // TODO: generate code that moves a value into a variable's address
  // on the stack.  the variable may be in a parent scope, so first
  // generate code that finds the variable's scope's stack frame by
  // following the static links.
}

static void visitAssignStatement(struct Statement *node) {
  // given
  struct Symbol *symbol = node->assign_symbol;
  int assigned_reg = visitExpression(node->assign_expression, node->assign_expression->ershov - 1);

  setVariable(symbol, assigned_reg);
}

static void setupFunctionCall(struct Symbol *fsymbol, struct ExpressionList *parameters, int reg_base) {
  // TODO: allocate space for the parameters

  // TODO: allocate space for the return value

  // TODO: allocate space for the static link and set the static link.
  // the static link depends on the scope of the function being
  // called.
  if (fsymbol->scope->level == current_scope->level)  {
    // TODO
  } else {
    int level_difference = (current_scope->level - 1) - fsymbol->scope->level;
    if (level_difference >= 0) {
      // TODO
    } else {
      error(0, 0, "nesting depth of callee should not be more than one level deeper than caller");
      exit(1);
    }
  }

  // TODO: emit the branch and link to the function's code index
  // (recall that branches are relative)

  // emit code to tear down the stack
  // TODO: deallocate space for the static link
  // TODO: pop the return value into reg_base
  // TODO: deallocate space for the parameters
}

static void visitCallStatement(struct Statement *node) {
  // given
  struct Symbol *fsymbol = node->call_symbol;
  struct ExpressionList *parameters = node->call_parameters;
  // since this is a statement, we know that no intermediate values
  // will be in registers.  so just use r0, though we don't need the
  // return value for a call statement
  int reg_base = 0;  // put result in r0
  setupFunctionCall(fsymbol, parameters, reg_base);
}

static void visitReturnStatement(struct Statement *node) {
  // TODO: generate code for the return statement. recall that the
  // function's symbol is stored as an attribute on the return
  // statement node. store the result in the stack slot for the return
  // value (FP - 3), i.e., OFFSET_RET_VAL
}

static void visitCompoundStatement(struct Statement *node) {
  // given
  struct StatementListElement *cur = node->compound_statement->head;
  while (NULL != cur) {
    visitStatement(cur->node);
    cur = cur->next;
  }
}

static void visitIfStatement(struct Statement *node) {
  // TODO

  // first evaluate the expression, recording the register in which the result is stored

  // emit a comparison, i.e., cmpi reg 1

  // emit a branch to skip the if body when comparison is false.  be
  // sure to store save the result of the emit, i.e., the index of the
  // branch instruction, for later backpatching.

  // process the body of the if

  // emit a branch to skip the else body, again saving the index for
  // later backpatching.

  // backpatch the first branch (the one that skips the if body) to
  // jump to the current code index.  remember that branchs are
  // relative, i.e., don't backpatch it to the current code_index, but
  // instead the difference between the current code_index and the
  // index of the branch instruction.

  // process the else branch if it exists

  // backpatch the second branch (that skips the else body)
}

static void visitWhileStatement(struct Statement *node) {
  // TODO (somewhat similar to if)
}

static void visitReadStatement(struct Statement *node) {
  // TODO
}

static void visitWriteStatement(struct Statement *node) {
  // given
  int reg = visitExpression(node->write_expression, node->write_expression->ershov - 1);
  emit(VM_WR(reg));
}

static int visitExpression(struct Expression *node, int reg_base) {
  // given skeleton
  if (reg_base > 11 || (reg_base - node->ershov + 1) < 0) {
    /* Some expressions may require storing more intermediate results
       than there are available registers.  It is left as an optional exercise
       to allocate extra space in the stack frame for the temporary
       variables. */
    error(0, 0, "expression requires too many registers, please rewrite the source code using extra local variables");
    exit(1);
  }
  if (BINARYEXPRESSION == node->kind) {
    // TODO: similar to unary expressions
    return -1;  // be sure to replace this with the correct return value
  } else if (UNARYEXPRESSION == node->kind) {
    // classroom
    if (isInt(node->datatype)) {
      return visitUnaryExpressionInt(node, reg_base);
    } else if (isBool(node->datatype)) {
      return visitUnaryExpressionBool(node, reg_base);
    } else {
      assert(false); // should not happen if typechecker is correct
    }
  } else if (NUMBERFACTOR == node->kind) {
    return visitNumberFactor(node, reg_base);
  } else if (BOOLEANFACTOR == node->kind) {
    return visitBooleanFactor(node, reg_base);
  } else if (VARIABLEFACTOR == node->kind) {
    return visitVariableFactor(node, reg_base);
  } else if (FUNCTIONFACTOR == node->kind) {
    return visitFunctionFactor(node, reg_base);
  } else {
    error(0, 0, "unknown option");
    exit(1);
  }
}

static int visitBinaryExpressionInt(struct Expression *node, int reg_base) {
  int right_reg;
  int left_reg;
  // use ershov numbers to determine the base registers for the left
  // and right children
  int result_reg = reg_base - node->ershov + 1;
  switch (node->binary_op->kind) {
  case PLUS:
    // TODO
    break;
  case MINUS:
    // TODO
    break;
  case MULT:
    // TODO
    break;
  case DIV:
    // TODO
    break;
  case MOD:
    // TODO
    break;
  default:
    assert(false);  // not supposed to happen if parser and typechecker are correct */
    break;
  }
  
  return result_reg;
}

static int visitUnaryExpressionInt(struct Expression *node, int reg_base) {
  // TODO
  return -1;  // be sure to replace this with the correct return value
}

static int visitBinaryExpressionBool(struct Expression *node, int reg_base) {
  // TODO
  int right_reg;
  int left_reg;
  // use ershov numbers to determine the base registers for the left
  // and right children
  int result_reg = reg_base - node->ershov + 1;;
  switch (node->binary_op->kind) {
  case LT:
    emit(VM_CMP(left_reg, right_reg));
    emit(VM_BLT(3));
    emit(VM_MOVI(result_reg, 0));
    emit(VM_BR(2));
    emit(VM_MOVI(result_reg, 1));
    break;
  case LTE:
    // TODO
    break;
  case GT:
    // TODO
    break;
  case GTE:
    // TODO
    break;
  case AND:
    // TODO
    break;
  case OR:
    // TODO
    break;
  case EQ:
    // TODO
    break;
  case NEQ:
    // TODO
    break;
  default:
    assert(false);  // not supposed to happen if parser and typechecker are correct */
    break;
  }

  return result_reg;
}

static int visitUnaryExpressionBool(struct Expression *node, int reg_base) {
  // classroom exercise
  int result_reg = visitExpression(node->unary_expression, reg_base);
  struct DataType *operand_type = node->unary_expression->datatype;
  switch (node->unary_op->kind) {
  case NOT:
    emit(VM_CMPI(result_reg, 0));
    emit(VM_BEQ(3));
    emit(VM_MOVI(result_reg, 0));
    emit(VM_BR(2));
    emit(VM_MOVI(result_reg, 1));
    break;
  default:
    assert(false);  // not supposed to happen if parser and typechecker are correct */
    break;
  }
  return result_reg;
}

static int visitNumberFactor(struct Expression *node, int reg_base) {
  // given
  emit(VM_MOVI(reg_base, node->number_value));
  return reg_base;
}

static int visitBooleanFactor(struct Expression *node, int reg_base) {
  // TODO: generate code for a boolean constant.  1 is true, 0 is false.
  return reg_base;
}

static int visitVariableFactor(struct Expression *node, int reg_base) {
  // TODO
  struct Symbol *symbol = node->variable_symbol;

  // similarly to assignment, first need to generate code that finds
  // follows the stack frame for the scope of the variable.  then
  // store the value in reg_base.
  
  return reg_base;
}

static int visitFunctionFactor(struct Expression *node, int reg_base) {
  // given
  struct Symbol *fsymbol = node->function_symbol;
  struct ExpressionList *parameters = node->function_parameters;

  // push any registers that hold temporary values
  for (int i = 0; i < reg_base; i++) {
    code[code_index++] = VM_PSH(i, SP);
  }

  setupFunctionCall(fsymbol, parameters, reg_base);

  // pop any registers that hold temporary values
  for (int i = reg_base - 1; i >= 0; i--) {
    code[code_index++] = VM_POP(i, SP);
  }

  return reg_base;
}

static int emit(Instruction instr) {
  code[code_index] = instr;
  return code_index++;  // return the index of the instr, before incrementing it
}

static void backpatch(int branch_instruction_address, int new_disp) {
  code[branch_instruction_address].arg1 = new_disp;
}
