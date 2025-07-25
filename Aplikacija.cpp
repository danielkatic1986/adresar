//
// Created by Daniel Katić on 25.07.2025.
//

#include "Aplikacija.h"
#include <cstring>

/**
 * @brief Funkcija koja se izvršava prije pokretanja glavne petlje
 */
void Aplikacija::prijePokretanja() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_RED); // Alert: bijeli tekst na crvenoj pozadini
        init_pair(2, COLOR_YELLOW, COLOR_RED); // Naslov: žuti tekst na crvenoj pozadini
    }
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
        switch (izbor) {
            case 0: {
                unosNoveStavke();
                break;
            }
                default: {
                break;
            }
        }
    }

    poslijePokretanja();
}

/**
 * @brief Pomoćna funkcija za unos teksta sa PDCurses bibliotekom
 * @param win pdcurses prozor
 * @param x horizontalna pozicija na ekranu
 * @param y vertikalna pozicija na ekranu
 * @param poruka poruka za prikaz kod unosa
 * @param maxDuljina maksimalna duljina unosa, default je 99
 * @return string koji je korisnik unesao
 */
std::string Aplikacija::unosTeksta(WINDOW *win, int x, int y, int maxDuljina) {
    wmove(win, y, x);
    char buffer[256] = {0};
    curs_set(1);
    echo();
    wgetnstr(win, buffer, maxDuljina);
    noecho();
    curs_set(0);

    return std::string(buffer);
}


/**
 * @brief Unos novog kontakta nakon što korisnik u meniju odabere 'Unos'
 */
void Aplikacija::unosNoveStavke() {
    int visina, sirina;
    getmaxyx(stdscr, visina, sirina);
    WINDOW* winAdresar = newwin(visina-7, sirina, 6, 0);

    const int xLabel = 2;
    const int xDvotocka = 14;
    const int xInput = xDvotocka + 2;
    const int yStart = 2;
    const int razmak = 2;

    const char* polja[] = {
        "Ime", "Prezime", "Adresa", "Kontakti", "Email adrese", "Opis"
    };

    const int brojPolja = sizeof(polja) / sizeof(polja[0]);
    std::string unosi[brojPolja];

    werase(winAdresar);
    box(winAdresar, 0, 0);

    // Ispis svih labela
    for (int i = 0; i < brojPolja; ++i) {
        int y = yStart + i * razmak;
        // Ispiši labelu
        mvwprintw(winAdresar, y, xLabel, "%s", polja[i]);
        // Ispiši točkice do dvotočke
        int duljinaLabele = strlen(polja[i]);
        for (int j = xLabel + duljinaLabele; j < xDvotocka; ++j) {
            mvwaddch(winAdresar, y, j, '.');
        }
        // Ispiši dvotočku
        mvwaddch(winAdresar, y, xDvotocka, ':');
    }
    wrefresh(winAdresar);

    // Unos za svako polje
    for (int i = 0; i < brojPolja; ++i) {
        unosi[i] = unosTeksta(winAdresar, xInput, yStart + i * razmak, 50);
        if (i == 0 && unosi[i].empty()){
            wrefresh(winAdresar);
            Meni::prikaziAlert("Ime je obavezno, probajte ponovno!");
            break;
        }
    }

    bool rezultat = adresar.dodaj(unosi[0], unosi[1], unosi[2], unosi[3], unosi[4], unosi[5]);

    delwin(winAdresar);
}