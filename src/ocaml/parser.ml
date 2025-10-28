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
	| Term_op of term_ops * term * factor 

type expression = 
	| Expression of term
	| Expression_op of expr_ops * expression * term
	
type statement = 
	| Statement of id * expression


(* Recursively generates AST *)

let parser = function
	| [] -> failwith ("Invalid argument") (* Empty List, should never be possible at this stage *)
	| _::[] -> failwith ("Invalid argument: only one ID.") (* Only 1 item in input list of tokens *)
	| _::b::[] -> failwith("Invalid Expression: Only two IDs") (* Only 2 items in input list of tokens *)
	(* b should always be a symbol (meaning assignment or math with an L and R)*)
	(* a should only ever be an ID (i.e. a variable) and c can be either a const number or another ID (i.e. integer math or reassignment of a var to a var) *)
	| a::b::c::xs -> match b with 
		| (T_symbol, "=") -> (match (a, c) with 
			| (T_id, x), (T_id, y) -> Statement(Var(x), Expression(Term(Factor(Var(y)))))
			| (T_id, x), (T_num, n) -> Statement(Var(x), Expression(Term(Factor(Num(n)))))
			| _, _ -> failwith ("Invalid Expression"))
(*
		| (T_symbol, "+") -> (match (a, c) with
			| (T_id, _), (T_id, _) -> "Addition with IDs"
			| (T_id, _), (T_num, _) -> "Addition with ID/Num"
			| (_, _), (_, _) -> "Invalid Expression")
		| (T_symbol, "-") -> (match (a, c) with
			| (T_id, _), (T_id, _) -> "Subtraction with IDs"
			| (T_id, _), (T_num, _) -> "Subtraction with ID/Num"
			| (_, _), (_, _) -> "Invalid Expression")
		| (T_symbol, "*") -> (match (a, c) with
			| (T_id, _), (T_id, _) -> "Multiplication with IDs"
			| (T_id, _), (T_num, _) -> "Multiplication with ID/Num"
			| (_, _), (_, _) -> "Invalid Expression")
		| (T_symbol, "/") -> (match (a, c) with
			| (T_id, _), (T_id, _) -> "Division with IDs"
			| (T_id, _), (T_num, _) -> "Division with ID/Num"
			| (_, _), (_, _) -> "Invalid Expression")
*)
		| (_, _) -> failwith("Invalid Expression (Not an operator)");;


let tokens = [(T_id), "x"; (T_symbol), "="; (T_id), "y"]
in assert (parser tokens = Statement(Var("x"), Expression(Term(Factor(Var("y"))))));


let tokens = [(T_id), "x"; (T_symbol), "="; (T_num), "3"]
in assert (parser tokens = Statement(Var("x"), Expression(Term(Factor(Num"3")))));
