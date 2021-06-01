list_collide1([], _, []) :- !.
list_collide1([H|_], X, Res) :- X is H, Res = H, !.
list_collide1([_|T], X, Res) :- list_collide1(T, X, Res).

list_collide([], _, _) :- !.
list_collide([H|T], List2, [Result]) :- list_collide(T, List2, [Tmp|Result]), list_collide1(List2, H, Tmp).

%list_collide([1, 2, 3, 4], [3, 4, 5, 6], Result)
%list_collide1([1, 2, 3, 4], 3, Res).
