#include "Giocatore.h"

// Costruttore
Giocatore::Giocatore(const std::string& nome, const std::string& cognome, int eta,
                     const std::string& ruolo_, int id_)
    : Persona(nome, cognome, eta), ruolo(ruolo_), id(id_) {}

// Getter e setter
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

// Operatore di stampa
std::ostream& operator<<(std::ostream& os, const Giocatore& g) {
    os << "Giocatore: " << g.getNome() << " " << g.getCognome()
       << ", Età: " << g.getEta()
       << ", Ruolo: " << g.ruolo
       << ", ID: " << g.id;
    return os;
}


/*
Possibili aggiunte future:
- Metodo per aggiornare statistiche (falli, punti, calci sbagliati)
- Metodo per confrontare due giocatori (==, <, >) per id o performance
*/


