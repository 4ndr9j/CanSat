# CanSat

Kod za CanSat takmicenje u Niksicu 2025.

U folderu bmp280 se nalazi kod za senzor temperature i pritiska. Dolazilo je do greske gdje senzor nije mogao biti pronadjen. U biblioteci je bila unijeta pogresna adresa. Senzor sa kojim radimo ima adresu 0x76, a njegov ChipID je na adresi 0x60.
