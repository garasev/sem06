domains
	name, surname, group, university = symbol.
	age = integer.
predicates
	study(name, surname, age, group, university).
	studentByUniversity(name, surname, group, university).
clauses
	study("Dmitry", "Kulikov", 20, "IU7-62B", "BMSTU").
	study("Vladimir", "Markeev", 21, "112", "MRSU").
	study("Dmitry", "Kulikov", 20, "112", "MRSU").
	study("Danila", "Spirin", 21, "31", "FSIN").
	study("Andrey", "Chalyy", 20, "32", "FSIN").
	study("Nikita", "Garasev", 19, "IU7-62B", "BMSTU").
	study("Andrey", "Chalyy", 20, "IU7-66B", "BMSTU").
	studentByUniversity(N, S, G, U) :- study(N, S, _, G, U).
goal
	study(Name, Surname, Age, Group, "BMSTU"), nl.
