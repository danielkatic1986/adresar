//
// Created by Daniel Katić on 25.07.2025..
//

#ifndef APLIKACIJA_H
#define APLIKACIJA_H

#include "Adresar.h"
#include "Meni.h"

struct Aplikacija {
    Adresar adresar;
    Meni meni;

    bool izvrsavaj = true;
    char izbor = 0;

    static void prijePokretanja();
    void petlja();

    static void poslijePokretanja();

    static char traziUnos();

    static std::string unos(const std::string& poruka);
};

#endif //APLIKACIJA_H
