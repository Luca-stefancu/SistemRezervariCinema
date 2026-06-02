#pragma once
#include <string>
#include "Film.h"
#include "Sala.h"
#include <vector>
using namespace std;

class Spectacol {
private:
    int id;
    Film* film;
    Sala* sala;
    string data;   // ex: "2024-01-15"
    string ora;    // ex: "18:30"
    float pret;
    vector<bool> locuriOcupate;

public:
    // Constructor
    Spectacol(int id, Film* film, Sala* sala, string data, string ora, float pret);

    // Getteri
    int getId() const;
    Film* getFilm() const;
    Sala* getSala() const;
    string getData() const;
    string getOra() const;
    float getPret() const;

    // Setteri
    void setData(string data);
    void setOra(string ora);
    void setPret(float pret);

    // Afisare
    void afisare() const;
    // Locuri
    void initializeazaLocuri();
    bool esteLocLiber(int index) const;
    void ocupaLoc(int index);
    void elibereazaLoc(int index);
    vector<bool>& getLocuriOcupate();
    int getLocuriLibere() const;
};
