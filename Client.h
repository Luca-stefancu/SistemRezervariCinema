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
    string tipClient; // "Student", "Pensionar", "Membru fidel", "Normal"

public:
    // Constructor
    Client(int id, string nume, string prenume, string email, string telefon, string tipClient);

    // Getteri
    int getId() const;
    string getNume() const;
    string getPrenume() const;
    string getEmail() const;
    string getTelefon() const;
    string getTipClient() const;

    // Setteri
    void setNume(string nume);
    void setPrenume(string prenume);
    void setEmail(string email);
    void setTelefon(string telefon);
    void setTipClient(string tipClient);

    // Afisare
    void afisare() const;
};
