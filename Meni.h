//
// Created by Daniel Katić on 25.07.2025..
//

#ifndef MENI_H
#define MENI_H

#include <string>
#include <curses.h>

#include "Adresar.h"

constexpr short BROJ_STAVKI = 5;

struct Meni {
    std::string stavke[BROJ_STAVKI];
    Meni();
    int prikaz(Adresar& adresar);
    void prikazGlavnogMenija(WINDOW* win, int izbor) const;
    void prikazNaslova(WINDOW* win) const;
    void prikazAdresara(WINDOW *win, const Adresar& adresar) const;
};

#endif //MENI_H
