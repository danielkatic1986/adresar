//
// Created by danie on 24.7.2025.
//

#ifndef STAVKA_H
#define STAVKA_H

#include <string>

constexpr short MAX_KONTAKTA = 5;
constexpr short MAX_EMAILADRESA = 5;

struct Stavka {
    int id;
    std::string ime;
    std::string prezime;
    std::string adresa;
    std::string kontakti[MAX_KONTAKTA];
    std::string emailAdrese[MAX_EMAILADRESA];
    std::string opis;
};

int generirajNoviID();
int dohvatiZadnjiID();

#endif //STAVKA_H
