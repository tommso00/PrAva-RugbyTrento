#include "Giocatore.h"
#include <sstream>

Giocatore::Giocatore() : id(0), nome(""), cognome(""), eta(0), punteggioTotale(0.0) {}
Giocatore::Giocatore(int id, string nome, string cognome, int eta, double punteggio)
    : id(id), nome(nome), cognome(cognome), eta(eta), punteggioTotale(punteggio) {}
Giocatore::~Giocatore() {}

int Giocatore::getId() const { return id; }
string Giocatore::getNome() const { return nome; }
string Giocatore::getCognome() const { return cognome; }
int Giocatore::getEta() const { return eta; }
double Giocatore::getPunteggio() const { return punteggioTotale; }
void Giocatore::setPunteggio(double punteggio) { punteggioTotale = punteggio; }

string Giocatore::toString() const {
    return "Giocatore [" + to_string(id) + "] " + nome + " " + cognome +
           ", eta: " + to_string(eta) + ", punti: " + to_string(punteggioTotale);
}

string Giocatore::toCSV() const {
    // id,nome,cognome,eta,punteggio
    ostringstream oss;
    oss << id << "," << nome << "," << cognome << "," << eta << "," << punteggioTotale;
    return oss.str();
}

Giocatore Giocatore::fromCSV(const string &line) {
    istringstream iss(line);
    string token;
    int id = 0;
    string nome, cognome;
    int eta = 0;
    double punteggio = 0.0;

    auto next = [&](string &out) {
        if (!getline(iss, out, ',')) out = "";
    };

    next(token); if (!token.empty()) id = stoi(token);
    next(nome);
    next(cognome);
    next(token); if (!token.empty()) eta = stoi(token);
    next(token); if (!token.empty()) punteggio = stod(token);

    return Giocatore(id, nome, cognome, eta, punteggio);
}

