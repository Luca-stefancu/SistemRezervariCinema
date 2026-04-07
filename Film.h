#pragma once
#include <string>
using namespace std;

class Film {
private:
    string titlu;
    string gen;
    int durata; // in minute
    float rating;

public:
    // Constructor
    Film(string titlu, string gen, int durata, float rating);

    // Getteri
    string getTitlu() const;
    string getGen() const;
    int getDurata() const;
    float getRating() const;

    // Setteri
    void setTitlu(string titlu);
    void setGen(string gen);
    void setDurata(int durata);
    void setRating(float rating);

    // Afisare
    void afisare() const;
};