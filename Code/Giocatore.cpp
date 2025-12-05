#include "Giocatore.h"

// Costruttore
Giocatore::Giocatore(const std::string& nome, 
					 const std::string& cognome,
					 int eta,
                     const std::string& ruolo_,
					 int id_)
    : Persona(nome, cognome, eta),
	  ruolo(ruolo_), 
	  id(id_) 
	  {
	placcaggi=0;
	metriCorsi =0;
	mete=0;
	calciPiazzati=0;

	falliCommessi=0;
	offload=0;

	minutiGiocati=0;
	partiteGiocate=0;;	

	}


// Getter e setter base
std::string Giocatore::getRuolo() const {
    return ruolo;
}

void Giocatore::setRuolo(const std::string& nuovoRuolo) {
    ruolo = nuovoRuolo;
}

int Giocatore::getId() const {
    return id;
}

void Giocatore::setId(int nuovoId) {
    id = nuovoId;
}

//Statistiche - Getter e Setter
int Giocatore::getPlaccaggi() const {
    return placcaggi;
}

void Giocatore::setPlaccaggi(int value) {
    placcaggi = value;
}

int Giocatore::getMetriCorsi() const {
    return metriCorsi;
}

void Giocatore::setMetriCorsi(int value) {
    metriCorsi = value;
}

int Giocatore::getMete() const {
    return mete;
}

void Giocatore::setMete(int value) {
    mete = value;
}

int Giocatore::getCalciPiazzati() const {
    return calciPiazzati;
}

void Giocatore::setCalciPiazzati(int value) {
    calciPiazzati = value;
}

int Giocatore::getFalliCommessi() const {
    return falliCommessi;
}

void Giocatore::setFalliCommessi(int value) {
    falliCommessi = value;
}

int Giocatore::getOffload() const {
    return offload;
}

void Giocatore::setOffload(int value) {
    offload = value;
}

int Giocatore::getMinutiGiocati() const {
    return minutiGiocati;
}

void Giocatore::setMinutiGiocati(int value) {
    minutiGiocati = value;
}

int Giocatore::getPartiteGiocate() const {
    return partiteGiocate;
}

void Giocatore::setPartiteGiocate(int value) {
    partiteGiocate = value;
}


// Operatore di stampa
std::ostream& operator<<(std::ostream& os, const Giocatore& g) {
    os << "Giocatore: " << g.getNome() << " " << g.getCognome()
       << ", Eta': " << g.getEta()
       << ", Ruolo: " << g.ruolo
       << ", ID: " << g.id;
    return os;
}


