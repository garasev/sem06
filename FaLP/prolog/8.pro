predicates
	factorial(integer, integer)
 	f(integer, integer, integer, integer)
	fib(integer, integer)
	fib1(integer, integer, integer, integer)
  
clauses
	factorial(X, Res):- f(X, Res, 1, 1).            %obertka
	f(X, Res, X, Res):- !.                                 % X = X1 -> exit
	f(X, Res, X1, Res1):- Tmp = X1+1, Res_tmp = Res1 * Tmp, f(X, Res, Tmp, Res_tmp). 
	
	fib(X, R):- fib1(X, R, 1, 0).                      %obertka
	fib1(1, R, R, _):- !.                                   % x=1 -> exit
	fib1(X, R, X1, X2):- R1 = X1 + X2, P = X - 1, fib1(P, R, R1, X1).

goal
	%factorial(3, Res).
	fib(6, R).
