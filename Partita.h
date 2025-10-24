#ifndef PARTITA_H
#define PARTITA_H

#include "Squadra.h"
#include <iostream>
using namespace std;

class Partita {
private:
    int id, data;
    Squadra locali;
    Squadra ospiti;
    int ptLocali, ptOspiti;

public:
    Partita(int id, int data, const Squadra& locali, const Squadra& ospiti);
    ~Partita();

    int getPunteggioPartita() const; 
    void setRisultato(int ptLocali, int ptOspiti);

    friend ostream& operator<<(ostream& os, const Partita& p);
};

#endif


