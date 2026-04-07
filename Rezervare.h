#pragma once
#include <string>
#include "Client.h"
#include "Spectacol.h"
using namespace std;

class Rezervare {
private:
    int id;
    Client* client;
    Spectacol* spectacol;
    int nrLocuri;
    string status; // "Confirmata", "Anulata", "In asteptare"
    string dataRezervare;

public:
    // Constructor
    Rezervare(int id, Client* client, Spectacol* spectacol, int nrLocuri, string dataRezervare);

    // Getteri
    int getId() const;
    Client* getClient() const;
    Spectacol* getSpectacol() const;
    int getNrLocuri() const;
    string getStatus() const;
    string getDataRezervare() const;

    // Setteri
    void setStatus(string status);
    void setNrLocuri(int nrLocuri);

    // Metode
    float calculeazaTotal() const;
    void confirma();
    void anuleaza();

    // Afisare
    void afisare() const;
};