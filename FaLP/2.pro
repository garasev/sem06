mother("nikita", "irina").
mother("irina", "raya").
mother("raya", "vera").
mother("vera", "sonya").

k_mother(Name, 0, Name) :- !.
k_mother(Name, K, Res) :- mother(Name, Mom), K2 is K - 1, k_mother(Mom, K2, Res).

%k_mother("nikita", 2, Res).

