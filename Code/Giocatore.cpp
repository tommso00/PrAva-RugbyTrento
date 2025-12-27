#include "Giocatore.h"
#include <iostream>

/**
 * @brief Costruttore principale Giocatore.
 */
Giocatore::Giocatore(const std::string& nome, const std::string& cognome, int eta, const std::string& ruolo, int id)
    : Persona(nome, cognome, eta), ruolo(ruolo), id(id),
      placcaggi(0), metriCorsi(0), mete(0), calciPiazzati(0),
      falliCommessi(0), offload(0), minutiGiocati(0), partiteGiocate(0) {}

/**
 * @brief Copy constructor Giocatore (deep copy).
 */
Giocatore::Giocatore(const Giocatore& other)
    : Persona(other),  // Base class copy
      ruolo(other.ruolo), id(other.id),
      placcaggi(other.placcaggi), metriCorsi(other.metriCorsi),
      mete(other.mete), calciPiazzati(other.calciPiazzati),
      falliCommessi(other.falliCommessi), offload(other.offload),
      minutiGiocati(other.minutiGiocati), partiteGiocate(other.partiteGiocate) {
    //std::cout << "Copy Giocatore(" << ruolo << ")" << std::endl;
}

/**
 * @brief Move constructor Giocatore (efficiente).
 */
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

/**
 * @brief Copy assignment operator Giocatore.
 */
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

/**
 * @brief Move assignment operator Giocatore.
 */
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

/**
 * @brief Restituisce il ruolo del giocatore.
 */
std::string Giocatore::getRuolo() const {
    return ruolo;
}

/**
 * @brief Imposta il ruolo del giocatore.
 */
void Giocatore::setRuolo(const std::string& nuovoRuolo) {
    ruolo = nuovoRuolo;
}

/**
 * @brief Restituisce l'ID del giocatore.
 */
int Giocatore::getId() const {
    return id;
}

/**
 * @brief Imposta l'ID del giocatore.
 */
void Giocatore::setId(int nuovoId) {
    id = nuovoId;
}

//Statistiche - Getter e Setter

/**
 * @brief Numero placcaggi effettuati.
 */
int Giocatore::getPlaccaggi() const {
    return placcaggi;
}

/**
 * @brief Imposta placcaggi del giocatore.
 */
void Giocatore::setPlaccaggi(int value) {
    placcaggi = value;
}

/**
 * @brief Metri percorsi con palla in mano.
 */
int Giocatore::getMetriCorsi() const {
    return metriCorsi;
}

/**
 * @brief Imposta metri corsi del giocatore.
 */
void Giocatore::setMetriCorsi(int value) {
    metriCorsi = value;
}

/**
 * @brief Numero di mete segnate.
 */
int Giocatore::getMete() const {
    return mete;
}

/**
 * @brief Imposta mete del giocatore.
 */
void Giocatore::setMete(int value) {
    mete = value;
}

/**
 * @brief Calci piazzati trasformati.
 */
int Giocatore::getCalciPiazzati() const {
    return calciPiazzati;
}

/**
 * @brief Imposta calci piazzati.
 */
void Giocatore::setCalciPiazzati(int value) {
    calciPiazzati = value;
}

/**
 * @brief Falli commessi dal giocatore.
 */
int Giocatore::getFalliCommessi() const {
    return falliCommessi;
}

/**
 * @brief Imposta falli commessi.
 */
void Giocatore::setFalliCommessi(int value) {
    falliCommessi = value;
}

/**
 * @brief Numero di offload eseguiti.
 */
int Giocatore::getOffload() const {
    return offload;
}

/**
 * @brief Imposta offload del giocatore.
 */
void Giocatore::setOffload(int value) {
    offload = value;
}

/**
 * @brief Minuti totali giocati.
 */
int Giocatore::getMinutiGiocati() const {
    return minutiGiocati;
}

/**
 * @brief Imposta minuti giocati.
 */
void Giocatore::setMinutiGiocati(int value) {
    minutiGiocati = value;
}

/**
 * @brief Numero partite disputate.
 */
int Giocatore::getPartiteGiocate() const {
    return partiteGiocate;
}

/**
 * @brief Imposta partite giocate.
 */
void Giocatore::setPartiteGiocate(int value) {
    partiteGiocate = value;
}

/**
 * @brief Overload operator<< per stampa Giocatore.
 */
std::ostream& operator<<(std::ostream& os, const Giocatore& g) {
    os << "Giocatore: " << g.getNome() << " " << g.getCognome()
       << ", Eta': " << g.getEta()
       << ", Ruolo: " << g.ruolo
       << ", ID: " << g.id;
    return os;
}

