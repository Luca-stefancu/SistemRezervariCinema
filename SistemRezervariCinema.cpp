#include <iostream>
#include <vector>
#include <string>
#include "Film.h"
#include "Sala.h"
#include "Client.h"
#include "Spectacol.h"
#include "Rezervare.h"
#include "Raport.h"
#include "UI.h"
#include <locale.h>
#include "Storage.h"
#include <map>

using namespace std;

vector<Film*> filme;
vector<Sala*> sali;
vector<Client*> clienti;
vector<Spectacol*> spectacole;
vector<Rezervare*> rezervari;

// ==================== FILME ====================
void gestionareFilme() {
    vector<string> optiuni = { "Adauga film", "Afiseaza filme", "Inapoi" };
    int sel = 0;

    while (true) {
        int result = drawMeniu(optiuni, "GESTIONARE FILME", sel);
        if (result == -99) return;
        if (result < 0) {
            int ales = -(result + 1);
            if (ales == 2) return;

            if (ales == 0) {
                clear(); drawBorder();
                int rows, cols; getmaxyx(stdscr, rows, cols);
                attron(COLOR_PAIR(COL_TITLU) | A_BOLD);
                mvprintw(2, (cols - 20) / 2, "ADAUGA FILM");
                attroff(COLOR_PAIR(COL_TITLU) | A_BOLD);

                string titlu = inputField("Titlu   :", 6, 10);
                string gen = inputField("Gen     :", 8, 10);
                string durStr = inputField("Durata  :", 10, 10);
                string ratStr = inputField("Rating  :", 12, 10);

                filme.push_back(new Film(titlu, gen, stoi(durStr), stof(ratStr)));
                mesajSucces("Film adaugat cu succes!");
            }

            if (ales == 1) {
                clear(); drawBorder();
                int rows, cols; getmaxyx(stdscr, rows, cols);
                attron(COLOR_PAIR(COL_TITLU) | A_BOLD);
                mvprintw(2, (cols - 20) / 2, "LISTA FILME");
                attroff(COLOR_PAIR(COL_TITLU) | A_BOLD);

                if (filme.empty()) {
                    mesajEroare("Nu exista filme!");
                }
                else {
                    int y = 5;
                    for (int i = 0; i < filme.size(); i++) {
                        attron(COLOR_PAIR(COL_ACCENT) | A_BOLD);
                        mvprintw(y++, 10, "[%d] %s", i, filme[i]->getTitlu().c_str());
                        attroff(COLOR_PAIR(COL_ACCENT) | A_BOLD);
                        attron(COLOR_PAIR(COL_NORMAL));
                        mvprintw(y++, 12, "Gen: %s | Durata: %d min | Rating: %.1f",
                            filme[i]->getGen().c_str(),
                            filme[i]->getDurata(),
                            filme[i]->getRating());
                        attroff(COLOR_PAIR(COL_NORMAL));
                        y++;
                    }
                    attron(COLOR_PAIR(COL_ACCENT));
                    mvprintw(rows - 2, (cols - 30) / 2, "Apasa orice tasta pentru a continua");
                    attroff(COLOR_PAIR(COL_ACCENT));
                    refresh(); getch();
                }
            }
        }
        else sel = result;
    }
}

// ==================== SALI ====================
void gestionareSali() {
    vector<string> optiuni = { "Adauga sala", "Afiseaza sali", "Inapoi" };
    int sel = 0;

    while (true) {
        int result = drawMeniu(optiuni, "GESTIONARE SALI", sel);
        if (result == -99) return;
        if (result < 0) {
            int ales = -(result + 1);
            if (ales == 2) return;

            if (ales == 0) {
                clear(); drawBorder();
                int rows, cols; getmaxyx(stdscr, rows, cols);
                attron(COLOR_PAIR(COL_TITLU) | A_BOLD);
                mvprintw(2, (cols - 20) / 2, "ADAUGA SALA");
                attroff(COLOR_PAIR(COL_TITLU) | A_BOLD);

                string nrStr = inputField("Numar sala  :", 6, 10);
                string capStr = inputField("Capacitate  :", 8, 10);
                string tip = inputField("Tip (2D/3D/IMAX):", 10, 10);

                sali.push_back(new Sala(stoi(nrStr), stoi(capStr), tip));
                mesajSucces("Sala adaugata cu succes!");
            }

            if (ales == 1) {
                clear(); drawBorder();
                int rows, cols; getmaxyx(stdscr, rows, cols);
                attron(COLOR_PAIR(COL_TITLU) | A_BOLD);
                mvprintw(2, (cols - 20) / 2, "LISTA SALI");
                attroff(COLOR_PAIR(COL_TITLU) | A_BOLD);

                if (sali.empty()) {
                    mesajEroare("Nu exista sali!");
                }
                else {
                    int y = 5;
                    for (int i = 0; i < sali.size(); i++) {
                        attron(COLOR_PAIR(COL_ACCENT) | A_BOLD);
                        mvprintw(y++, 10, "[%d] Sala %d", i, sali[i]->getNumarSala());
                        attroff(COLOR_PAIR(COL_ACCENT) | A_BOLD);
                        attron(COLOR_PAIR(COL_NORMAL));
                        mvprintw(y++, 12, "Capacitate: %d | Tip: %s",
                            sali[i]->getCapacitate(),
                            sali[i]->getTip().c_str());
                        attroff(COLOR_PAIR(COL_NORMAL));
                        y++;
                    }
                    attron(COLOR_PAIR(COL_ACCENT));
                    mvprintw(rows - 2, (cols - 30) / 2, "Apasa orice tasta pentru a continua");
                    attroff(COLOR_PAIR(COL_ACCENT));
                    refresh(); getch();
                }
            }
        }
        else sel = result;
    }
}

// ==================== CLIENTI ====================
void gestionareClienti() {
    vector<string> optiuni = { "Adauga client", "Afiseaza clienti", "Inapoi" };
    int sel = 0;

    while (true) {
        int result = drawMeniu(optiuni, "GESTIONARE CLIENTI", sel);
        if (result == -99) return;
        if (result < 0) {
            int ales = -(result + 1);
            if (ales == 2) return;

            if (ales == 0) {
                clear(); drawBorder();
                int rows, cols; getmaxyx(stdscr, rows, cols);
                attron(COLOR_PAIR(COL_TITLU) | A_BOLD);
                mvprintw(2, (cols - 20) / 2, "ADAUGA CLIENT");
                attroff(COLOR_PAIR(COL_TITLU) | A_BOLD);

                string idStr = inputField("ID       :", 5, 10);
                string nume = inputField("Nume     :", 7, 10);
                string prenume = inputField("Prenume  :", 9, 10);
                string email = inputField("Email    :", 11, 10);
                string telefon = inputField("Telefon  :", 13, 10);

                vector<string> tipuri = { "Normal", "Student (20%)", "Pensionar (30%)", "Membru fidel (10%)" };
                int tipSel = 0;
                while (true) {
                    int r = drawMeniu(tipuri, "ALEGE TIP CLIENT", tipSel);
                    if (r < 0) { tipSel = -(r + 1); break; }
                    else tipSel = r;
                }

                string tipClient;
                if (tipSel == 0) tipClient = "Normal";
                else if (tipSel == 1) tipClient = "Student";
                else if (tipSel == 2) tipClient = "Pensionar";
                else tipClient = "Membru fidel";

                clienti.push_back(new Client(stoi(idStr), nume, prenume, email, telefon, tipClient));
                mesajSucces("Client adaugat cu succes!");
            }

            if (ales == 1) {
                clear(); drawBorder();
                int rows, cols; getmaxyx(stdscr, rows, cols);
                attron(COLOR_PAIR(COL_TITLU) | A_BOLD);
                mvprintw(2, (cols - 20) / 2, "LISTA CLIENTI");
                attroff(COLOR_PAIR(COL_TITLU) | A_BOLD);

                if (clienti.empty()) {
                    mesajEroare("Nu exista clienti!");
                }
                else {
                    int y = 5;
                    for (int i = 0; i < clienti.size(); i++) {
                        attron(COLOR_PAIR(COL_ACCENT) | A_BOLD);
                        mvprintw(y++, 10, "[%d] %s %s", i,
                            clienti[i]->getNume().c_str(),
                            clienti[i]->getPrenume().c_str());
                        attroff(COLOR_PAIR(COL_ACCENT) | A_BOLD);
                        attron(COLOR_PAIR(COL_NORMAL));
                        mvprintw(y++, 12, "Email: %s | Tel: %s | Tip: %s",
                            clienti[i]->getEmail().c_str(),
                            clienti[i]->getTelefon().c_str(),
                            clienti[i]->getTipClient().c_str());
                        attroff(COLOR_PAIR(COL_NORMAL));
                        y++;
                    }
                    attron(COLOR_PAIR(COL_ACCENT));
                    mvprintw(rows - 2, (cols - 30) / 2, "Apasa orice tasta pentru a continua");
                    attroff(COLOR_PAIR(COL_ACCENT));
                    refresh(); getch();
                }
            }
        }
        else sel = result;
    }
}

// ==================== SPECTACOLE ====================
void gestionareSpectacole() {
    vector<string> optiuni = { "Adauga spectacol", "Afiseaza spectacole", "Inapoi" };
    int sel = 0;

    while (true) {
        int result = drawMeniu(optiuni, "GESTIONARE SPECTACOLE", sel);
        if (result == -99) return;
        if (result < 0) {
            int ales = -(result + 1);
            if (ales == 2) return;

            if (ales == 0) {
                if (filme.empty() || sali.empty()) {
                    mesajEroare("Trebuie sa existe filme si sali!");
                    continue;
                }

                // Alege film
                vector<string> numFilme;
                for (auto f : filme) numFilme.push_back(f->getTitlu());
                int filmSel = 0;
                while (true) {
                    int r = drawMeniu(numFilme, "ALEGE FILM", filmSel);
                    if (r < 0) { filmSel = -(r + 1); break; }
                    else filmSel = r;
                }

                // Alege sala
                vector<string> numSali;
                for (auto s : sali) numSali.push_back("Sala " + to_string(s->getNumarSala()) + " - " + s->getTip());
                int salaSel = 0;
                while (true) {
                    int r = drawMeniu(numSali, "ALEGE SALA", salaSel);
                    if (r < 0) { salaSel = -(r + 1); break; }
                    else salaSel = r;
                }

                clear(); drawBorder();
                int rows, cols; getmaxyx(stdscr, rows, cols);
                attron(COLOR_PAIR(COL_TITLU) | A_BOLD);
                mvprintw(2, (cols - 20) / 2, "DETALII SPECTACOL");
                attroff(COLOR_PAIR(COL_TITLU) | A_BOLD);

                string idStr = inputField("ID       :", 6, 10);
                string data = inputField("Data     :", 8, 10);
                string ora = inputField("Ora      :", 10, 10);
                string pretStr = inputField("Pret     :", 12, 10);

                spectacole.push_back(new Spectacol(stoi(idStr), filme[filmSel], sali[salaSel], data, ora, stof(pretStr)));
                mesajSucces("Spectacol adaugat cu succes!");
            }

            if (ales == 1) {
                clear(); drawBorder();
                int rows, cols; getmaxyx(stdscr, rows, cols);
                attron(COLOR_PAIR(COL_TITLU) | A_BOLD);
                mvprintw(2, (cols - 20) / 2, "LISTA SPECTACOLE");
                attroff(COLOR_PAIR(COL_TITLU) | A_BOLD);

                if (spectacole.empty()) {
                    mesajEroare("Nu exista spectacole!");
                }
                else {
                    int y = 5;
                    for (int i = 0; i < spectacole.size(); i++) {
                        attron(COLOR_PAIR(COL_ACCENT) | A_BOLD);
                        mvprintw(y++, 10, "[%d] %s", i, spectacole[i]->getFilm()->getTitlu().c_str());
                        attroff(COLOR_PAIR(COL_ACCENT) | A_BOLD);
                        attron(COLOR_PAIR(COL_NORMAL));
                        mvprintw(y++, 12, "Sala: %d | Data: %s | Ora: %s | Pret: %.2f RON",
                            spectacole[i]->getSala()->getNumarSala(),
                            spectacole[i]->getData().c_str(),
                            spectacole[i]->getOra().c_str(),
                            spectacole[i]->getPret());
                        attroff(COLOR_PAIR(COL_NORMAL));
                        y++;
                    }
                    attron(COLOR_PAIR(COL_ACCENT));
                    mvprintw(rows - 2, (cols - 30) / 2, "Apasa orice tasta pentru a continua");
                    attroff(COLOR_PAIR(COL_ACCENT));
                    refresh(); getch();
                }
            }
        }
        else sel = result;
    }
}

// ==================== REZERVARI ====================
void gestionareRezervari() {
    vector<string> optiuni = { "Adauga rezervare", "Afiseaza rezervari", "Anuleaza rezervare", "Inapoi" };
    int sel = 0;

    while (true) {
        int result = drawMeniu(optiuni, "GESTIONARE REZERVARI", sel);
        if (result == -99) return;
        if (result < 0) {
            int ales = -(result + 1);
            if (ales == 3) return;

            if (ales == 0) {
                if (clienti.empty() || spectacole.empty()) {
                    mesajEroare("Trebuie sa existe clienti si spectacole!");
                    continue;
                }

                // Alege client
                vector<string> numClienti;
                for (auto c : clienti)
                    numClienti.push_back(c->getNume() + " " + c->getPrenume() + " [" + c->getTipClient() + "]");
                int clientSel = 0;
                while (true) {
                    int r = drawMeniu(numClienti, "ALEGE CLIENT", clientSel);
                    if (r < 0) { clientSel = -(r + 1); break; }
                    else clientSel = r;
                }

                // Alege spectacol
                vector<string> numSpectacole;
                for (auto s : spectacole)
                    numSpectacole.push_back(s->getFilm()->getTitlu() + " | " + s->getData() + " " + s->getOra());
                int spectacolSel = 0;
                while (true) {
                    int r = drawMeniu(numSpectacole, "ALEGE SPECTACOL", spectacolSel);
                    if (r < 0) { spectacolSel = -(r + 1); break; }
                    else spectacolSel = r;
                }

                clear(); drawBorder();
                int rows, cols; getmaxyx(stdscr, rows, cols);
                attron(COLOR_PAIR(COL_TITLU) | A_BOLD);
                mvprintw(2, (cols - 20) / 2, "DETALII REZERVARE");
                attroff(COLOR_PAIR(COL_TITLU) | A_BOLD);

                string idStr = inputField("ID rezervare :", 6, 10);
                string locStr = inputField("Nr. locuri   :", 8, 10);
                string data = inputField("Data rezervare:", 10, 10);

                // Verifica daca sunt locuri libere
                int locuriLibere = spectacole[spectacolSel]->getLocuriLibere();
                if (locuriLibere < stoi(locStr)) {
                    mesajEroare("Nu sunt suficiente locuri libere!");
                    continue;
                }

                // Selectie locuri din matrice
                vector<int> locuriAlese = selectieLocuri(spectacole[spectacolSel], stoi(locStr));

                if (locuriAlese.empty()) {
                    mesajEroare("Rezervare anulata!");
                    continue;
                }

                // Ocupa locurile selectate
                for (int loc : locuriAlese)
                    spectacole[spectacolSel]->ocupaLoc(loc);

                Rezervare* r = new Rezervare(stoi(idStr),
                    clienti[clientSel],
                    spectacole[spectacolSel],
                    stoi(locStr), data);
                r->confirma();
                rezervari.push_back(r);

                // Afiseaza total cu reducere
                float total = r->calculeazaTotal();
                string tip = clienti[clientSel]->getTipClient();
                clear(); drawBorder();
                attron(COLOR_PAIR(COL_TITLU) | A_BOLD);
                mvprintw(2, (cols - 20) / 2, "REZERVARE CONFIRMATA");
                attroff(COLOR_PAIR(COL_TITLU) | A_BOLD);

                attron(COLOR_PAIR(COL_NORMAL));
                mvprintw(6, 10, "Client  : %s %s",
                    clienti[clientSel]->getNume().c_str(),
                    clienti[clientSel]->getPrenume().c_str());
                mvprintw(8, 10, "Film    : %s", spectacole[spectacolSel]->getFilm()->getTitlu().c_str());
                mvprintw(10, 10, "Locuri  : %s", locStr.c_str());
                attroff(COLOR_PAIR(COL_NORMAL));

                if (tip != "Normal") {
                    attron(COLOR_PAIR(COL_EROARE));
                    float red = (tip == "Student") ? 20 : (tip == "Pensionar") ? 30 : 10;
                    mvprintw(12, 10, "Reducere: %.0f%%", red);
                    attroff(COLOR_PAIR(COL_EROARE));
                }

                attron(COLOR_PAIR(COL_SUCCES) | A_BOLD);
                mvprintw(14, 10, "TOTAL   : %.2f RON", total);
                attroff(COLOR_PAIR(COL_SUCCES) | A_BOLD);

                attron(COLOR_PAIR(COL_ACCENT));
                mvprintw(rows - 2, (cols - 30) / 2, "Apasa orice tasta pentru a continua");
                attroff(COLOR_PAIR(COL_ACCENT));
                refresh(); getch();
            }

            if (ales == 1) {
                clear(); drawBorder();
                int rows, cols; getmaxyx(stdscr, rows, cols);
                attron(COLOR_PAIR(COL_TITLU) | A_BOLD);
                mvprintw(2, (cols - 20) / 2, "LISTA REZERVARI");
                attroff(COLOR_PAIR(COL_TITLU) | A_BOLD);

                if (rezervari.empty()) {
                    mesajEroare("Nu exista rezervari!");
                }
                else {
                    int y = 5;
                    for (int i = 0; i < rezervari.size(); i++) {
                        attron(COLOR_PAIR(COL_ACCENT) | A_BOLD);
                        mvprintw(y++, 10, "[%d] %s %s → %s", i,
                            rezervari[i]->getClient()->getNume().c_str(),
                            rezervari[i]->getClient()->getPrenume().c_str(),
                            rezervari[i]->getSpectacol()->getFilm()->getTitlu().c_str());
                        attroff(COLOR_PAIR(COL_ACCENT) | A_BOLD);
                        attron(COLOR_PAIR(COL_NORMAL));
                        mvprintw(y++, 12, "Locuri: %d | Total: %.2f RON | Status: %s",
                            rezervari[i]->getNrLocuri(),
                            rezervari[i]->calculeazaTotal(),
                            rezervari[i]->getStatus().c_str());
                        attroff(COLOR_PAIR(COL_NORMAL));
                        y++;
                    }
                    attron(COLOR_PAIR(COL_ACCENT));
                    mvprintw(rows - 2, (cols - 30) / 2, "Apasa orice tasta pentru a continua");
                    attroff(COLOR_PAIR(COL_ACCENT));
                    refresh(); getch();
                }
            }
            if (ales == 2) {
                if (rezervari.empty()) {
                    mesajEroare("Nu exista rezervari!");
                    continue;
                }

                // Afiseaza rezervarile active
                vector<string> listaRez;
                vector<int> indexActivi;
                for (int i = 0; i < rezervari.size(); i++) {
                    if (rezervari[i]->getStatus() == "Confirmata") {
                        string item = rezervari[i]->getClient()->getNume() + " " +
                            rezervari[i]->getClient()->getPrenume() + " -> " +
                            rezervari[i]->getSpectacol()->getFilm()->getTitlu();
                        listaRez.push_back(item);
                        indexActivi.push_back(i);
                    }
                }

                if (listaRez.empty()) {
                    mesajEroare("Nu exista rezervari active!");
                    continue;
                }

                // Selectie cu sageti
                int rezSel = 0;
                while (true) {
                    int r = drawMeniu(listaRez, "ALEGE REZERVARE DE ANULAT", rezSel);
                    if (r == -99) break;
                    if (r < 0) { rezSel = -(r + 1); break; }
                    else rezSel = r;
                }

                // Confirmare anulare
                int idxReal = indexActivi[rezSel];
                clear(); drawBorder();
                int rows, cols; getmaxyx(stdscr, rows, cols);

                attron(COLOR_PAIR(COL_TITLU) | A_BOLD);
                mvprintw(2, (cols - 20) / 2, "ANULARE REZERVARE");
                attroff(COLOR_PAIR(COL_TITLU) | A_BOLD);

                attron(COLOR_PAIR(COL_NORMAL));
                mvprintw(5, 10, "Client  : %s %s",
                    rezervari[idxReal]->getClient()->getNume().c_str(),
                    rezervari[idxReal]->getClient()->getPrenume().c_str());
                mvprintw(7, 10, "Film    : %s",
                    rezervari[idxReal]->getSpectacol()->getFilm()->getTitlu().c_str());
                mvprintw(9, 10, "Locuri  : %d", rezervari[idxReal]->getNrLocuri());
                mvprintw(11, 10, "Total   : %.2f RON", rezervari[idxReal]->calculeazaTotal());
                attroff(COLOR_PAIR(COL_NORMAL));

                attron(COLOR_PAIR(COL_EROARE) | A_BOLD);
                mvprintw(14, 10, "Esti sigur ca vrei sa anulezi? (Y/N)");
                attroff(COLOR_PAIR(COL_EROARE) | A_BOLD);
                refresh();

                int ch = getch();
                if (ch == 'y' || ch == 'Y') {
                    rezervari[idxReal]->anuleaza();
                    mesajSucces("Rezervarea a fost anulata!");
                }
                else {
                    mesajEroare("Anulare abandonata!");
                }
            }
        }
        else sel = result;
    }
}

// ==================== RAPOARTE ====================
void gestionareRapoarte() {
    Raport raport(rezervari, spectacole);
    vector<string> optiuni = {
        "Filmul cel mai popular",
        "Incasari totale",
        "Incasari pe zi",
        "Sala cea mai ocupata",
        "Clientul fidel",
        "Inapoi"
    };
    int sel = 0;

    while (true) {
        int result = drawMeniu(optiuni, "RAPOARTE SI STATISTICI", sel);
        if (result == -99) return;
        if (result < 0) {
            int ales = -(result + 1);
            if (ales == 5) return;

            clear(); drawBorder();
            int rows, cols;
            getmaxyx(stdscr, rows, cols);

            attron(COLOR_PAIR(COL_TITLU) | A_BOLD);
            mvprintw(2, (cols - 24) / 2, "RAPOARTE SI STATISTICI");
            attroff(COLOR_PAIR(COL_TITLU) | A_BOLD);

            int y = 5;

            if (ales == 0) {
                // Filmul cel mai popular
                map<string, int> contor;
                for (auto r : rezervari)
                    if (r->getStatus() == "Confirmata")
                        contor[r->getSpectacol()->getFilm()->getTitlu()] += r->getNrLocuri();

                attron(COLOR_PAIR(COL_ACCENT) | A_BOLD);
                mvprintw(y++, 10, "=== Filmul cel mai popular ===");
                attroff(COLOR_PAIR(COL_ACCENT) | A_BOLD);

                if (contor.empty()) {
                    attron(COLOR_PAIR(COL_EROARE));
                    mvprintw(y++, 10, "Nu exista rezervari confirmate!");
                    attroff(COLOR_PAIR(COL_EROARE));
                }
                else {
                    string celMaiPopular;
                    int maxLocuri = 0;
                    for (auto& p : contor)
                        if (p.second > maxLocuri) {
                            maxLocuri = p.second;
                            celMaiPopular = p.first;
                        }
                    attron(COLOR_PAIR(COL_NORMAL));
                    mvprintw(y++, 10, "Film: %s", celMaiPopular.c_str());
                    mvprintw(y++, 10, "Total locuri rezervate: %d", maxLocuri);
                    attroff(COLOR_PAIR(COL_NORMAL));
                }
            }

            else if (ales == 1) {
                // Incasari totale
                float total = 0;
                for (auto r : rezervari)
                    if (r->getStatus() == "Confirmata")
                        total += r->calculeazaTotal();

                attron(COLOR_PAIR(COL_ACCENT) | A_BOLD);
                mvprintw(y++, 10, "=== Incasari totale ===");
                attroff(COLOR_PAIR(COL_ACCENT) | A_BOLD);
                attron(COLOR_PAIR(COL_SUCCES) | A_BOLD);
                mvprintw(y++, 10, "Total: %.2f RON", total);
                attroff(COLOR_PAIR(COL_SUCCES) | A_BOLD);
            }

            else if (ales == 2) {
                // Incasari pe zi
                attron(COLOR_PAIR(COL_ACCENT) | A_BOLD);
                mvprintw(y++, 10, "=== Incasari pe zi ===");
                attroff(COLOR_PAIR(COL_ACCENT) | A_BOLD);

                string data = inputField("Data (YYYY-MM-DD):", y + 1, 10);

                float total = 0;
                for (auto r : rezervari)
                    if (r->getStatus() == "Confirmata" && r->getDataRezervare() == data)
                        total += r->calculeazaTotal();

                attron(COLOR_PAIR(COL_SUCCES) | A_BOLD);
                mvprintw(y + 3, 10, "Total pe %s: %.2f RON", data.c_str(), total);
                attroff(COLOR_PAIR(COL_SUCCES) | A_BOLD);
            }

            else if (ales == 3) {
                // Sala cea mai ocupata
                map<int, int> contor;
                for (auto r : rezervari)
                    if (r->getStatus() == "Confirmata")
                        contor[r->getSpectacol()->getSala()->getNumarSala()] += r->getNrLocuri();

                attron(COLOR_PAIR(COL_ACCENT) | A_BOLD);
                mvprintw(y++, 10, "=== Sala cea mai ocupata ===");
                attroff(COLOR_PAIR(COL_ACCENT) | A_BOLD);

                if (contor.empty()) {
                    attron(COLOR_PAIR(COL_EROARE));
                    mvprintw(y++, 10, "Nu exista rezervari confirmate!");
                    attroff(COLOR_PAIR(COL_EROARE));
                }
                else {
                    int salaCeaMaiOcupata = 0, maxLocuri = 0;
                    for (auto& p : contor)
                        if (p.second > maxLocuri) {
                            maxLocuri = p.second;
                            salaCeaMaiOcupata = p.first;
                        }
                    attron(COLOR_PAIR(COL_NORMAL));
                    mvprintw(y++, 10, "Sala: %d", salaCeaMaiOcupata);
                    mvprintw(y++, 10, "Total locuri ocupate: %d", maxLocuri);
                    attroff(COLOR_PAIR(COL_NORMAL));
                }
            }

            else if (ales == 4) {
                // Clientul fidel
                map<string, int> contor;
                for (auto r : rezervari)
                    if (r->getStatus() == "Confirmata") {
                        string nume = r->getClient()->getNume() + " " + r->getClient()->getPrenume();
                        contor[nume]++;
                    }

                attron(COLOR_PAIR(COL_ACCENT) | A_BOLD);
                mvprintw(y++, 10, "=== Clientul fidel ===");
                attroff(COLOR_PAIR(COL_ACCENT) | A_BOLD);

                if (contor.empty()) {
                    attron(COLOR_PAIR(COL_EROARE));
                    mvprintw(y++, 10, "Nu exista rezervari confirmate!");
                    attroff(COLOR_PAIR(COL_EROARE));
                }
                else {
                    string celMaiFidel;
                    int maxRezervari = 0;
                    for (auto& p : contor)
                        if (p.second > maxRezervari) {
                            maxRezervari = p.second;
                            celMaiFidel = p.first;
                        }
                    attron(COLOR_PAIR(COL_NORMAL));
                    mvprintw(y++, 10, "Client: %s", celMaiFidel.c_str());
                    mvprintw(y++, 10, "Total rezervari: %d", maxRezervari);
                    attroff(COLOR_PAIR(COL_NORMAL));
                }
            }

            attron(COLOR_PAIR(COL_ACCENT));
            mvprintw(rows - 2, (cols - 30) / 2, "Apasa orice tasta pentru a continua");
            attroff(COLOR_PAIR(COL_ACCENT));
            refresh();
            getch();

        }
        else sel = result;
    }
}

// ==================== MAIN ====================
int main() {
    setlocale(LC_ALL, "");
    initUI();

    // Date de test
   // Incarca date salvate
    Storage::incarca(filme, sali, clienti, spectacole, rezervari);

    // Date de test doar daca nu exista date salvate
    if (filme.empty()) {
        filme.push_back(new Film("Inception", "Actiune", 148, 9.3));
        filme.push_back(new Film("Titanic", "Drama", 195, 8.7));
        sali.push_back(new Sala(1, 100, "3D"));
        sali.push_back(new Sala(2, 50, "IMAX"));
        clienti.push_back(new Client(1, "Popescu", "Ion", "ion@email.com", "0712345678", "Normal"));
        clienti.push_back(new Client(2, "Ionescu", "Maria", "maria@email.com", "0723456789", "Student"));
        clienti.push_back(new Client(3, "Georgescu", "Dan", "dan@email.com", "0734567890", "Pensionar"));
        spectacole.push_back(new Spectacol(1, filme[0], sali[0], "2024-03-14", "19:00", 50));
        spectacole.push_back(new Spectacol(2, filme[1], sali[1], "2024-03-15", "20:00", 40));
    }

    vector<string> meniuPrincipal = {
        "Gestionare filme",
        "Gestionare sali",
        "Gestionare clienti",
        "Gestionare spectacole",
        "Gestionare rezervari",
        "Rapoarte",
        "Iesire"
    };

    int sel = 0;
    while (true) {
        int result = drawMeniu(meniuPrincipal, "MENIU PRINCIPAL", sel);
        if (result == -99) break;
        if (result < 0) {
            int ales = -(result + 1);
            if (ales == 0) gestionareFilme();
            else if (ales == 1) gestionareSali();
            else if (ales == 2) gestionareClienti();
            else if (ales == 3) gestionareSpectacole();
            else if (ales == 4) gestionareRezervari();
            else if (ales == 5) gestionareRapoarte();
            else if (ales == 6) break;
        }
        else sel = result;
    }
    Storage::salveaza(filme, sali, clienti, spectacole, rezervari);
    endwin();
    return 0;
}
