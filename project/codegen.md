## Code Generation

### Helper Functions

    VM_OPNAME(arg, arg, ...)
    
There is a series of macros to create the instruction struct for each
opcode, e.g., `VM_CMPI(0, 1)`, generates `cmpi r0 1`.  These are all
contained in `codegen_instr.h`.  See `ops.txt` as a reference.

    int emit(Instruction instr);
    
This function adds the given instructions to the `code[]` array,
advances the `code_index`, and returns the index of the generated
instruction.  For instance, `emit(VM_CMPI(0, 1))`, adds `cmpi r0 1` to
the list of generated instructions.

    void backpatch(int branch_instruction_address, int new_disp);
    
This function backpatches a branch at code index
`instruction_address`, i.e., it replaces the displacement argument
with the given `new_disp` value.  For instance, if I generate a branch:

    int save_index = emit(VM_BR(0));
    
I can later backpatch it by doing:

    backpatch(save_index, code_index - save_index);

### Functions

(The dragon book sections 7.2 and 7.3 discuss stack management.)

- Getting the stack right
- Tested with writes function calls and variables, as well as constants to test entrance into functions

#### Function Calls

Stack layout:

- Offsets to reach caller values, i.e., activation record (positive offsets in our machine)
  - `FP - (4 + i)`: ith parameter
  - `FP - 3`: return value
  - `FP - 2`: the static link, or access link, i.e., the frame pointer of the parent function
- Offsets to reach callee values (negative offsets in our machine)
  - `FP - 1`: return address (previous contents of `ln` link register)
  - `FP + 0`: the dynamic link, or, control link, i.e., the previous function's base pointer
  - `FP + (1 + i)`: ith local variable


There are convenience macros for these offsets:

    #define OFFSET_FIRST_PARAM -4
    #define OFFSET_RET_VAL -3
    #define OFFSET_STATIC_LINK -2
    #define OFFSET_RET_ADDR -1
    #define OFFSET_FIRST_LOCAL 1 

##### Callee Setup

`visitFuncDecl`

The function's address in the symbol table is the index into the code array.

`current_scope` is updated to record the current scope to look up variables in the symbol table.  Set and restore this variable to the `scope` field of the FuncDecl AST node as you traverse the tree.

- Prologue (before emitting code for the function body)

  - emit a push for the link register (r14), i.e., return address, `psh r14 r13`
  - emit a push for the old frame pointer (r12), `psh r12 r13`
  - update the frame pointer to be the current stack pointer, `mov r12 r13`
  - (done via `visitBlock`, not in `visitFuncDecl`) add space for the local variables, i.e., advance the stack pointer by one for each variable
    - locals are done by `visitVarDecls` via `visitBlock`, so that function should emit `addi sp sp 1` for each one

- Call `visitFormals` and `visitBlock` between prologue and epilogue

- Epilogue (after emitting code for the block)

  - tear down the stack frame, `mov r13 r12`
  - update to the old frame pointer, `pop r12 r13`
  - get the old instruction pointer, emit a pop for the link register, `pop r14 r13`
  - emit a return to link register, `ret r14`

`visitFormals`

- The addresses parameters are relative offsets from the fp, i.e., only store the offset, not the absolute address (which is not knowable at compile-time)

  - These are allocated and stored by the caller, so we only need to set their addresses
  - Each parameters is a fixed distance from the frame pointer
  - They were set by the caller, so we use an offset that is down the stack (negative in our case), rather than into the stack frame.

`visitBlock`

- call the visitor for variable declarations
- save the current `code_index` in order to backpatch the jump
- emit a jump with an arbitrary `disp` that we will backpatch later
- call the visitors for function declarations and 
- backpatch the saved jump with the now current `code_index`, .e., `code[saved_code_index] = code_index - saved_code_index` (recall that branches use relative offsets in the code)
- visit the statement to emit it

`visitVarDecls`

- loop through the variables (skeleton code for iterating over the list is given)
- get the symbol (`cur->node->symbol`) for each variable
- set the address for each variable (`symbol->address`), which is the offset from the frame pointer.  variables appear one after another starting from `OFFSET_FIRST_LOCAL`.
  - e.g., if there are three local variables, `x` and `y`, `x` has
    offset 1 while `y` has offset 2 and so on for more locals.
- emit `addi sp sp 1` for each variable for the prologue

`visitReturnStatement`

- Recall that the caller pushed the return address to `FP - 3`
- visit the expression using its ershov number minus 1 (the initial register base)
- move the register holding the return expression to the stack at that offset
- emit the epilogue

##### Caller Setup

`setupFunctionCall` is used by both `visitCallStatement` and `visitFunctionFactor` to prepare the stack for the call.

- note that your compiler doesn't track the stack pointer, rather it emits code that increments/decrements the pointer in well-defined fixed amounts, i.e., the stack frame size.
- `
visitFunctionFactor` (given) emits pushes for any registers that hold
  temp values (r0-r#), all registers before `reg_base`.
  `visitCallStatement` doesn't need to do this because it doesn't use
  any registers itself.
m
        push r0 sp
        push r1 sp
        ...

`setupFunctionCall` does the following:

- allocate space on the stack for all the parameters (if there are any)
  - use the `list->size` to move the stack pointer `addi sp sp size`, where size is `list->size`
- run `visitExpression` for each expression element.  evaluate these one-at-a-time and immediately store them onto the stack.  that will obviate the need to hold values in registers.

        struct ExpressionListElement *cur = parameters->head;
        int i = 0;
        while (NULL != cur) {
          // TODO: visit the expression and record the resulting register
          // TODO: emit a store into the stack frame under the corresponding actual parameter slot
          i++;
    
          cur = cur->next;
        }



  - use `SP - i` to access the ith parameter
  - emit code for each expression
  - then emit a sto for the resulting value of each expression
- advance the stack pointer by 1 to make space for the return value (easiest to always do this, but can improve memory usage for void functions by omitting it)
- emit a push for the static link
  - remember that the callee's level is `fsymbol->scope->level + 1`.  `fsymbol->scope->level` is the level in which `fsymbol` was declared, so add 1 to find the level of the scope fsymbol creates.
  - if the callee is defined inside the caller's scope (`fsymbol->scope->level == current_scope->level`), the static link is the caller's frame pointer:

            psh fp, sp
        
  - if the callee is a sibling (`fsymbol->scope->level == current_scope->level - 1`), the static link is copied from the current stack frame:
  
  
            ld r0 fp -2
            psh r0 sp
        
  - if the callee is in an ancestor's scope, i.e., N > 0, where N is `(current_scope->level - 1) - fsymbol->scope->level`, then follow the static link N times and copy the the static link found there:
  
            ld r0 fp -2
            ld r0 r0 -2   # for N=1
            ld r0 r0 -2   # for N=2
            ...           # etc
            psh r0 sp 
   
- emit `bl disp`, where `disp` is the current IP (r15) minus the address of function (from symbol table)
- emit pops for the register values stored by the prologue (in reverse order!)

#### Variable Access

`visitVariableFactor(struct Expression *node);`

- Look up the variable in the symbol table (`node->variable_symbol`)
- Check whether the variable is in the current scope (`current_scope->level` vs variable's `symbol->scope->level`)
  - If it's in the current scope, load the variable's value into the register given by `reg_base`.  The load takes some base register plus an offset immediate value.  The base address in this case is the frame pointer, whereas the offset is the address for the variable (`symbol->address`) computed when visiting the function declaration.
  - If the scope is an ancestor (level of symbol is lower than current scope), then we need to emit code that follows the static link N times, where N is the difference in nesting depth, i.e., the difference between the levels.  Save the current frame pointer, and keep loading the static link to the parent's stack frame into FP.  Then store the value into the same register and restore FP.  Recall that the static link can be found at `FP - 2`.
  
            mov r# fp       # store the current fp into the given reg_base r#
            ld r#, r#, -2   # get the parent's frame pointer
            ld r#, r#, -2   # get the parent's parent's frame pointer
            ...             # etc
            ld r#, r#, off  # finally load the variables new value r# (reg_base) into its palce on the stack, i.e., the offset symbol->address from the ancestor stack frame found


`setVariable(struct Symbol *symbol, int reg);` and `visitAssignStatement(struct Statement *node);`

The assign statement is factored out in `setVariable`, since
`visitReadStatement` will need to use it as well.  In `setVariable`, do the following:

- Take the register holding the result of the expression, `reg` as
  passed in from `assigned_reg`, which is the retrun value of
  `visitExpression`.
- Just as with VARIABLEFACTOR above, find the stack frame in which the
  variable is defined
  - If the variable is in the current scope, generate a store into the variable's offset from the frame pointer
  - If the variable is in an ancestor scope, we need to find its frame pointer as above, then perform the store:  first push FP to save it, follow the static links by loading the offset from FP (`OFFSET_STATIC_LINK`=-2) into FP, performing the store, then restoring FP.

            psh fp, sp      # save the current FP
            ld fp, fp, -2   # N=1, fp holds the static parent frame pointer
            ld fp, fp, -2   # N=2, fp holds the static parent's parent's frame pointer
            ld fp, fp, -2   # etc
            ...
            sto r#, fp, off # finally load the variables value, i.e., store the assigned registers r# to the offset symbol->address from the ancestor's stack frame pointer
            pop fp, sp      # restore the current FP

### Expressions

    static int visitExpression(struct Expression *node, int reg_base);
    static int visitBinaryExpressionInt(struct Expression *node, int reg_base);
    static int visitUnaryExpressionInt(struct Expression *node, int reg_base);
    static int visitBinaryExpressionBool(struct Expression *node, int reg_base);
    static int visitUnaryExpressionBool(struct Expression *node, int reg_base);
    static int visitNumberFactor(struct Expression *node, int reg_base);
    static int visitBooleanFactor(struct Expression *node, int reg_base);
    
- Getting the register allocation right, eshov number
- Tested with writes of expressions of constant factors

Statements will only ever call `visitExpression`.  Each function takes
a base register `reg_base` and returns the register that holds the
final result.  Statements can always given 0 for the reg_base (or any
other general-purpose register), since statements require no temporary
values.  The expression visitors will use the Ershov number performed
by the typechecker to determine a new base register for child nodes.

Notice that for binary and unary expressions, there are two functions,
one for integers and one for Booleans.  This is because the machine
instructions for computing operations on these types are different.
Since we already performed type checking, we know by inspecting the
type attributes on the expression nodes which type the expression is
working with.  Check out `visitExpression` to see how the type is used
to dispatch the correct visitor.

Furthermore, the type checker guarantees that we will never see
operations between different types, for instance an integer variable
or number factor in an expression operating on Booleans will be caught
before attempting code generation.

#### Register Allocation

(This can be found in the dragon book section 8.10)

We will use the Ershov numbering scheme computed during typechecking
to implement optimal allocation of registers intermediate values in
expressions.

Some expressions may require storing more intermediate results than
there are registers.  For this project, we will throw an error when
this happens.  The programmer will have to manually rewrite the
expression to use extra local variables.  In general, we can work with
more values than registers by spilling intermediate values to memory.
It is left as an optional exercise to allocate extra space in the
stack frame for the temporary variables (dragon book 8.10 shows the
algorithm, which requires also allocating space in the stack when
emitting the function's prologue).

Here is the algorithm for choosing registers:

- For leaf nodes (`NUMBERFACTOR`, `BOOLEANFACTOR`, `FUNCTIONFACTOR`,
  `VARIABLEFACTOR`,), the result is always just put in `reg_base`,
  since their label is 1.
- For nodes with a single child, we just reuse the register from the
  single child.
- For nodes with two children that have the same Ershov number label:
  - If the labels are the same, then we first emit code for the right
    child with base `reg_base - 1`, then emit the left child with at
    base `reg_base`.  The result is then in `reg_base - node->ershov + 1`.
  - If the labels are different, we first emit code for the larger
    child with `reg_base`, then the smaller child, also with
    `reg_base`.  The result is then in `reg_base - node->ershov + 1`.

_Don't forget to return the resulting register number from each expression visitor!_

#### Boolean Expressions

Computing operations on Boolean expressions is very different from
integers, because, like most physical processors, our machine does not
have explicit operations for Boolean values.  Instead, we use the
compare operation combined with branching to implement the operations.
For instance here is what logical negation looks like, if we have the
value we want negated in r0:

    cmpi r0 0
    beq 3
    movi r0 1
    br 2
    movi r0 0

The basic idea is to compare `r0` to 0, our encoding for `false`.  If
they are equal, then we set `r0` to 1 or `true`.  If they are not
equal, then set `r0` to 0.  This is effectively implementing negation
with an if-then-else statement.  Notice that the branch displacements
are constants: there is no need for backpatching, since we know ahead
of time how many instruction get emitted.

Here is a more complicated example with the `<` operator, where `r0`
and `r1` hold the values being compared and `r2` holds the result.

    cmp r0 r1
    blt 3
    movi r1 0
    br 2
    movi r2 1
    
The code is very similar, except that we use `blt` instead of `beq`,
because we are evaluating the less than symbol.  `<=`. `>`, `>=`, `=`,
and `!=` are similar, using the corresponding branch operator.

`and` and `or` are slightly more subtle.  In a loose sense, we
implement a circuit for an AND or OR gate.  Here is an example of AND,
where `r0` and `r1` hold the values we want to conjoin and `r2` holds
the result.

    cmpi r0 0   # check whether the first operand is false
    beq 5       #   if it is, the result is also false, so jump the to the last op
    cmpi r1 0   # check whether the second operand is false
    beq 3       #   if is is, the result is false, so jump
    movi r2 1   # at this point, we know both operands are true, so set the result to true
    br 2        #   branch past the next op, since it sets the result to false
    movi r2 0   # the target of the jump when either operand is false

This is like writing the `and` operation as two if-statements that
check each operand one-at-a-time.  `or` is similar, but instead if either operand is true, the result is true.

    cmpi r0 1
    beq 5
    cmpi r1 1
    beq 3
    movi r2 0
    br 2
    movi r2 1


### Statements

    static void visitStatement(struct Statement *node);  // given
    static void visitCompoundStatement(struct Statement *list);
    static void visitIfStatement(struct Statement *node);
    static void visitWhileStatement(struct Statement *node);
    static void visitWriteStatement(struct Statement *node);
    static void visitReadStatement(struct Statement *node);
    

- Generating correct control flow and store instructions
- Tested with writes of integer constants

_For all statements (except read) that use expressions, give `ershov - 1` as the initial `reg_base`.  For the read statement, you can just use register `0`, since no expression is being evaluated._

`static void visitIfStatement(struct Statement *node);`

An if statement with the optional else branch:

    if true then
      write 1
    else
      write 0

and it's equivalent VM code:

    movi r0 1
    cmpi r0 1
    bne 4
    movi r0 1
    wr r0
    br 3
    movi r0 0
    wr r0

An if statement without the optional else branch:

    if true then
      write 1

and it's equivalent VM code:

    movi r0 1
    cmpi r0 1
    bne 4
    movi r0 1
    wr r0
    br 1
    
 



`static void visitWhileStatement(struct Statement *node);`

A while loop:

    while true do
      write 1

and it's equivalent VM code:

    movi r0 1
    cmpi r0 1
    bne 4
    movi r0 1
    wr r0
    br -5

This is just like an if statement, but with an extra jump back to the
condition evaluation.

`static void visitReadStatement(struct Statement *node);`

- be sure to use setVariable
