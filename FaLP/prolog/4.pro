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
	infoByBrandAndColor(brand, color, surname, city, phone, bank).
	
clauses 
        person("Garasev", "89273141395", adress("Moscow", "Kapotnoua", 19, 110)).
	person("Garasev", "89222341333", adress("Belgorod", "Smolenskaya", 29, 112)).
	person("Kulikov", "89271939173", adress("Saransk", "Kovalenko", 7, 89)).
	person("Kulikov", "89272030284", adress("Saransk", "Kovalenko", 7, 89)).
	person("Garasev", "89273141395", adress("Moscow", "Kapotnoua", 19, 110)).
	person("Garasev", "89222341333", adress("Belgorod", "Smolenskaya", 29, 112)).
	person("Chalyy", "892722822832", adress("Anadyr", "Morshovaya", 18, 322)).
	
	car("Kulikov", "Audi", "white", 4500000).
	car("Kulikov", "Audi", "black", 1500000).
	car("Garasev", "BMW X6", "pink", 7500000).
	car("Garasev", "Audi", "black", 1500000).
	car("Chalyy", "Bugatti", "gold", 7500000).
	car("Chalyy", "Lada Vesta", "white", 500000).
	
	depositor("Kulikov", "Sberbank", "11111", 1500).
	depositor("Kulikov", "Tinkoff", "22222", 3500).
	depositor("Garasev", "Tinkoff", "22822", 7500).
	depositor("Chalyy", "SelhozBank", "33333", 500).
	
	infoByBrandAndColor(Brand, Color, Surname, City, Phone, Bank):- 
	car(Surname, Brand, Color, _),
	person(Surname, Phone, adress(City, _, _, _)),
	depositor(Surname, Bank, _ , _).
goal 
	infoByBrandAndColor("Bugatti", "black", Surname, City, Phone, Bank).
