#include "Giocatore.h"
using namespace std;

Giocatore::Giocatore(const string& nome,const string& cognome ,int eta, const string& ruolo, int id)
    : Persona(nome,cognome ,eta), ruolo(ruolo), id(id) {}

Giocatore::~Giocatore() {
    cout << "Distruttore Giocatore chiamato per: " << nome << endl;
}

string Giocatore::getRuolo() const { return ruolo; }
void Giocatore::setRuolo(const string& nuovoRuolo) { ruolo = nuovoRuolo; }

int Giocatore::getId() const { return id; }
void Giocatore::setId(int nuovoId) { id = nuovoId; }

ostream& operator<<(ostream& os, const Giocatore& g) {
    os << "Giocatore: " << g.getNome() << " (" << g.getEta() << " anni), Ruolo: "
       << g.getRuolo() << ", ID: " << g.getId();
    return os;
}

/*
Possibili aggiunte future:
- Metodo per aggiornare statistiche (falli, punti, calci sbagliati)
- Metodo per confrontare due giocatori (==, <, >) per id o performance
*/


