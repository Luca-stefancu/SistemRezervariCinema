#pragma once
#include <string>
using namespace std;

class Client {
private:
    int id;
    string nume;
    string prenume;
    string email;
    string telefon;

public:
    // Constructor
    Client(int id, string nume, string prenume, string email, string telefon);

    // Getteri
    int getId() const;
    string getNume() const;
    string getPrenume() const;
    string getEmail() const;
    string getTelefon() const;

    // Setteri
    void setNume(string nume);
    void setPrenume(string prenume);
    void setEmail(string email);
    void setTelefon(string telefon);

    // Afisare
    void afisare() const;
};