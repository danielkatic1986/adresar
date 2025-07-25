//
// Created by Daniel Katić on 25.07.2025.
//

#include "Aplikacija.h"

/**
 * @brief Funkcija koja se izvršava prije pokretanja glavne petlje
 */
void Aplikacija::prijePokretanja() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
}

/**
 * @brief Funkcija koja se izvršava nakon što je glavna petlja završila
 */
void Aplikacija::poslijePokretanja() {
    curs_set(1);
    endwin();
}


/**
 * @brief Glavna petlja aplikacije
 *
 * Prikazuje glavni meni, obrađuje korisnički unos i poziva odgovarajuće funkcije
 * za dodavanje, izlaz i ostale opcije. Petlja traje dok korisnik ne odabere izlaz.
 */
void Aplikacija::petlja() {
    prijePokretanja();

    while (izbor != 4) {
        izbor = static_cast<char>(meni.prikaz(adresar));
    }

    poslijePokretanja();
}
