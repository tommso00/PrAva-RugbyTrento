#include "Partita.h"

// Costruttore: crea la partita con id, data e squadre locali e ospiti
Partita::Partita(int id_, int data_, const Squadra& locali_, const Squadra& ospiti_) 
    : id(id_), data(data_), locali(locali_), ospiti(ospiti_), ptLocali(0), ptOspiti(0) {}

// Restituisce il punteggio totale (ad esempio la somma dei punti segnati)
int Partita::getPunteggioPartita() const {
    return ptLocali + ptOspiti;
}

// Imposta il risultato della partita (punti locali e ospiti)
void Partita::setRisultato(int ptLocali_, int ptOspiti_) {
    ptLocali = ptLocali_;
    ptOspiti = ptOspiti_;
}

// Operatore di stampa per mostrare informazioni della partita
std::ostream& operator<<(std::ostream& os, const Partita& p) {
    os << "Partita ID: " << p.id << ", Data: " << p.data << "\n";
    os << "Locali: " << p.locali << " - Punti: " << p.ptLocali << "\n";
    os << "Ospiti: " << p.ospiti << " - Punti: " << p.ptOspiti;
    return os;
}


/*
Secondo me possiamo far ritornare una stringa a getPunteggioPartita() 
del tipo cout << ptLocali << "-" << ptOspiti << endl;
:)

*/

