#pragma once
#include <vector>
#include <string>
#include "Rezervare.h"
#include "Spectacol.h"
using namespace std;

class Raport {
private:
    vector<Rezervare*>& rezervari;
    vector<Spectacol*>& spectacole;

public:
    Raport(vector<Rezervare*>& rezervari, vector<Spectacol*>& spectacole);

    void filmulCelMaiPopular() const;
    void incasariTotale() const;
    void incasariPeZi(string data) const;
    void salaCeaMaiOcupata() const;
    void clientulFidel() const;
    void afisareMeniu() const;
};