//
// Created by danie on 24.7.2025.
//

#include "Adresar.h"
#include "Stavka.h"

#include <iostream>
#include <string>

int Adresar::zadnjiID = 0;

bool Adresar::dodaj(std::string ime, std::string prezime, std::string adresa,
             std::string kontakt, std::string email, std::string opis) {

    Stavka temp;
    temp.id = generirajNoviID();
    temp.ime = ime;
    temp.prezime = prezime;
    temp.adresa = adresa;
    temp.kontakti[0] = kontakt;
    temp.emailAdrese[0] = email;
    temp.opis = opis;

    this->stavke[temp.id] = temp;
    zadnjiID = temp.id;

    return true;
}
