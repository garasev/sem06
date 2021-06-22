domains
	surname = symbol.
	phone = symbol.
	city = symbol.
	street = symbol.
	house = integer.
	flat = integer.
	adress = adress(city, street, house, flat).
	brand = symbol.
	color = symbol.
	price = integer.
	bank = symbol.
	account = symbol.
	amount = integer.
	
predicates
	person(surname, phone, adress).
	car(surname, brand, color, price).
	depositor(surname, bank, account, amount).
	carByPhone(phone, surname, brand, price).
	modelByPhone(phone, brand).
	accountAndPhoneBySurnameAndCity(surname, city, street, phone, bank).
	
clauses 
	person("Garasev", "89273141395", adress("Moscow", "Kapotnoua", 19, 110)).
	person("Kulikov", "89271939173", adress("Saransk", "Kovalenko", 7, 89)).
	person("Kulikov", "89272030284", adress("Saransk", "Kovalenko", 7, 89)).
	person("Chalyy", "892722822832", adress("Anadyr", "Morshovaya", 18, 322)).
	person("Kulikov", "89273222280", adress("Moscow", "Kurskya", 25, 2)).
	person("Kulikov", "89273222281", adress("Moscow", "Kurskya", 25, 2)).
	
	car("Garasev", "BMW X6", "pink", 7500000).
	car("Kulikov", "Audi A6", "white", 4500000).
	car("Kulikov", "Audi A4", "black", 1500000).
	car("Chalyy", "Bugatti", "gold", 7500000).
	car("Chalyy", "Lada Vesta", "white", 500000).
	
	depositor("Garasev", "Tinkoff", "22822", 7500).
	depositor("Garasev", "VTB", "23822", 6500).
	depositor("Kulikov", "Sberbank", "11111", 1500).
	depositor("Kulikov", "Tinkoff", "22222", 3500).
	depositor("Chalyy", "SelhozBank", "33333", 500).
	
	carByPhone(Phone, Surname, Brand, Price) :- person(Surname, Phone,_), 
           car(Surname, Brand, _, Price). 
	
	modelByPhone(Phone, Brand) :- carByPhone(Phone, _, Brand, _).
	
	accountAndPhoneBySurnameAndCity(Surname, City, Street, Phone, Bank) :- 
	person(Surname, Phone, adress(City, Street, _, _)), depositor(Surname, Bank, _, _).
	
goal
	carByPhone("89271939173", Surname, Brand, Price), nl.
	%modelByPhone("892722822832", Brand).
	%accountAndPhoneBySurnameAndCity("Kulikov", "Saransk", Street, Phone, Bank), nl.
