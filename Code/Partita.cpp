#include "Partita.h"

// Costruttore
Partita::Partita(int id_, int data_, const Squadra& locali_, const Squadra& ospiti_) 
    : id(id_), data(data_), locali(locali_), ospiti(ospiti_), ptLocali(0), ptOspiti(0),cartellinoRossoLoc(0), cartellinoRossoOsp(0),
      cartellinoGialloLoc(0), cartellinoGialloOsp(0),
      possessoLoc(0.0), possessoOsp(0.0)  {}

int Partita::getPunteggioPartita() const {
    return ptLocali + ptOspiti;	//dovremmo farlo ritornare una stringa??? ptlocali << ":" << ptospiti?
}

void Partita::setRisultato(int ptLocali_, int ptOspiti_) {
    ptLocali = ptLocali_;
    ptOspiti = ptOspiti_;
}

int Partita::getPuntiOspiti() const {
    return ptOspiti;
}

int Partita::getPuntiLocali() const {
    return ptLocali;
}

int Partita::getCartellinoRossoLoc() const {
    return cartellinoRossoLoc;
}
void Partita::setCartellinoRossoLoc(int value) {
    cartellinoRossoLoc = value;
}

int Partita::getCartellinoRossoOsp() const {
    return cartellinoRossoOsp;
}

void Partita::setCartellinoRossoOsp(int value) {
    cartellinoRossoOsp = value;
}

int Partita::getCartellinoGialloLoc() const {
    return cartellinoGialloLoc;
}

void Partita::setCartellinoGialloLoc(int value) {
    cartellinoGialloLoc = value;
}

int Partita::getCartellinoGialloOsp() const {
    return cartellinoGialloOsp;
}

void Partita::setCartellinoGialloOsp(int value) {
    cartellinoGialloOsp = value;
}

double Partita::getPossessoLoc() const {
    return possessoLoc;
}

void Partita::setPossessoLoc(double value) {
    possessoLoc = value;
}

double Partita::getPossessoOsp() const {
    return possessoOsp;
}

void Partita::setPossessoOsp(double value) {
    possessoOsp = value;
}

void Partita::setPuntiLocali(int value) {
    ptLocali = value;
}

void Partita::setPuntiOspiti(int value) {
    ptOspiti = value;
}

const Squadra& Partita::getOspiti() const {
    return ospiti;
}

int Partita::getData() const {
    return data;
}

const Squadra& Partita::getLocali() const {
    return locali;
}

int Partita::getId() const {
    return id;
}


// Operatore di stampa per mostrare informazioni della partita
std::ostream& operator<<(std::ostream& os, const Partita& p) {
 	os << "Partita ID: " << p.id << ", Data: " << p.data << "\n";
	os << "Squadre: " << p.locali.getNome() << " vs " << p.ospiti.getNome() << "\n";
	os << "Punteggio partita: " << p.ptLocali << ":" << p.ptOspiti;

/* 	os << "Partita ID: " << p.id << ", Data: " << p.data << "\n";
	os << "Locali: " << p.locali << " - Punti: " << p.ptLocali << "\n";
    os << "Ospiti: " << p.ospiti << " - Punti: " << p.ptOspiti;
*/  return os;
}


/*
Secondo me possiamo far ritornare una stringa a getPunteggioPartita() 
del tipo cout << ptLocali << "-" << ptOspiti << endl;
:)

*/

