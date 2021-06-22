domains
	name, sex = symbol
	
predicates
	parent(name, sex, name).
	grands(name, name, name, name, name).
	
clauses 
	parent("Irina", "woman", "Nikita"). % Nikita`s mother is Irina
	parent("Raya", "woman", "Irina"). % Irina`s mother is Raya
	parent("Vera", "woman", "Alex"). % Alex`s mother is Vera
	parent("Alex", "man", "Nikita"). % Nikita`s mother is Alex
	parent("Anatoly", "man", "Alex"). % Alex`s mother is Anatoly
	parent("Vitaliy", "man", "Irina"). % Vitaliya`s mother is Irina
	
	grands(Name, MotherMother, MotherFather, FatherMother, FatherFather):-
	parent(Mother, "woman", Name), 
	parent(MotherMother, "woman", Mother),
	parent(MotherFather, "man", Mother), 
	parent(Father,"man", Name),
	parent(FatherMother,"woman", Father), 
	parent(FatherFather,"man", Father).
goal
	grands("Nikita", MotherMother, MotherFather, _, _).