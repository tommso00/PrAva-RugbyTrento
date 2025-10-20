#ifndef PARTITA_H
#define PARTITA_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
using namespace std;

class Giocatore; // forward

class Partita {
private:
    int id;
    string data; // es. "2025-10-14"
    vector<shared_ptr<Giocatore>> giocatori;
    map<int, double> punteggi; // key = giocatore.id

public:
    Partita();
    Partita(int id, string data);
    ~Partita();

    int getId() const;
    string getData() const;

    void aggiungiGiocatore(shared_ptr<Giocatore> g);
    void setPunteggio(shared_ptr<Giocatore> g, double punti);
    double getPunteggio(shared_ptr<Giocatore> g) const;
    vector<shared_ptr<Giocatore>> getGiocatori() const;
    string toString() const;

    // Serializzazione CSV
    string toCSV() const;
    // fromCSV richiede la lista di giocatori disponibili (shared_ptr) per ricostruire i riferimenti
    static Partita fromCSV(const string &line, const vector<shared_ptr<Giocatore>> &giocatoriDisponibili);
};

#endif // PARTITA_H

