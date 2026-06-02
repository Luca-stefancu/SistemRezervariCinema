#pragma once
#include <fstream>
#include <vector>
#include <string>
#include "Film.h"
#include "Sala.h"
#include "Client.h"
#include "Spectacol.h"
#include "Rezervare.h"
#include <sstream>
using namespace std;

class Storage {
public:

    static void salveaza(
        vector<Film*>& filme,
        vector<Sala*>& sali,
        vector<Client*>& clienti,
        vector<Spectacol*>& spectacole,
        vector<Rezervare*>& rezervari)
    {
        ofstream f("../../../date.txt");

        f << "[FILME]\n";
        f << filme.size() << "\n";
        for (auto x : filme)
            f << "titlu=" << x->getTitlu() << "\n"
            << "gen=" << x->getGen() << "\n"
            << "durata=" << x->getDurata() << "\n"
            << "rating=" << x->getRating() << "\n"
            << "---\n";

        f << "[SALI]\n";
        f << sali.size() << "\n";
        for (auto x : sali)
            f << "numar=" << x->getNumarSala() << "\n"
            << "capacitate=" << x->getCapacitate() << "\n"
            << "tip=" << x->getTip() << "\n"
            << "---\n";

        f << "[CLIENTI]\n";
        f << clienti.size() << "\n";
        for (auto x : clienti)
            f << "id=" << x->getId() << "\n"
            << "nume=" << x->getNume() << "\n"
            << "prenume=" << x->getPrenume() << "\n"
            << "email=" << x->getEmail() << "\n"
            << "telefon=" << x->getTelefon() << "\n"
            << "tip=" << x->getTipClient() << "\n"
            << "---\n";

        f << "[SPECTACOLE]\n";
        f << spectacole.size() << "\n";
        for (auto x : spectacole) {
            int filmIdx = 0, salaIdx = 0;
            for (int i = 0; i < filme.size(); i++)
                if (filme[i] == x->getFilm()) filmIdx = i;
            for (int i = 0; i < sali.size(); i++)
                if (sali[i] == x->getSala()) salaIdx = i;

            f << "id=" << x->getId() << "\n";
            f << "film=" << filmIdx << "\n";
            f << "sala=" << salaIdx << "\n";
            f << "data=" << x->getData() << "\n";
            f << "ora=" << x->getOra() << "\n";
            f << "pret=" << x->getPret() << "\n";
            f << "locuri_ocupate=";
            for (int i = 0; i < x->getLocuriOcupate().size(); i++)
                f << x->getLocuriOcupate()[i] << (i < x->getLocuriOcupate().size() - 1 ? "," : "");
            f << "\n";
            f << "---\n";
        }

        f << "[REZERVARI]\n";
        f << rezervari.size() << "\n";
        for (auto x : rezervari) {
            int clientIdx = 0, spectacolIdx = 0;
            for (int i = 0; i < clienti.size(); i++)
                if (clienti[i] == x->getClient()) clientIdx = i;
            for (int i = 0; i < spectacole.size(); i++)
                if (spectacole[i] == x->getSpectacol()) spectacolIdx = i;

            f << "id=" << x->getId() << "\n"
                << "client=" << clientIdx << "\n"
                << "spectacol=" << spectacolIdx << "\n"
                << "locuri=" << x->getNrLocuri() << "\n"
                << "status=" << x->getStatus() << "\n"
                << "data=" << x->getDataRezervare() << "\n"
                << "---\n";
        }

        f.close();
    }

    static string valoare(const string& linie) {
        return linie.substr(linie.find('=') + 1);
    }

    static void incarca(
        vector<Film*>& filme,
        vector<Sala*>& sali,
        vector<Client*>& clienti,
        vector<Spectacol*>& spectacole,
        vector<Rezervare*>& rezervari)
    {
        ifstream f("../../../date.txt");
        if (!f.is_open()) return;

        string linie;
        while (getline(f, linie)) {

            if (linie == "[FILME]") {
                int n; f >> n; f.ignore();
                for (int i = 0; i < n; i++) {
                    string titlu, gen, durStr, ratStr, sep;
                    getline(f, titlu); titlu = valoare(titlu);
                    getline(f, gen);   gen = valoare(gen);
                    getline(f, durStr); durStr = valoare(durStr);
                    getline(f, ratStr); ratStr = valoare(ratStr);
                    getline(f, sep);
                    filme.push_back(new Film(titlu, gen, stoi(durStr), stof(ratStr)));
                }
            }

            if (linie == "[SALI]") {
                int n; f >> n; f.ignore();
                for (int i = 0; i < n; i++) {
                    string nrStr, capStr, tip, sep;
                    getline(f, nrStr);  nrStr = valoare(nrStr);
                    getline(f, capStr); capStr = valoare(capStr);
                    getline(f, tip);    tip = valoare(tip);
                    getline(f, sep);
                    sali.push_back(new Sala(stoi(nrStr), stoi(capStr), tip));
                }
            }

            if (linie == "[CLIENTI]") {
                int n; f >> n; f.ignore();
                for (int i = 0; i < n; i++) {
                    string idStr, nume, prenume, email, telefon, tip, sep;
                    getline(f, idStr);   idStr = valoare(idStr);
                    getline(f, nume);    nume = valoare(nume);
                    getline(f, prenume); prenume = valoare(prenume);
                    getline(f, email);   email = valoare(email);
                    getline(f, telefon); telefon = valoare(telefon);
                    getline(f, tip);     tip = valoare(tip);
                    getline(f, sep);
                    clienti.push_back(new Client(stoi(idStr), nume, prenume, email, telefon, tip));
                }
            }

            if (linie == "[SPECTACOLE]") {
                int n; f >> n; f.ignore();
                for (int i = 0; i < n; i++) {
                    string idStr, filmStr, salaStr, data, ora, pretStr, sep;
                    getline(f, idStr);   idStr = valoare(idStr);
                    getline(f, filmStr); filmStr = valoare(filmStr);
                    getline(f, salaStr); salaStr = valoare(salaStr);
                    getline(f, data);    data = valoare(data);
                    getline(f, ora);     ora = valoare(ora);
                    getline(f, pretStr); 
                    string locuriStr;
                    getline(f, locuriStr); locuriStr = valoare(locuriStr);
                    pretStr = valoare(pretStr);
                    getline(f, sep);
                    spectacole.push_back(new Spectacol(
                        stoi(idStr),
                        filme[stoi(filmStr)],
                        sali[stoi(salaStr)],
                        data, ora, stof(pretStr)));
                    // Incarca locurile ocupate
                    if (!locuriStr.empty()) {
                        stringstream ss(locuriStr);
                        string token;
                        int idx = 0;
                        while (getline(ss, token, ',')) {
                            if (token == "1")
                                spectacole.back()->ocupaLoc(idx);
                            idx++;
                        }
                    }
                }
            }

            if (linie == "[REZERVARI]") {
                int n; f >> n; f.ignore();
                for (int i = 0; i < n; i++) {
                    string idStr, clientStr, spectacolStr, locStr, status, data, sep;
                    getline(f, idStr);       idStr = valoare(idStr);
                    getline(f, clientStr);   clientStr = valoare(clientStr);
                    getline(f, spectacolStr); spectacolStr = valoare(spectacolStr);
                    getline(f, locStr);      locStr = valoare(locStr);
                    getline(f, status);      status = valoare(status);
                    getline(f, data);        data = valoare(data);
                    getline(f, sep);
                    Rezervare* r = new Rezervare(
                        stoi(idStr),
                        clienti[stoi(clientStr)],
                        spectacole[stoi(spectacolStr)],
                        stoi(locStr), data);
                    r->setStatus(status);
                    rezervari.push_back(r);
                }
            }
        }
        f.close();
    }
};