#include "Giocatore.h"
#include <iostream>

// Costruttore
Giocatore::Giocatore(const std::string& nome, const std::string& cognome, int eta, const std::string& ruolo, int id)
    : Persona(nome, cognome, eta), ruolo(ruolo), id(id),
      placcaggi(0), metriCorsi(0), mete(0), calciPiazzati(0),
      falliCommessi(0), offload(0), minutiGiocati(0), partiteGiocate(0) {}
	
// ? COPY CONSTRUCTOR
Giocatore::Giocatore(const Giocatore& other)
    : Persona(other),  // Base class copy
      ruolo(other.ruolo), id(other.id),
      placcaggi(other.placcaggi), metriCorsi(other.metriCorsi),
      mete(other.mete), calciPiazzati(other.calciPiazzati),
      falliCommessi(other.falliCommessi), offload(other.offload),
      minutiGiocati(other.minutiGiocati), partiteGiocate(other.partiteGiocate) {
    //std::cout << "Copy Giocatore(" << ruolo << ")" << std::endl;
}

// ? MOVE CONSTRUCTOR
Giocatore::Giocatore(Giocatore&& other) noexcept
    : Persona(std::move(other)),  // Move base class
      ruolo(std::move(other.ruolo)), id(other.id),
      placcaggi(other.placcaggi), metriCorsi(other.metriCorsi),
      mete(other.mete), calciPiazzati(other.calciPiazzati),
      falliCommessi(other.falliCommessi), offload(other.offload),
      minutiGiocati(other.minutiGiocati), partiteGiocate(other.partiteGiocate) {
    other.id = 0;
    //std::cout << "Move Giocatore(" << ruolo << ")" << std::endl;
}

// ? COPY ASSIGNMENT
Giocatore& Giocatore::operator=(const Giocatore& other) {
    if(this != &other) {
        Persona::operator=(other);  // Base class assignment
        
        ruolo = other.ruolo;
        id = other.id;
        placcaggi = other.placcaggi;
        metriCorsi = other.metriCorsi;
        mete = other.mete;
        calciPiazzati = other.calciPiazzati;
        falliCommessi = other.falliCommessi;
        offload = other.offload;
        minutiGiocati = other.minutiGiocati;
        partiteGiocate = other.partiteGiocate;
    }
    //std::cout << "Copy assign Giocatore(" << ruolo << ")" << std::endl;
    return *this;
}

// ? MOVE ASSIGNMENT
Giocatore& Giocatore::operator=(Giocatore&& other) noexcept {
    if(this != &other) {
        Persona::operator=(std::move(other));  // Move base class
        
        ruolo = std::move(other.ruolo);
        id = other.id;
        placcaggi = other.placcaggi;
        // ... move tutti i primitivi
        
        other.id = 0;
    }
    //std::cout << "Move assign Giocatore(" << ruolo << ")" << std::endl;
    return *this;
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


