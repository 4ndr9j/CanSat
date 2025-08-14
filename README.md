# CanSat

Kod za CanSat takmicenje u Niksicu 2025.

U folderu bmp280 se nalazi kod za senzor temperature i pritiska. Dolazilo je do greske gdje senzor nije mogao biti pronadjen. U biblioteci je bila unijeta pogresna adresa. Senzor sa kojim radimo ima adresu 0x76, a njegov ChipID je na adresi 0x60.

U folderu main se nalazi kod za SIM800L modul i BMP280 senzor, koji bi trebalo da je priblizan finalnom.
Na dobijeni poziv, predvidjeno je da kod odbije poziv, preuzme podatke sa BMP280 senzora i posalje ih u vidu poruke na broj sa kojeg je dobio poziv.

Dodat je i prilog povezivanje.jpg gdje su prikazane sve konekcije i nacin povezivanja komponenti.
