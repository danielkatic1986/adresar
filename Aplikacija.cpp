//
// Created by Daniel Katić on 25.07.2025.
//

#include "Aplikacija.h"

void Aplikacija::prijePokretanja() {

}

void Aplikacija::poslijePokretanja() {

}

char Aplikacija::traziUnos() {
    char n;
    std::cout << "Unesite izbor: ";
    std::cin >> n;
    return n;
}

std::string Aplikacija::unos(const std::string& poruka) {
    std::string unos;
    std::cout << poruka << std::endl;
    std::cin.ignore();
    std::getline(std::cin, unos);
    return unos;
}

void Aplikacija::petlja() {
    prijePokretanja();

    // Glavna petlja aplikacije
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
