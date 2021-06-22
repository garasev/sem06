domains 
	list = integer*.
predicates
	len(list, integer).
	len(list, integer, integer).
  
	sum(list, integer).
	sum(list, integer, integer). 
  
	sumOdd(list, integer).
	sumOdd(List, integer, integer).
clauses
	len(List, Len) :- len(List, 0, Len).
	len([], Len, Len):- !.
	len([_|T], Cur, Len) :- NewLen = Cur + 1, len(T, NewLen, Len).
  
	sum(List, Sum) :- sum(List, 0, Sum).
	sum([], Sum, Sum):- !. 
	sum([H|T], Cur, Sum) :- NewSum = Cur + H, sum(T, NewSum, Sum).
  
	sumOdd(List, Sum):- sumOdd(List, 0, Sum).
	sumOdd([], Sum, Sum):- !. 
	sumOdd([_], Sum, Sum):- !.
	sumOdd([_|[H|T]], Cur, Sum):- NewSum = Cur+H, sumOdd(T, NewSum, Sum).
  
goal
	%len([1, 2, 3, 4, 5], Len).
	sum([1, 2, 8, 9], Sum).
	%sumOdd([1, 2, 0, 8, 1], Sum).
