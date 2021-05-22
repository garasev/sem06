domains
	list = integer*.

predicates
	bigger(list, integer, list) 
	oddlist(list, list)
	delete(list, integer, list)
	createSet(list, list)
clauses
  	bigger([], _ ,[]):-!.
  	bigger([H|T], Num, Res) :- H <= Num, bigger(T, Num, Res).
  	bigger([H|T], Num, [H|Res]) :- H > Num, bigger(T, Num, Res).
  
  	oddlist([], []):- !.
  	oddlist([_], []):- !.
  	oddlist([_|[H|T]], [H|Res]):- oddlist(T, Res).
  
  	delete([], _ , []):- !.
  	delete([H|T], Num, [H|Res]) :- H <> Num, delete(T, Num, Res).
  	delete([H|T], H, Res):- delete(T,H, Res).
  
  	createSet([], []):- !.
  	createSet([H|T], [H| Res]):- delete(T, H, Tmp), createSet(Tmp, Res).
goal
  	bigger([1,2,3,4,5], 2, Res).
  	%oddlist([0,1,2,3,4,5,6,7,8,9], Res).
  	%delete([1,2,2,2,2,2,1],2,Res).
  	%createSet([1,2,2,2,2,1,1,1], Res).
