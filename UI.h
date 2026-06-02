#pragma once
#include <ncurses.h>
#include <string>
#include <vector>
#include <locale.h>
#include "Spectacol.h"
using namespace std;

// Culori
#define COL_TITLU    1
#define COL_SELECTED 2
#define COL_NORMAL   3
#define COL_SUCCES   4
#define COL_EROARE   5
#define COL_ACCENT   6

void initUI() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();

    // Definire culori
    init_pair(COL_TITLU, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COL_SELECTED, COLOR_BLACK, COLOR_CYAN);
    init_pair(COL_NORMAL, COLOR_WHITE, COLOR_BLACK);
    init_pair(COL_SUCCES, COLOR_GREEN, COLOR_BLACK);
    init_pair(COL_EROARE, COLOR_RED, COLOR_BLACK);
    init_pair(COL_ACCENT, COLOR_MAGENTA, COLOR_BLACK);
}

void drawLogo(int startY, int startX) {
    attron(COLOR_PAIR(COL_TITLU) | A_BOLD);
    mvprintw(startY + 0, startX, "  __          ___      _  _       ___      __  __        _   ");
    mvprintw(startY + 1, startX, " / __|       |_ _|    | \\| |     | __|    |  \\/  |      /_\\  ");
    mvprintw(startY + 2, startX, "| (__         | |     | .` |     | _|     | |\\/| |     / _ \\ ");
    mvprintw(startY + 3, startX, " \\___|       |___|    |_|\\_|     |___|    |_|  |_|    /_/ \\_\\");
    attroff(COLOR_PAIR(COL_TITLU) | A_BOLD);

    attron(COLOR_PAIR(COL_ACCENT) | A_BOLD);
    mvprintw(startY + 5, startX + 10, "*** Sistem de Rezervari Cinema ***");
    attroff(COLOR_PAIR(COL_ACCENT) | A_BOLD);
}

void drawBorder() {
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    attron(COLOR_PAIR(COL_ACCENT));

    // Colturi
    mvprintw(0, 0, "+");
    mvprintw(0, cols - 1, "+");
    mvprintw(rows - 1, 0, "+");
    mvprintw(rows - 1, cols - 1, "+");

    // Linii orizontale
    for (int i = 1; i < cols - 1; i++) {
        mvprintw(0, i, "-");
        mvprintw(rows - 1, i, "-");
    }

    // Linii verticale
    for (int i = 1; i < rows - 1; i++) {
        mvprintw(i, 0, "|");
        mvprintw(i, cols - 1, "|");
    }

    attroff(COLOR_PAIR(COL_ACCENT));
}

int drawMeniu(const vector<string>& optiuni, const string& titlu, int selectat) {
    clear();
    drawBorder();

    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    // Logo
    drawLogo(1, (cols - 50) / 2);

    // Linie separatoare
    attron(COLOR_PAIR(COL_ACCENT));
    for (int i = 1; i < cols - 1; i++)
        mvprintw(10, i, "─");
    attroff(COLOR_PAIR(COL_ACCENT));

    // Titlu meniu
    attron(COLOR_PAIR(COL_TITLU) | A_BOLD);
    mvprintw(12, (cols - titlu.size()) / 2, "%s", titlu.c_str());
    attroff(COLOR_PAIR(COL_TITLU) | A_BOLD);

    // Optiuni
    for (int i = 0; i < optiuni.size(); i++) {
        int y = 14 + i * 2;
        int x = (cols - optiuni[i].size() - 6) / 2;

        if (i == selectat) {
            attron(COLOR_PAIR(COL_SELECTED) | A_BOLD);
            mvprintw(y, x - 2, " [>>] %s  ", optiuni[i].c_str());
            attroff(COLOR_PAIR(COL_SELECTED) | A_BOLD);
        }
        else {
            attron(COLOR_PAIR(COL_NORMAL));
            mvprintw(y, x - 2, "    %s  ", optiuni[i].c_str());
            attroff(COLOR_PAIR(COL_NORMAL));
        }
    }

    // Instructiuni jos
    attron(COLOR_PAIR(COL_ACCENT));
    mvprintw(rows - 2, (cols - 44) / 2, "[Sus/Jos] Navigare   [ENTER] Selectie   [Q] Iesire");
    attroff(COLOR_PAIR(COL_ACCENT));

    refresh();

    // Input
    int ch = getch();
    if (ch == KEY_UP && selectat > 0) return selectat - 1;
    if (ch == KEY_DOWN && selectat < optiuni.size() - 1) return selectat + 1;
    if (ch == 10) return -(selectat + 1); // Enter — returnează negativ ca semnal
    if (ch == 'q' || ch == 'Q') return -99;
    return selectat;
}

string inputField(const string& label, int y, int x) {
    attron(COLOR_PAIR(COL_TITLU));
    mvprintw(y, x, "%s", label.c_str());
    attroff(COLOR_PAIR(COL_TITLU));

    attron(COLOR_PAIR(COL_NORMAL));
    mvprintw(y, x + label.size() + 1, "                    ");
    attroff(COLOR_PAIR(COL_NORMAL));

    echo();
    curs_set(1);
    char buf[256];
    move(y, x + label.size() + 1);
    getnstr(buf, 255);
    noecho();
    curs_set(0);
    return string(buf);
}

void mesajSucces(const string& msg) {
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    attron(COLOR_PAIR(COL_SUCCES) | A_BOLD);
    mvprintw(rows - 4, (cols - msg.size()) / 2, "✓ %s", msg.c_str());
    attroff(COLOR_PAIR(COL_SUCCES) | A_BOLD);
    refresh();
    napms(1500);
}

void mesajEroare(const string& msg) {
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    attron(COLOR_PAIR(COL_EROARE) | A_BOLD);
    mvprintw(rows - 4, (cols - msg.size()) / 2, "✗ %s", msg.c_str());
    attroff(COLOR_PAIR(COL_EROARE) | A_BOLD);
    refresh();
    napms(1500);
}

vector<int> selectieLocuri(Spectacol* spectacol, int nrLocuri) {
    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    int capacitate = spectacol->getSala()->getCapacitate();
    int nrColoane = 10;
    int nrRanduri = (capacitate + nrColoane - 1) / nrColoane;

    vector<int> locuriSelectate;
    int cursorPos = 0;

    while (locuriSelectate.size() < nrLocuri) {
        clear();
        drawBorder();

        // Titlu
        attron(COLOR_PAIR(COL_TITLU) | A_BOLD);
        mvprintw(2, (cols - 30) / 2, "SELECTIE LOCURI - %s",
            spectacol->getFilm()->getTitlu().c_str());
        attroff(COLOR_PAIR(COL_TITLU) | A_BOLD);

        // Legenda
        attron(COLOR_PAIR(COL_SUCCES));
        mvprintw(4, 10, "[L] Liber");
        attroff(COLOR_PAIR(COL_SUCCES));

        attron(COLOR_PAIR(COL_EROARE));
        mvprintw(4, 25, "[X] Ocupat");
        attroff(COLOR_PAIR(COL_EROARE));

        attron(COLOR_PAIR(COL_TITLU));
        mvprintw(4, 40, "[*] Selectat");
        attroff(COLOR_PAIR(COL_TITLU));

        attron(COLOR_PAIR(COL_ACCENT) | A_BOLD);
        mvprintw(4, 58, "Selectate: %d/%d", (int)locuriSelectate.size(), nrLocuri);
        attroff(COLOR_PAIR(COL_ACCENT) | A_BOLD);

        // Ecran cinema
        attron(COLOR_PAIR(COL_ACCENT));
        mvprintw(6, (cols - 20) / 2, "=====  ECRAN  =====");
        attroff(COLOR_PAIR(COL_ACCENT));

        // Matrice locuri
        int startY = 8;
        int startX = (cols - nrColoane * 5) / 2;

        for (int i = 0; i < capacitate; i++) {
            int rand = i / nrColoane;
            int col = i % nrColoane;
            int y = startY + rand * 2;
            int x = startX + col * 5;

            bool eSelectat = false;
            for (int s : locuriSelectate)
                if (s == i) { eSelectat = true; break; }

            if (i == cursorPos) {
                attron(COLOR_PAIR(COL_SELECTED) | A_BOLD);
                mvprintw(y, x, "[%2d]", i + 1);
                attroff(COLOR_PAIR(COL_SELECTED) | A_BOLD);
            }
            else if (eSelectat) {
                attron(COLOR_PAIR(COL_TITLU) | A_BOLD);
                mvprintw(y, x, "[*%d]", i + 1);
                attroff(COLOR_PAIR(COL_TITLU) | A_BOLD);
            }
            else if (!spectacol->esteLocLiber(i)) {
                attron(COLOR_PAIR(COL_EROARE));
                mvprintw(y, x, "[XX]");
                attroff(COLOR_PAIR(COL_EROARE));
            }
            else {
                attron(COLOR_PAIR(COL_SUCCES));
                mvprintw(y, x, "[%2d]", i + 1);
                attroff(COLOR_PAIR(COL_SUCCES));
            }
        }

        // Instructiuni
        attron(COLOR_PAIR(COL_ACCENT));
        mvprintw(rows - 2, (cols - 50) / 2,
            "[Sageti] Navigare  [ENTER] Selecteaza  [Q] Anuleaza");
        attroff(COLOR_PAIR(COL_ACCENT));

        refresh();

        int ch = getch();
        if (ch == KEY_LEFT && cursorPos > 0)
            cursorPos--;
        else if (ch == KEY_RIGHT && cursorPos < capacitate - 1)
            cursorPos++;
        else if (ch == KEY_UP && cursorPos >= nrColoane)
            cursorPos -= nrColoane;
        else if (ch == KEY_DOWN && cursorPos + nrColoane < capacitate)
            cursorPos += nrColoane;
        else if (ch == 10) { // Enter
            if (!spectacol->esteLocLiber(cursorPos)) {
                // Loc ocupat
                attron(COLOR_PAIR(COL_EROARE) | A_BOLD);
                mvprintw(rows - 4, (cols - 24) / 2, "Locul %d este ocupat!", cursorPos + 1);
                attroff(COLOR_PAIR(COL_EROARE) | A_BOLD);
                refresh();
                napms(1000);
                continue;
            }

            bool eraSelectat = false;
            for (int k = 0; k < locuriSelectate.size(); k++) {
                if (locuriSelectate[k] == cursorPos) {
                    locuriSelectate.erase(locuriSelectate.begin() + k);
                    eraSelectat = true;
                    break;
                }
            }
            if (!eraSelectat)
                locuriSelectate.push_back(cursorPos);
        }
        else if (ch == 'q' || ch == 'Q') {
            locuriSelectate.clear();
            return locuriSelectate;
        }
    }

    // Confirmare finala
    clear(); drawBorder();
    int r2, c2; getmaxyx(stdscr, r2, c2);

    attron(COLOR_PAIR(COL_TITLU) | A_BOLD);
    mvprintw(2, (c2 - 20) / 2, "LOCURI SELECTATE");
    attroff(COLOR_PAIR(COL_TITLU) | A_BOLD);

    attron(COLOR_PAIR(COL_SUCCES) | A_BOLD);
    mvprintw(5, 10, "Ai selectat %d locuri:", nrLocuri);
    attroff(COLOR_PAIR(COL_SUCCES) | A_BOLD);

    int x = 10;
    for (int loc : locuriSelectate) {
        attron(COLOR_PAIR(COL_TITLU));
        mvprintw(7, x, "[%d]", loc + 1);
        attroff(COLOR_PAIR(COL_TITLU));
        x += 6;
    }

    attron(COLOR_PAIR(COL_ACCENT));
    mvprintw(r2 - 2, (c2 - 36) / 2, "[ENTER] Confirma    [Q] Reselecteaza");
    attroff(COLOR_PAIR(COL_ACCENT));
    refresh();

    int ch = getch();
    if (ch == 'q' || ch == 'Q') {
        locuriSelectate.clear();
        return selectieLocuri(spectacol, nrLocuri);
    }

    return locuriSelectate;
}