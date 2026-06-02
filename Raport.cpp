#include "Raport.h"
#include <iostream>
#include <map>
using namespace std;

Raport::Raport(vector<Rezervare*>& rezervari, vector<Spectacol*>& spectacole)
    : rezervari(rezervari), spectacole(spectacole) {
}

void Raport::filmulCelMaiPopular() const {
    map<string, int> contor;
    for (auto r : rezervari)
        if (r->getStatus() == "Confirmata")
            contor[r->getSpectacol()->getFilm()->getTitlu()] += r->getNrLocuri();

    if (contor.empty()) {
        cout << "Nu exista rezervari confirmate!" << endl;
        return;
    }

    string celMaiPopular;
    int maxLocuri = 0;
    for (auto& p : contor)
        if (p.second > maxLocuri) {
            maxLocuri = p.second;
            celMaiPopular = p.first;
        }

    cout << "=== Filmul cel mai popular ===" << endl;
    cout << "Film: " << celMaiPopular << endl;
    cout << "Total locuri rezervate: " << maxLocuri << endl;
}

void Raport::incasariTotale() const {
    float total = 0;
    for (auto r : rezervari)
        if (r->getStatus() == "Confirmata")
            total += r->calculeazaTotal();

    cout << "=== Incasari totale ===" << endl;
    cout << "Total: " << total << " RON" << endl;
}

void Raport::incasariPeZi(string data) const {
    float total = 0;
    for (auto r : rezervari)
        if (r->getStatus() == "Confirmata" && r->getDataRezervare() == data)
            total += r->calculeazaTotal();

    cout << "=== Incasari pe ziua " << data << " ===" << endl;
    cout << "Total: " << total << " RON" << endl;
}

void Raport::salaCeaMaiOcupata() const {
    map<int, int> contor;
    for (auto r : rezervari)
        if (r->getStatus() == "Confirmata")
            contor[r->getSpectacol()->getSala()->getNumarSala()] += r->getNrLocuri();

    if (contor.empty()) {
        cout << "Nu exista rezervari confirmate!" << endl;
        return;
    }

    int salaCeaMaiOcupata = 0;
    int maxLocuri = 0;
    for (auto& p : contor)
        if (p.second > maxLocuri) {
            maxLocuri = p.second;
            salaCeaMaiOcupata = p.first;
        }

    cout << "=== Sala cea mai ocupata ===" << endl;
    cout << "Sala: " << salaCeaMaiOcupata << endl;
    cout << "Total locuri ocupate: " << maxLocuri << endl;
}

void Raport::clientulFidel() const {
    map<string, int> contor;
    for (auto r : rezervari)
        if (r->getStatus() == "Confirmata") {
            string numeClient = r->getClient()->getNume() + " " + r->getClient()->getPrenume();
            contor[numeClient]++;
        }

    if (contor.empty()) {
        cout << "Nu exista rezervari confirmate!" << endl;
        return;
    }

    string celMaiFidel;
    int maxRezervari = 0;
    for (auto& p : contor)
        if (p.second > maxRezervari) {
            maxRezervari = p.second;
            celMaiFidel = p.first;
        }

    cout << "=== Clientul fidel ===" << endl;
    cout << "Client: " << celMaiFidel << endl;
    cout << "Total rezervari: " << maxRezervari << endl;
}

void Raport::afisareMeniu() const {
    cout << "\n=== RAPOARTE SI STATISTICI ===" << endl;
    cout << "1. Filmul cel mai popular" << endl;
    cout << "2. Incasari totale" << endl;
    cout << "3. Incasari pe zi" << endl;
    cout << "4. Sala cea mai ocupata" << endl;
    cout << "5. Clientul fidel" << endl;
    cout << "0. Inapoi la meniul principal" << endl;
    cout << "Alegere: ";
}
