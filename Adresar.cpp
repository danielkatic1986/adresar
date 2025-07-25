//
// Created by danie on 24.7.2025.
//

#include "Adresar.h"
#include "Stavka.h"

#include <iostream>
#include <string>
#include <cstring>
#include <ranges>

int Adresar::zadnjiID = 0;

bool Adresar::dodaj(std::string ime, std::string prezime, std::string adresa,
             std::string kontakt, std::string email, std::string opis) {

    if (ime.empty()) return false;

    Stavka temp;
    temp.id = generirajNoviID();
    temp.ime = ime;
    temp.prezime = prezime;
    temp.adresa = adresa;
    temp.opis = opis;

    splitZarez(kontakt.c_str(), temp.kontakti, MAX_KONTAKTA);
    splitZarez(email.c_str(), temp.emailAdrese, MAX_EMAILADRESA);

    // TODO: Ukoliko je ime prazno onda ne dodati ništa
    this->stavke[temp.id] = temp;
    zadnjiID = ++temp.id;

    return true;
}

void Adresar::splitZarez(const char *unos, std::string polje[], int maxPolja) {
    char temp[256];
    strncpy(temp, unos, sizeof(temp));
    temp[sizeof(temp) - 1] = '\0';

    char* token = strtok(temp, ",");
    int i=0;
    while (token != nullptr && i < maxPolja) {
        while (*token == ' ' || *token == '\t') ++token;
        char* kraj = token + strlen(token) - 1;
        while (kraj > token && (*kraj == ' ' || *kraj == '\t')) *kraj-- = '\0';
        polje[i++] = std::string(token);
        token = strtok(nullptr, ",");
    }

    for (; i < maxPolja; ++i) polje[i].clear();
}
