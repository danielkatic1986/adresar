//
// Created by danie on 24.7.2025.
//

#ifndef ADRESAR_H
#define ADRESAR_H

#include <string>
#include "Stavka.h"

struct Adresar {
  Stavka stavke[1000];

  bool dodaj(std::string ime, std::string prezime, std::string adresa,
             std::string kontakt, std::string email, std::string opis);
};

#endif //ADRESAR_H
