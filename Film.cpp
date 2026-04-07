#include "Film.h"
#include <iostream>
using namespace std;

Film::Film(string titlu, string gen, int durata, float rating) {
    this->titlu = titlu;
    this->gen = gen;
    this->durata = durata;
    this->rating = rating;
}

string Film::getTitlu() const { return titlu; }
string Film::getGen() const { return gen; }
int Film::getDurata() const { return durata; }
float Film::getRating() const { return rating; }

void Film::setTitlu(string titlu) { this->titlu = titlu; }
void Film::setGen(string gen) { this->gen = gen; }
void Film::setDurata(int durata) { this->durata = durata; }
void Film::setRating(float rating) { this->rating = rating; }

void Film::afisare() const {
    cout << "Film: " << titlu << endl;
    cout << "Gen: " << gen << endl;
    cout << "Durata: " << durata << " minute" << endl;
    cout << "Rating: " << rating << "/10" << endl;
}