static void visitUnaryExpression(struct Expression *node) {
  // given
  visitExpression(node->unary_expression);
  struct DataType *operand_type = node->unary_expression->datatype;
  switch (node->unary_op->kind) {
  case MINUS:
    // int -> int
    if (isInt(operand_type)) {
      node->datatype = getInt();
    } else {
      type_error(EXPRESSION_EXPECTED_INT);
    }
    break;
  case NOT:
    // bool -> bool
    if (isBool(operand_type)) {
      node->datatype = getBool();
    } else {
      type_error(EXPRESSION_EXPECTED_BOOL);
    }
    break;
  default:
    assert(false);  // not supposed to happen if parser is correct
    break;
  }
}
