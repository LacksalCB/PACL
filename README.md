# PACL
Graphics processing focused programming language.  Examples of syntax (and basic testing benchmarks) are provided in `/examples`.
Basic design is outlined in `Design.txt` and `Outline.txt`.


## Progress/Functionality
Current Goal: Parsing/AST Construction

Effectively creating a deterministic CFL to represent language in AST
Phase 0 Design -> Mathematical Expression Parser:
	<stmt> ::= <id> = <exp> 
	<exp> ::= <term> | <exp> + <term> | <exp> - <term>
	<term> ::= <factor> | <term> * <factor> | <term> / <factor>
	<factor> ::= <var> | <num> | (<exp>)
	<var> ::= [azAz_*09azAZ*]
	<num> ::= [09]*

0.0 Simple Assignment (DONE)
0.1 Assignment + Recursive OP (DONE)
0.2 Assignment + Recursive OP with Precedence (IN PROGRESS)
0.3 Full Mathematical Expressions (TODO)
