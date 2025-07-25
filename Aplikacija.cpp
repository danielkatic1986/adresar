//
// Created by Daniel Katić on 25.07.2025.
//

#include "Aplikacija.h"

/**
 * @brief Funkcija koja se izvršava prije pokretanja glavne petlje
 */
void Aplikacija::prijePokretanja() {

}

/**
 * @brief Funkcija koja se izvršava nakon što je glavna petlja završila
 */
void Aplikacija::poslijePokretanja() {

}

/**
 * @brief Unos jednog chara
 *
 *  Funkcija ispisuje "Unesite izbor: " i zatim vraća uneseni karakter.
 *  Koristi se u meniju za dohvaćanje izbora korisnika.
 *
 * @return char unosa korisnika
 */
char Aplikacija::traziUnos() {
    char n;
    std::cout << "Unesite izbor: ";
    std::cin >> n;
    return n;
}

/**
 * @brief Unos stringa pomoću getline, koristi se za unos stavki
 * @param poruka string koji će se prikazati korisniku tijekom unosa
 * @return vraća uneseni string, koristi se getline pa se može unijeti i razmak
 */
std::string Aplikacija::unos(const std::string& poruka) {
    std::string unos;
    std::cout << poruka << std::endl;
    std::cin.ignore();
    std::getline(std::cin, unos);
    return unos;
}

/**
 * @brief Glavna petlja aplikacije
 *
 * Prikazuje glavni meni, obrađuje korisnički unos i poziva odgovarajuće funkcije
 * za dodavanje, izlaz i ostale opcije. Petlja traje dok korisnik ne odabere izlaz.
 */
void Aplikacija::petlja() {
    prijePokretanja();

    while (izvrsavaj) {
        meni.ispisGlavniMeni();
        izbor = traziUnos();
        switch (izbor) {
            case '1': {
                Stavka temp;
                temp.id = generirajNoviID();
                temp.ime = unos("Ime: ");
                temp.prezime = unos("Prezime: ");
                temp.adresa = unos("Adresa: ");
                temp.kontakti[0] = unos("Kontakt: ");
                temp.emailAdrese[0] = unos("Email: ");
                temp.opis = unos("Opis: ");
                adresar.dodaj("Daniel", "Katic", "Zezelovo selo 29", "0921175505", "danielkatic@gmail.com", "Proba");
                std::cout << "Nova stavka dodana u adresar." << std::endl;
                break;
            }
            case 'x': {
                izvrsavaj = false;
                break;
            }
            default: {
                std::cout << "Krivi izbor, pokusajte ponovno!\n";
                break;
            }
        }
    }

    poslijePokretanja();
}
