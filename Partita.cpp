#include "Partita.h"
using namespace std;

Partita::Partita(int id, int data, const Squadra& locali, const Squadra& ospiti)
    : id(id), data(data), locali(locali), ospiti(ospiti), ptLocali(0), ptOspiti(0) {}

Partita::~Partita() {
    cout << "Distruttore Partita ID: " << id << " chiamato" << endl;
}

int Partita::getPunteggioPartita() const {
    return ptLocali + ptOspiti;
}

void Partita::setRisultato(int ptL, int ptO) {
    ptLocali = ptL;
    ptOspiti = ptO;
}

ostream& operator<<(ostream& os, const Partita& p) {
    os << "Partita ID: " << p.id << " | " << p.locali.getNome() << " "
       << p.ptLocali << " - " << p.ptOspiti << " " << p.ospiti.getNome();
    return os;
}

/*
Secondo me possiamo far ritornare una stringa a getPunteggioPartita() 
del tipo cout << ptLocali << "-" << ptOspiti << endl;
:)

*/

