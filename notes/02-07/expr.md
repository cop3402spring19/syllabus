    static struct  Expression *expr() {
      // partially given to enable write NUMBER (allow user to work with tagged union)

      struct Expression *left = simpleexpr();

      next();
      if (is_relop()) {
        struct Expression *node = newExpression(BINARYEXPRESSION);

        node->binary_left = left;
        node->binary_op = token();
        node->binary_right = simpleexpr();
        return node;
      } else {
        previous();
        return left;
      }
    }
