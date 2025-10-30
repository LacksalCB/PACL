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

(* Recursively generates AST *)

let rec parse_expression = function
	| [] -> failwith ("Invalid expression")
	| a::[] -> (match a with
		| (T_id, x) ->
			Expression(Term(Factor(Var(x))))
		| (T_num, n) ->
			Expression(Term(Factor(Num(n))))
		| _ -> failwith ("Invalid expression: Terminal must be of VAR or NUM type."))
	| [_;_] -> failwith ("Invalid expression")
	

let rec parse = function 
	| [] -> failwith ("Invalid argument") 							(* Empty List *)
	| [_] -> failwith ("Invalid argument: only one ID.") 			(* Only 1 item in input list of tokens *)
	| [_; _] -> failwith ("Invalid Expression: Only two IDs") 	(* Only 2 items in input list of tokens *)
	(* b should always be a symbol (meaning assignment or math with an L and R) *)
	| a::b::xs -> match b with 
		(* Simple variable assignment *)
		| (T_symbol, "=") -> (match a with 
			| (T_id, x)  -> 
				Statement(Var(x), parse_expression xs)
			| _ -> failwith ("Invalid expression"))
		| _ -> failwith ("Invalid Expression");;


let tokens = [(T_id, "x"); (T_symbol, "="); (T_id, "y")]
in assert (parse tokens = Statement(Var("x"), Expression(Term(Factor(Var("y"))))))

(*
let tokens = [(T_id), "x"; (T_symbol), "="; (T_num), "3"]
in assert (parse tokens = Statement(Var("x"), Expression(Term(Factor(Num"3")))));
*)

(*
let tokens = [(T_id), "x"; (T_symbol), "="; (T_num), "1"; (T_symbol), "+"; (T_num), "2"]
in assert (parse_statement tokens = Statement(Var("x"), Expression_op(Expression(Term(Factor(Num("1")))), Add, Term(Factor(Num("2"))))));
*)
