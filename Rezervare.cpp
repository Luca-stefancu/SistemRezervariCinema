#include "Rezervare.h"
#include <iostream>
using namespace std;

Rezervare::Rezervare(int id, Client* client, Spectacol* spectacol, int nrLocuri, string dataRezervare) {
    this->id = id;
    this->client = client;
    this->spectacol = spectacol;
    this->nrLocuri = nrLocuri;
    this->status = "In asteptare";
    this->dataRezervare = dataRezervare;
}

int Rezervare::getId() const { return id; }
Client* Rezervare::getClient() const { return client; }
Spectacol* Rezervare::getSpectacol() const { return spectacol; }
int Rezervare::getNrLocuri() const { return nrLocuri; }
string Rezervare::getStatus() const { return status; }
string Rezervare::getDataRezervare() const { return dataRezervare; }

void Rezervare::setStatus(string status) { this->status = status; }
void Rezervare::setNrLocuri(int nrLocuri) { this->nrLocuri = nrLocuri; }

float Rezervare::calculeazaTotal() const {
    float total = nrLocuri * spectacol->getPret();
    string tip = client->getTipClient();
    float reducere = 0;

    if (tip == "Student") reducere = 0.20;
    else if (tip == "Pensionar") reducere = 0.30;
    else if (tip == "Membru fidel") reducere = 0.10;

    total = total - (total * reducere);
    return total;
}

void Rezervare::confirma() {
    status = "Confirmata";
    cout << "Rezervarea #" << id << " a fost confirmata!" << endl;
}

void Rezervare::anuleaza() {
    status = "Anulata";
    cout << "Rezervarea #" << id << " a fost anulata!" << endl;
}

void Rezervare::afisare() const {
    string tip = client->getTipClient();
    float totalFaraReducere = nrLocuri * spectacol->getPret();
    float totalCuReducere = calculeazaTotal();

    cout << "=== Rezervare ID: " << id << " ===" << endl;
    cout << "Client: " << client->getNume() << " " << client->getPrenume() << endl;
    cout << "Tip client: " << tip << endl;
    cout << "Film: " << spectacol->getFilm()->getTitlu() << endl;
    cout << "Data spectacol: " << spectacol->getData() << " ora " << spectacol->getOra() << endl;
    cout << "Nr. locuri: " << nrLocuri << endl;
    cout << "Pret fara reducere: " << totalFaraReducere << " RON" << endl;

    if (tip != "Normal") {
        float reducere = 0;
        if (tip == "Student") reducere = 20;
        else if (tip == "Pensionar") reducere = 30;
        else if (tip == "Membru fidel") reducere = 10;
        cout << "Reducere aplicata: " << reducere << "%" << endl;
    }

    cout << "Total de plata: " << totalCuReducere << " RON" << endl;
    cout << "Status: " << status << endl;
    cout << "Data rezervare: " << dataRezervare << endl;
}
