//
// Created by Daniel Katić on 25.07.2025.
//

#include "Meni.h"
#include <curses.h>

Meni::Meni() {
    stavke[0] = "Unos";
    stavke[1] = "Izmjena";
    stavke[2] = "Brisanje";
    stavke[3] = "Sortiranje";
    stavke[4] = "Izlaz";
}

void Meni::prikazGlavnogMenija(WINDOW *win, int izbor) const {
    werase(win);
    box(win, 0, 0);

    for (int i=0; i < BROJ_STAVKI; i++) {
        if (i == izbor) {
            wattron(win, A_REVERSE);
            mvwprintw(win, 1, 2 + i * 15, "%s", stavke[i].c_str());
            wattroff(win, A_REVERSE);
        } else {
            mvwprintw(win, 1, 2 + i * 15, "%s", stavke[i].c_str());
        }
    }

    wrefresh(win);
}

void Meni::prikazNaslova(WINDOW *win) const {
    werase(win);
    box(win, 0, 0);
    std::string naslov = "Adresar";
    int x = (getmaxx(win) - naslov.size()) / 2;
    mvwprintw(win, 1, x, "%s", naslov.c_str());
    wrefresh(win);
}

void Meni::prikazAdresara(WINDOW *win, const Adresar& adresar) const {
    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 1, 2, "Popis osoba:");
    for (int i = 0; i < adresar.zadnjiID; ++i) {
        mvwprintw(win, 2 + i, 4, "%s", adresar.stavke[i].ime.c_str());
    }
    wrefresh(win);
}


int Meni::prikaz(Adresar& adresar) {
    int visina, sirina;
    getmaxyx(stdscr, visina, sirina);

    // Prozor za meni (gore)
    WINDOW* winNaslov = newwin(3, sirina, 0, 0);
    // Prozor za naslov (sredina)
    WINDOW* winMeni = newwin(3, sirina, 3, 0);
    // Prozor za adresar (ispod)
    WINDOW* winAdresar = newwin(visina - 6, sirina, 6, 0);

    int izbor = 0;
    int ch;

    while (true) {
        refresh();
        prikazNaslova(winNaslov);
        prikazGlavnogMenija(winMeni, izbor);
        prikazAdresara(winAdresar, adresar);

        ch = getch();
        if (ch == KEY_LEFT) {
            if (izbor > 0) izbor--;
        } else if (ch == KEY_RIGHT) {
            if (izbor < BROJ_STAVKI - 1) izbor++;
        } else if (ch == '\n' || ch == KEY_ENTER) {
            break;
        }
    }
    return izbor;
}
