#include "Sala.h"
#include <iostream>
using namespace std;

Sala::Sala(int numarSala, int capacitate, string tip) {
    this->numarSala = numarSala;
    this->capacitate = capacitate;
    this->tip = tip;
}

int Sala::getNumarSala() const { return numarSala; }
int Sala::getCapacitate() const { return capacitate; }
string Sala::getTip() const { return tip; }

void Sala::setNumarSala(int numarSala) { this->numarSala = numarSala; }
void Sala::setCapacitate(int capacitate) { this->capacitate = capacitate; }
void Sala::setTip(string tip) { this->tip = tip; }

void Sala::afisare() const {
    cout << "Sala: " << numarSala << endl;
    cout << "Capacitate: " << capacitate << " locuri" << endl;
    cout << "Tip: " << tip << endl;
}