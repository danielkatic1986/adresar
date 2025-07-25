//
// Created by danie on 24.7.2025.
//

#ifndef STAVKA_H
#define STAVKA_H

#include <string>

struct Stavka {
    int id;
    std::string ime;
    std::string prezime;
    std::string adresa;
    std::string kontakti[5];
    std::string emailAdrese[5];
    std::string opis;
};

int generirajNoviID();
int dohvatiZadnjiID();

#endif //STAVKA_H
