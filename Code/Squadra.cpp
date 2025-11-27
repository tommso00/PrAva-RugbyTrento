#include "Squadra.h"
#include <algorithm>

// Costruttore
Squadra::Squadra(int id_, const std::string& nome_, const std::string& indirizzo_)
    : id(id_), nome(nome_), indirizzo(indirizzo_), punteggioClassifica(0) {}

// Getter/Setter info principali
std::string Squadra::getNome() const {
    return nome;
}

void Squadra::setNome(const std::string& n) {
    nome = n;
}

std::string Squadra::getIndirizzo() const {
    return indirizzo;
}

void Squadra::setIndirizzo(const std::string& i) {
    indirizzo = i;
}

int Squadra::getId() const {
    return id;
}

void Squadra::setId(int i) {
    id = i;
}

int Squadra::getPunteggio() const {
    return punteggioClassifica;
}

void Squadra::setPunteggio(int p) {
    punteggioClassifica = p;
}

// Aggiunge un giocatore al vettore
void Squadra::addGiocatore(const Giocatore& g) {
    giocatori.push_back(g);
}

// Rimuove un giocatore tramite id
void Squadra::removeGiocatore(int idGiocatore) {
    auto it = std::remove_if(giocatori.begin(), giocatori.end(),
        [idGiocatore](const Giocatore& g) { return g.getId() == idGiocatore; });
    if (it != giocatori.end()) {
        giocatori.erase(it, giocatori.end());
    }
}

// Operatore di stampa
std::ostream& operator<<(std::ostream& os, const Squadra& s) {
    os << "Squadra: " << s.nome << ", Indirizzo: " << s.indirizzo <<", ID: "<< s.getId()<<"\n";
    os << "Punteggio Classifica: " << s.punteggioClassifica << "\n";
    os << "Giocatori:\n";
    for (const auto& g : s.giocatori) {
        os << g << "\n"; // Presuppone operator<< per Giocatore
    }
    return os;
}

/*
Possibili aggiunte future:
-Aggiungere lista Staff alla squadra
-Calcolo automatico classifica da Partite
-Mancano eventuali controlli
*/


