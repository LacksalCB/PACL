(* Input tokenized list of tuples in the format:  *)
(* {(Type, Value); (Type, value);... *)

type token_t = 
	| T_id
	| T_num 
	| T_symbol

(* AST TYPES *)
type term_ops = 
	| Mul
	| Div

type expr_ops = 
	| Add
	| Sub

type id = 
	| Var of string
	| Num of string

type factor =
	| Factor of id

type term = 
	| Term of factor
	| Term_op of term * term_ops * factor 

type expression = 
	| Expression of term
	| Expression_op of expression * expr_ops * term
	
type statement = 
	| Statement of id * expression

(* This is basically the next step 
let rec parse_term = function 
 	| blah

*)

let rec parse_expression = function
	| [] -> failwith ("Invalid expression")
	| [_;_] -> failwith ("Invalid expression")
	| a::[] -> (match a with
		| (T_id, x) ->
			Expression(Term(Factor(Var(x))))
		| (T_num, n) ->
			Expression(Term(Factor(Num(n))))
		| _ -> failwith ("Invalid expression: Terminal must be of VAR or NUM type."))
	| a::b::c::xs -> match b with
		| (T_symbol, "+") -> (match (a, c) with 
			| (T_id, x), (T_id, y) ->
				Expression_op(Expression(Term(Factor(Var(x)))), Add, Term(Factor(Var(y))))
			| (T_id, x), (T_num, y) ->
				Expression_op(Expression(Term(Factor(Var(x)))), Add, Term(Factor(Num(y))))
			| (T_num, x), (T_id, y) ->
				Expression_op(Expression(Term(Factor(Num(x)))), Add, Term(Factor(Var(y))))
			| (T_num, x), (T_num, y) ->
				Expression_op(Expression(Term(Factor(Num(x)))), Add, Term(Factor(Num(y))))
			| _, _ -> failwith ("Invalid Expression: Malformed operation (bad addition)"))
		| (T_symbol, "-") -> (match (a, c) with 	
			| (T_id, x), (T_id, y) ->
				Expression_op(Expression(Term(Factor(Var(x)))), Sub, Term(Factor(Var(y))))
			| (T_id, x), (T_num, y) ->
				Expression_op(Expression(Term(Factor(Var(x)))), Sub, Term(Factor(Num(y))))
			| (T_num, x), (T_id, y) ->
				Expression_op(Expression(Term(Factor(Num(x)))), Sub, Term(Factor(Var(y))))
			| (T_num, x), (T_num, y) ->
				Expression_op(Expression(Term(Factor(Num(x)))), Sub, Term(Factor(Num(y))))
			| _, _ -> failwith ("Invalid Expression: Malformed operation (bad subtraction)"))
		| (T_symbol, "*") -> (match (a, c) with 	
			| (T_id, x), (T_id, y) ->
				Expression(Term_op(Term(Factor(Var(x))), Mul, Factor(Var(y))))
			| (T_id, x), (T_num, y) ->
				Expression(Term_op(Term(Factor(Var(x))), Mul, Factor(Num(y))))
			| (T_num, x), (T_id, y) ->
				Expression(Term_op(Term(Factor(Num(x))), Mul, Factor(Var(y))))
			| (T_num, x), (T_num, y) ->
				Expression(Term_op(Term(Factor(Num(x))), Mul, Factor(Num(y))))
			| _, _ -> failwith ("Invalid Expression: Malformed operation (bad multiplication)"))
		| (T_symbol, "/") -> (match (a, c) with
			| (T_id, x), (T_id, y) ->
				Expression(Term_op(Term(Factor(Var(x))), Div, Factor(Var(y))))
			| (T_id, x), (T_num, y) ->
				Expression(Term_op(Term(Factor(Var(x))), Div, Factor(Num(y))))
			| (T_num, x), (T_id, y) ->
				Expression(Term_op(Term(Factor(Num(x))), Div, Factor(Var(y))))
			| (T_num, x), (T_num, y) ->
				Expression(Term_op(Term(Factor(Num(x))), Div, Factor(Num(y)))) 	
			| _, _ -> failwith ("Invalid Expression: Malformed operation (bad division)"))
		| _ -> failwith ("Invalid expression: unknown operator.")
	

let rec parse = function 
	| [] -> failwith ("Invalid argument") 							(* Empty List *)
	| [_] -> failwith ("Invalid argument: only one ID.") 			(* Only 1 item in input list of tokens *)
	| [_; _] -> failwith ("Invalid Expression: Only two IDs") 		(* Only 2 items in input list of tokens *)
	(* b should always be a symbol (meaning assignment or math with an L and R) *)
	| a::b::xs -> match b with 
		(* Simple variable assignment *)
		| (T_symbol, "=") -> (match a with 
			| (T_id, x)  -> 
				Statement(Var(x), parse_expression xs)
			| _ -> failwith ("Invalid expression"))
		| _ -> failwith ("Invalid Expression")

