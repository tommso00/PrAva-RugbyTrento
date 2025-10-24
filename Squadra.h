#ifndef SQUADRA_H
#define SQUADRA_H

#include <string>
#include <vector>
#include <iostream>
#include "Giocatore.h"
#include "Staff.h"
using namespace std;

class Squadra {
private:
    string nome, indirizzo;
    int id, punteggioClassifica;
    vector<Giocatore> giocatori;

public:
    Squadra(const string& nome, const string& indirizzo, int id);
    ~Squadra();

    string getNome() const;
    string getIndirizzo() const;
    int getId() const;
    int getPunteggio() const;

    void setNome(const string& n);
    void setIndirizzo(const string& i);
    void setId(int i);
    void setPunteggio(int p);

    void addGiocatore(const Giocatore& g);
    void removeGiocatore(int id);

    friend ostream& operator<<(ostream& os, const Squadra& s);
};

#endif


