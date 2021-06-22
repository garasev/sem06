predicates
	max(integer, integer, integer) 
	max_cat(integer, integer, integer) 
	max(integer, integer, integer, integer) 
	max_cat(integer, integer, integer, integer) 
clauses
	max(X, Y, X):- X >= Y.
	max(X, Y, Y):- X < Y.
	max_cat(X, Y, X):- X >= Y, !.
	max_cat(_, Y, Y).
	max(X, Y, Z, X):- X >= Y, X >= Z.
	max(X, Y, Z, Y):- Y >= X, Y >= Z.
	max(X, Y, Z, Z):- Z >= X, Z >= Y.
	max_cat(X, Y, Z, X):- X >= Y, X >= Z, !.
	max_cat(_, Y, Z, Y):- Y >= Z, !.
	max_cat(_, _, Z, Z).
goal
	max(1, 5, 3, Max).
