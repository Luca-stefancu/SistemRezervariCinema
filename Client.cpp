#include "Client.h"
#include <iostream>
using namespace std;

Client::Client(int id, string nume, string prenume, string email, string telefon, string tipClient) {
    this->id = id;
    this->nume = nume;
    this->prenume = prenume;
    this->email = email;
    this->telefon = telefon;
    this->tipClient = tipClient;
}
int Client::getId() const { return id; }
string Client::getNume() const { return nume; }
string Client::getPrenume() const { return prenume; }
string Client::getEmail() const { return email; }
string Client::getTelefon() const { return telefon; }
string Client::getTipClient() const { return tipClient; }

void Client::setNume(string nume) { this->nume = nume; }
void Client::setPrenume(string prenume) { this->prenume = prenume; }
void Client::setEmail(string email) { this->email = email; }
void Client::setTelefon(string telefon) { this->telefon = telefon; }
void Client::setTipClient(string tipClient) { this->tipClient = tipClient; }

void Client::afisare() const {
    cout << "=== Client ID: " << id << " ===" << endl;
    cout << "Nume: " << nume << " " << prenume << endl;
    cout << "Email: " << email << endl;
    cout << "Telefon: " << telefon << endl;
    cout << "Tip: " << tipClient << endl;
}
