#include "Spectacol.h"
#include <iostream>
using namespace std;

Spectacol::Spectacol(int id, Film* film, Sala* sala, string data, string ora, float pret) {
    this->id = id;
    this->film = film;
    this->sala = sala;
    this->data = data;
    this->ora = ora;
    this->pret = pret;
}

int Spectacol::getId() const { return id; }
Film* Spectacol::getFilm() const { return film; }
Sala* Spectacol::getSala() const { return sala; }
string Spectacol::getData() const { return data; }
string Spectacol::getOra() const { return ora; }
float Spectacol::getPret() const { return pret; }

void Spectacol::setData(string data) { this->data = data; }
void Spectacol::setOra(string ora) { this->ora = ora; }
void Spectacol::setPret(float pret) { this->pret = pret; }

void Spectacol::afisare() const {
    cout << "=== Spectacol ID: " << id << " ===" << endl;
    cout << "Film: " << film->getTitlu() << endl;
    cout << "Sala: " << sala->getNumarSala() << " (" << sala->getTip() << ")" << endl;
    cout << "Data: " << data << endl;
    cout << "Ora: " << ora << endl;
    cout << "Pret: " << pret << " RON" << endl;
}