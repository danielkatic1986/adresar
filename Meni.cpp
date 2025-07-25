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

    int visina, sirina;
    getmaxyx(win, visina, sirina);

    // Minimalne i preporučene širine
    const int minID = 3, minIme = 6, minPrezime = 8, minAdresa = 10, minBrojevi = 10, minEmailovi = 10, minOpis = 5;
    int wID = 3, wIme = 12, wPrezime = 12, wAdresa = 16, wBrojevi = 16, wEmailovi = 18;

    // Zbroji širine svih stupaca osim Opisa (+6 za razmake)
    int fiksno = wID + wIme + wPrezime + wAdresa + wBrojevi + wEmailovi + 6;

    // Ako nema dovoljno mjesta, smanji sve stupce na minimum
    if (sirina < fiksno + minOpis) {
        wID = minID; wIme = minIme; wPrezime = minPrezime; wAdresa = minAdresa; wBrojevi = minBrojevi; wEmailovi = minEmailovi;
        fiksno = wID + wIme + wPrezime + wAdresa + wBrojevi + wEmailovi + 6;
    }

    // Ostatak ide za Opis
    int wOpis = sirina - fiksno;
    if (wOpis < minOpis) wOpis = minOpis;

    // Izračunaj x pozicije
    int xID = 2;
    int xIme = xID + wID + 1;
    int xPrezime = xIme + wIme + 1;
    int xAdresa = xPrezime + wPrezime + 1;
    int xBrojevi = xAdresa + wAdresa + 1;
    int xEmailovi = xBrojevi + wBrojevi + 1;
    int xOpis = xEmailovi + wEmailovi + 1;

    // Header
    mvwprintw(win, 1, xID,      "ID");
    mvwprintw(win, 1, xIme,     "Ime");
    mvwprintw(win, 1, xPrezime, "Prezime");
    mvwprintw(win, 1, xAdresa,  "Adresa");
    mvwprintw(win, 1, xBrojevi, "Brojevi");
    mvwprintw(win, 1, xEmailovi,"Emailovi");
    mvwprintw(win, 1, xOpis,    "Opis");

    for (int x = 1; x < sirina - 1; ++x)
        mvwaddch(win, 2, x, ACS_HLINE);

    int y = 3;
    for (int i = 0; i < Adresar::zadnjiID; ++i) {
        const Stavka& s = adresar.stavke[i];
        mvwprintw(win, y, xID,      "%s", skratiZaPrikaz(std::to_string(s.id), wID).c_str());
        mvwprintw(win, y, xIme,     "%s", skratiZaPrikaz(s.ime, wIme).c_str());
        mvwprintw(win, y, xPrezime, "%s", skratiZaPrikaz(s.prezime, wPrezime).c_str());
        mvwprintw(win, y, xAdresa,  "%s", skratiZaPrikaz(s.adresa, wAdresa).c_str());

        // Brojevi
        std::string brojevi;
        for (int j = 0; j < 5; ++j) {
            if (!s.kontakti[j].empty()) {
                if (!brojevi.empty()) brojevi += ", ";
                brojevi += s.kontakti[j];
            }
        }
        mvwprintw(win, y, xBrojevi, "%s", skratiZaPrikaz(brojevi, wBrojevi).c_str());

        // Emailovi
        std::string emailovi;
        for (int j = 0; j < 5; ++j) {
            if (!s.emailAdrese[j].empty()) {
                if (!emailovi.empty()) emailovi += ", ";
                emailovi += s.emailAdrese[j];
            }
        }
        mvwprintw(win, y, xEmailovi, "%s", skratiZaPrikaz(emailovi, wEmailovi).c_str());

        // Opis
        mvwprintw(win, y, xOpis, "%s", skratiZaPrikaz(s.opis, wOpis).c_str());

        ++y;
    }

    wrefresh(win);
}

int Meni::prikaz(Adresar& adresar) {
    int visina, sirina;
    getmaxyx(stdscr, visina, sirina);

    WINDOW* winNaslov  = newwin(3, sirina, 0, 0);                   // 3 reda: okvir + tekst + okvir
    WINDOW* winMeni    = newwin(3, sirina, 3, 0);                   // 3 reda: okvir + tekst + okvir
    WINDOW* winAdresar = newwin(visina - 7, sirina, 6, 0);          // ostatak (od reda 6 do visina-2)
    WINDOW* winStatus  = newwin(1, sirina, visina - 1, 0);          // zadnji red

    int izbor = 0;
    int ch;

    while (true) {
        refresh();
        prikazNaslova(winNaslov);
        prikazGlavnogMenija(winMeni, izbor);
        prikazAdresara(winAdresar, adresar);

        // Prikaz status bara (možeš ovdje staviti poruku po želji)
        werase(winStatus);
        wattron(winStatus, A_REVERSE);
        mvwprintw(winStatus, 0, 1, "F10 za izlaz | Enter za odabir | Strelice za kretanje");
        wattroff(winStatus, A_REVERSE);
        wrefresh(winStatus);

        ch = getch();
        if (ch == KEY_LEFT) {
            if (izbor > 0) izbor--;
        } else if (ch == KEY_RIGHT) {
            if (izbor < BROJ_STAVKI - 1) izbor++;
        } else if (ch == '\n' || ch == KEY_ENTER) {
            break;
        } else if (ch == KEY_F(10)) {
            izbor = BROJ_STAVKI - 1; // npr. zadnja stavka je "Izlaz"
            break;
        }
    }

    // Oslobodi prozore (opcionalno, ako ih ne koristiš dalje)
    delwin(winNaslov);
    delwin(winMeni);
    delwin(winAdresar);
    delwin(winStatus);

    return izbor;
}

std::string Meni::skratiZaPrikaz(const std::string& tekst, size_t maxDuljina) {
    if (tekst.length() <= maxDuljina) return tekst;
    if (maxDuljina <= 3) return tekst.substr(0, maxDuljina); // edge case
    return tekst.substr(0, maxDuljina - 3) + "...";
}

void Meni::prikaziAlert(const std::string& poruka, const std::string& naslov) {
    int visina, sirina;
    getmaxyx(stdscr, visina, sirina);

    int w = std::max(std::max((int)poruka.length(), (int)naslov.length()), 24) + 8;
    int h = 7;
    int y = (visina - h) / 2;
    int x = (sirina - w) / 2;

    WINDOW* winAlert = newwin(h, w, y, x);

    // Cijeli prozor u crvenoj pozadini
    if (has_colors()) wbkgd(winAlert, COLOR_PAIR(1));
    werase(winAlert);
    box(winAlert, 0, 0);

    // Naslov (žuto na crvenom, podebljano)
    if (has_colors()) wattron(winAlert, COLOR_PAIR(2));
    wattron(winAlert, A_BOLD);
    mvwprintw(winAlert, 1, (w - naslov.length()) / 2, "%s", naslov.c_str());
    wattroff(winAlert, A_BOLD);
    if (has_colors()) wattroff(winAlert, COLOR_PAIR(2));

    // Poruka (bijelo na crvenom)
    if (has_colors()) wattron(winAlert, COLOR_PAIR(1));
    mvwprintw(winAlert, 3, (w - poruka.length()) / 2, "%s", poruka.c_str());
    if (has_colors()) wattroff(winAlert, COLOR_PAIR(1));

    // Uputa
    mvwprintw(winAlert, h - 2, (w - 24) / 2, "Pritisni bilo koju tipku...");

    wrefresh(winAlert);
    wgetch(winAlert);

    delwin(winAlert);
    touchwin(stdscr);
    refresh();
}