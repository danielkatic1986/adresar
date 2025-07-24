#include <iostream>
#include <cctype>

#include "tabulate.hpp"

#include "Adresar.h"

void ispisMenija(const tabulate::Table& meni) {
    std::cout << meni << std::endl;
}

int main() {
    Adresar adresar;
    tabulate::Table meni;
    meni.add_row({"Funkcija", "Naredba"});
    meni.add_row({"Prikaz adresara", "1"});
    meni.add_row({"Dodaj novu stavku", "2"});
    meni.add_row({"Editiraj stavku", "3"});
    meni.add_row({"Izbrisi stavku", "4"});
    meni.add_row({"Izlaz", "x"});

    meni[0].format()
    .padding_top(1)
    .padding_bottom(1)
    .font_align(tabulate::FontAlign::center)
    .font_style({tabulate::FontStyle::underline})
    .font_background_color(tabulate::Color::red);

    meni.column(1).format()
        .font_align(tabulate::FontAlign::center);

    bool izvrsavaj = true;
    char izbor = 0;

    while (izvrsavaj) {
        ispisMenija(meni);
        std::cout << "Unesite izbor: ";
        std::cin >> izbor;
        switch (std::tolower(izbor)) {
            case 'x':
                izvrsavaj = false;
            break;
            default:
                std::cout << "Krivi izbor, pokusajte ponovno!\n";
            break;
        }
    }
    
    return 0;
}