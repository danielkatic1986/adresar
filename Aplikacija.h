//
// Created by Daniel Katić on 25.07.2025..
//

#ifndef APLIKACIJA_H
#define APLIKACIJA_H

#include "Adresar.h"
#include "Meni.h"
#include <string>
#include <curses.h>

struct Aplikacija {
    Adresar adresar;
    Meni meni;

    bool izvrsavaj = true;
    char izbor = 0;

    void prijePokretanja();
    void petlja();
    void poslijePokretanja();
    void unosNoveStavke();

    std::string unosTeksta(WINDOW* win, int x, int y, int maxDuljina = 99);
};

#endif //APLIKACIJA_H
