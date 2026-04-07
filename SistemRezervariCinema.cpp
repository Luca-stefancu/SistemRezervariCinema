#include <iostream>
#include <vector>
#include "Film.h"
#include "Sala.h"
#include "Client.h"
#include "Spectacol.h"
#include "Rezervare.h"
#include "Raport.h"

using namespace std;

int main() {
    vector<Film*> filme;
    vector<Sala*> sali;
    vector<Client*> clienti;
    vector<Spectacol*> spectacole;
    vector<Rezervare*> rezervari;

    int opt;

    do {
        cout << "\n===== MENIU PRINCIPAL =====\n";
        cout << "1. Gestionare filme\n";
        cout << "2. Gestionare sali\n";
        cout << "3. Gestionare clienti\n";
        cout << "4. Gestionare spectacole\n";
        cout << "5. Gestionare rezervari\n";
        cout << "6. Rapoarte\n";
        cout << "0. Iesire\n";
        cout << "Alegere: ";
        cin >> opt;

        switch (opt) {

            // ===== FILME =====
        case 1: {
            int op;
            cout << "\n1. Adauga film\n2. Afiseaza filme\n";
            cin >> op;

            if (op == 1) {
                string titlu, gen;
                int durata;
                float rating;

                cout << "Titlu: "; cin >> titlu;
                cout << "Gen: "; cin >> gen;
                cout << "Durata: "; cin >> durata;
                cout << "Rating: "; cin >> rating;

                filme.push_back(new Film(titlu, gen, durata, rating));
            }
            else {
                for (auto f : filme)
                    f->afisare();
            }
            break;
        }

              // ===== SALI =====
        case 2: {
            int op;
            cout << "\n1. Adauga sala\n2. Afiseaza sali\n";
            cin >> op;

            if (op == 1) {
                int nr, cap;
                string tip;

                cout << "Numar: "; cin >> nr;
                cout << "Capacitate: "; cin >> cap;
                cout << "Tip: "; cin >> tip;

                sali.push_back(new Sala(nr, cap, tip));
            }
            else {
                for (auto s : sali)
                    s->afisare();
            }
            break;
        }

              // ===== CLIENTI =====
        case 3: {
            int op;
            cout << "\n1. Adauga client\n2. Afiseaza clienti\n";
            cin >> op;

            if (op == 1) {
                int id;
                string nume, prenume, email, telefon;

                cout << "ID: "; cin >> id;
                cout << "Nume: "; cin >> nume;
                cout << "Prenume: "; cin >> prenume;
                cout << "Email: "; cin >> email;
                cout << "Telefon: "; cin >> telefon;

                clienti.push_back(new Client(id, nume, prenume, email, telefon));
            }
            else {
                for (auto c : clienti)
                    c->afisare();
            }
            break;
        }

              // ===== SPECTACOLE =====
        case 4: {
            if (filme.empty() || sali.empty()) {
                cout << "Trebuie sa existe filme si sali!\n";
                break;
            }

            int id, filmIndex, salaIndex;
            string data, ora;
            float pret;

            cout << "ID: "; cin >> id;

            cout << "Alege film:\n";
            for (int i = 0; i < filme.size(); i++)
                cout << i << ". " << filme[i]->getTitlu() << endl;
            cin >> filmIndex;

            cout << "Alege sala:\n";
            for (int i = 0; i < sali.size(); i++)
                cout << i << ". Sala " << sali[i]->getNumarSala() << endl;
            cin >> salaIndex;

            cout << "Data: "; cin >> data;
            cout << "Ora: "; cin >> ora;
            cout << "Pret: "; cin >> pret;

            spectacole.push_back(
                new Spectacol(id, filme[filmIndex], sali[salaIndex], data, ora, pret)
            );

            break;
        }

              // ===== REZERVARI =====
        case 5: {
            if (clienti.empty() || spectacole.empty()) {
                cout << "Trebuie clienti si spectacole!\n";
                break;
            }

            int id, clientIndex, spectacolIndex, locuri;
            string data;

            cout << "ID: "; cin >> id;

            cout << "Alege client:\n";
            for (int i = 0; i < clienti.size(); i++)
                cout << i << ". " << clienti[i]->getNume() << endl;
            cin >> clientIndex;

            cout << "Alege spectacol:\n";
            for (int i = 0; i < spectacole.size(); i++)
                cout << i << ". " << spectacole[i]->getFilm()->getTitlu() << endl;
            cin >> spectacolIndex;

            cout << "Nr locuri: "; cin >> locuri;
            cout << "Data rezervare: "; cin >> data;

            Rezervare* r = new Rezervare(id,
                clienti[clientIndex],
                spectacole[spectacolIndex],
                locuri,
                data);

            r->confirma(); // automat confirmata
            rezervari.push_back(r);

            break;
        }

              // ===== RAPOARTE =====
        case 6: {
            Raport raport(rezervari, spectacole);

            int opRap;
            do {
                raport.afisareMeniu();
                cin >> opRap;

                switch (opRap) {
                case 1: raport.filmulCelMaiPopular(); break;
                case 2: raport.incasariTotale(); break;
                case 3: {
                    string data;
                    cout << "Data: ";
                    cin >> data;
                    raport.incasariPeZi(data);
                    break;
                }
                case 4: raport.salaCeaMaiOcupata(); break;
                case 5: raport.clientulFidel(); break;
                }
            } while (opRap != 0);

            break;
        }

        }

    } while (opt != 0);

    return 0;
}