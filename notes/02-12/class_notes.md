Brian Kernighan  

Debugging techniques are very important and helpful in programming. You need to learn it by your own.  
Focus on one piece of code at a time. Break it down to small pieces.  
Don't just use the test cases given to you. Design little test cases for your code.  
You noticed there is a problem. The first step is to figure out where it is happening. Ex: if it is in statement function, craft a test case that just has statement. It needs a little experience to write good test cases.  
Prints are also helpful. So if you have a hypothesis you can add print in that part of your code. Craft even smaller test cases to step through your code line by line.  
Make sure that every little line makes what it supposed to do  

Debugging tool is like a fancy print statement generator, use it  
As a programmer, all you are doing is setting variables: setting states and changing states  
You should be able to trace how this state changes through the program  

Abstraction means remove unnecessary parts.  

Next project is typechecker. It is tricky but easier to implement. It is a tree traversal algorithm.  

### Bottom-up parsing
With bottom up parsing, we start with the tokens in the language, then, we continue with what productions lead to those tokens until we reach to starting symbol  
Instead of recursive functions, we will use a stack  
Recursion is simply saving your state of stack - in this algorithm, we will manage the stack  
We use stack which is going to save your states. We scan the input from left to right.  
At the end of the process, our stack will only have the start state and all tokens will be consumed  
Shift reduce parsing: as we read elements we push nonterminals on the stack.  

There are two operations:  
- Shift: Reading a symbol and pushing it on to the stack.  
- Reduce: Pop the right handside from the stack and replace it with a nonterminal which creates that. Replace a sequence of symbols with a nonterminal (based on the grammar).  
You have parsing which tells you given state and what state to move to.  

The meaning of LR is: L: left to right scanning, R: right-most derivation  
LR parsing algorithm looks at the next token in the input and decides what action to take  

By using parse table, we can see if we can replace that terminal with a nonterminal or not. If we can, we have a reduce.  
Sometimes parsing table tells us don’t reduce now, still you need to do shift and read next symbols.  
You can see the next symbol (one symbol look-ahead), parsing table makes the decision if we should shift or reduce  
Anytime you use a pop off on the stack those are the children of the nonterminal node you will push. So it is kind of similar to syntax tree construction.  
If the table is empty for the current state, it leads to an error which means that this particular string is not in the language  
When you read all of the symbols from the input string and the stack only has start nonterminal, the grammar accepts that string.  
Money sign $ is used as a sign for the end of the string.  

Constructing parsing table from grammar is another thing to do  

We start with the right hand side of the productions (terminals and nonterminals) and replace it with the left hand side of the production (nonterminals)  

It can recognize any unambigous context free grammar (while the other algorithm we used cannot recognize some)  

We are simulating a push-down automata (which is finite state automata + stack)  

## Constructing LR(0) States  
Little dots say that we are at this position in the grammar  
By definition, the algorithm adds an extra starting state as S’ -> S$, where $ denotes end of string  
To show non-determinism, we write all possible positions we could be at our grammar since we may not know yet which production we will end up having  

You are keeping track of every single state you could be at the grammar  
It encapsulates all possible inputs of the grammar  

Parsing table is like a transition table  

If our transition happens with a terminal, we do “shift” (consume token and push it onto the stack)  
If our transition happens with a non-terminal: we do “reduce”  

For example, “r3” means “reduce with production(or rule) 3”. 3 is not the state. So, we use the production rule 3 while reducing.  
