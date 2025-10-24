#include "Squadra.h"
using namespace std;

Squadra::Squadra(const string& nome, const string& indirizzo, int id)
    : nome(nome), indirizzo(indirizzo), id(id), punteggioClassifica(0) {}

Squadra::~Squadra() {
    cout << "Distruttore Squadra chiamato per: " << nome << endl;
}

string Squadra::getNome() const { return nome; }
string Squadra::getIndirizzo() const { return indirizzo; }
int Squadra::getId() const { return id; }
int Squadra::getPunteggio() const { return punteggioClassifica; }

void Squadra::setNome(const string& n) { nome = n; }
void Squadra::setIndirizzo(const string& i) { indirizzo = i; }
void Squadra::setId(int i) { id = i; }
void Squadra::setPunteggio(int p) { punteggioClassifica = p; }

void Squadra::addGiocatore(const Giocatore& g) {
    giocatori.push_back(g);
}

void Squadra::removeGiocatore(int id) {
    for (auto it = giocatori.begin(); it != giocatori.end(); ++it) {
        if (it->getId() == id) {
            giocatori.erase(it);
            break;
        }
    }
}

ostream& operator<<(ostream& os, const Squadra& s) {
    os << "Squadra: " << s.nome << " (ID: " << s.id << "), Punteggio: " 
       << s.punteggioClassifica << ", Indirizzo: " << s.indirizzo << endl;
    os << "Giocatori:" << endl;
    for (const auto& g : s.giocatori) {
        os << " - " << g << endl;
    }
    return os;
}

/*
Possibili aggiunte future:
-Aggiungere lista Staff alla squadra
-Calcolo automatico classifica da Partite
-Mancano eventuali controlli
*/


