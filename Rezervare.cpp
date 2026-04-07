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
    return nrLocuri * spectacol->getPret();
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
    cout << "=== Rezervare ID: " << id << " ===" << endl;
    cout << "Client: " << client->getNume() << " " << client->getPrenume() << endl;
    cout << "Film: " << spectacol->getFilm()->getTitlu() << endl;
    cout << "Data spectacol: " << spectacol->getData() << " ora " << spectacol->getOra() << endl;
    cout << "Nr. locuri: " << nrLocuri << endl;
    cout << "Total: " << calculeazaTotal() << " RON" << endl;
    cout << "Status: " << status << endl;
    cout << "Data rezervare: " << dataRezervare << endl;
}