#pragma once
#include <string>
using namespace std;

class Sala {
private:
    int numarSala;
    int capacitate;
    string tip; // ex: "2D", "3D", "IMAX"

public:
    // Constructor
    Sala(int numarSala, int capacitate, string tip);

    // Getteri
    int getNumarSala() const;
    int getCapacitate() const;
    string getTip() const;

    // Setteri
    void setNumarSala(int numarSala);
    void setCapacitate(int capacitate);
    void setTip(string tip);

    // Afisare
    void afisare() const;
};