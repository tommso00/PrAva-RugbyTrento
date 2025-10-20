#ifndef STATISTICHE_H
#define STATISTICHE_H

#include <iostream>
#include <vector>
#include <memory>
#include "Partita.h"
using namespace std;

class Statistiche {
private:
    vector<Partita> partite;

public:
    Statistiche();
    Statistiche(const vector<Partita> &p);
    ~Statistiche();

    double mediaPunteggi() const;
    shared_ptr<Giocatore> migliorGiocatore() const;
    int totalePartite() const;
    void stampaStatistiche() const;
};

#endif // STATISTICHE_H

