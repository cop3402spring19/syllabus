Notion of characters is not built in the language. As a programmer you are going to use state machines regularly.  

Pokemon video, you can model playing the game entirely with state machines.  
You learn the abstract in computer science and you can apply it in real problems.  

Here are two sentences:
1. “Colorless green ideas sleep furiously.”  
2. “Furiously sleep ideas green colorless.”  

The second sentence follows english grammar better. Semantically none of them makes sense. However, syntactically the second one makes more sense.  
The language have these syntax nested. Language has nested structure.
Something that language desingers have to do.
Regular expressions can do a lot but they are not powerful enough to express the syntax. So, we need something more powerful like CFGs.

Regular expressions are limited because they:
- can't do counting
- can't do nesting

One cannot write a regular language for the following language: equal number of `a`s and `b`s `{ epsilon, ab, aabb, aaabbb, ... }`.  
We cannot show it with regular expressions.  
`a*b*` does not show this language since the number of `a`s should be equal to number of `b`s.  

Regular languages cannot handle nested structures (like programming languages).  

If something is regular language, it is also context-free language.  

There is this hierarchy of language from chomsky.  

How do we learn language? This question is still out: linguistics.  

Chomsky suggests that you are born with the skills to learn the language. 
The belief was that grammar has the ability to generate language. You have the structure in your brain and when you speak you follow the grammar tree. Generative grammar.  

State machines corresponds to language.  
It provides the mechanical explanation for language generation.  
We can use them So to do interesting things like writing compilers.  

We have different tools to express each type of language.  

Regular languages are expressed using regular expressions.  
Context free languages are expressed using context free grammars (CFG).  

### CFG
CFGs take the words and represent them as symbols  
Mechanical way to describe relation between elements  
Defines a potentially infinite language   

Example with English language:  
```
sentence  -> subject verb object
sentence  -> subject verb
subject   -> article adjective noun
article   -> "the"
article   -> "an"
adjective -> "blue"
...
...
```  

We start from some symbol and keep breaking down until we end up with terminals  
Terminals are the actual words in the language  

Symbols may have multiple ways to be broken down (see `sentence` above), grammar allows many rules  

CFGs are defined using by:
- Terminals (actual words of the language)  
- Nonterminals (symbols, like statements, sentences)  
- Productions (denoted by `->`) (rules in the language. some elements of the language can be broken down into smaller pieces, sentences can be broken into words, statements can be broken intoo other statements..)  
- Starting symbol (by convention, always the first non-terminal, the first symbol)  

On the left hand-side, you have non-terminals (symbols)  
Then, productions (denoted by arrow `->`)  
Then, followed by list of terminals and/or non-terminals  

You recognize the terminals with the lexer  

Non-terminals can be broken down, terminals cannot  

Any regular language is also a context free language, but not vice versa.  
You can represent any regular expression by using a context free grammar  

Concatenation in regular expression (`ab`):  
```
A -> ab
```  
Union in regular expression (`a | b`):   
```
A -> a
A -> b
```
Closure(`a*`):  
```
A -> Aa      : you can keep expanding by using this production
A -> epsilon : you can stop expanding by using this production
```

By convention, non-terminals are written in capital letters.  

__Example:__  
Terminals: ```plus, minus, times, div, lparen, rparen, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9```   
Non-terminals: ```T, F, N, D```  
```
T -> T plus F
T -> T minus F
T -> F
F -> F times N
F -> F div N
F -> N
N -> N D | epsilonD
N -> lparen T rparen
D -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
```

Grammar generates strings in the language  
Compiler does the reverse: it checks if and how the string could be generated from the grammar  

Let's start by generating string  
Each step(`=>`) in the derivation is one application of a production  

`T => T minus F`          : T is expanded to "T minus F"  
`  => T plus F minus F`   : T is expanded to "T plus F"  
`  => F plus F minus F`   : T is expanded to F  
`  =>* N plus N minus N`  : when we put start near `=>`, it means we did multiple derivations at one step. Here, we expanded all `F`s to `N`s (three derivation in total)  
`  =>* 10 plus 3 minus 2` : first `N` is expanded such that `N=>ND=>NDD=>epsilonDD=>10`. Second `N` is expanded such that `N=>ND=>epsilonD=>3`. Third `N` is expanded to `N=>ND=>epsilonD=>2`.  
  
  
__Example:__  
`E -> E * E | E + E | id | (E)`  


Notice that instead of multiple productions of `E` to show union, `|` is used to write multiple possible productions.  

Non-terminals: `E`  
Terminals: `*`, `+`, `id`, `(`, `)`  

We know the terminals because they have no productions. Terminals occur on the left hand-side while non-terminals do not.  

Given the string in the language, what is the derivation of that symbol from our grammar? This will be the work for our project.  

String: `id + id`  

Derivation:
```
E => E + E
  => id + E
  => id + id
```

String: `id + id * id`  

Derivation:  
```
E => E * E
  => E + E * E     : first E is expanded to E + E
  => id + E * E
  => id + id * E   
  => id + id * id   
```

Or, another derivation:  
```
E => E + E
  => id + E        : first E is expanded to id
  => id + E * E    : E is expanded to E*E
  => id + id * E
  => id + id * id
```

You can first expand any non-terminal you want. By convention, always start expanding from left-most non-terminal symbol.  

Here, we are only talking about the structure and syntax - not meaning. It is very hard to understand meaning in languages.
Parse trees are another way to express how we can create the strings from the start symbol in the grammar.  

We can use a tree representation to represent derivations: parse tree  
```
        E
     /  |   \
    E   *    E
 /  | \      |
E   +  E    id
|      |
id     id
```

Or:  

```
     E
 /   |   \
E    +    E
|       / | \
id     E  *  E
       |     |
       id   id
```

So, we have two different parses of the string. So, the grammar is ambiguous. 

Let’s say we have id's in such way:  
`1 + 2 * 3`  

First parse tree suggests to first do the addition, then multiplication, which has 9 as the result.  Second parse tree suggests to first do the multiplication then the addition, which has 7 as the result.  

To solve the ambiguoity, we could rewrite the grammar:
```
E -> E + T | E
T -> T * F | F
T -> id
```

There is only one possible derivation for the string `id + id * id` with the above grammar. Next time, we will go over the derivation of this grammar.
