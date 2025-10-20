#ifndef GIOCATORE_H
#define GIOCATORE_H

#include <iostream>
#include <string>
using namespace std;

class Giocatore {
private:
    int id;
    string nome;
    string cognome;
    int eta;
    double punteggioTotale;

public:
    Giocatore();
    Giocatore(int id, string nome, string cognome, int eta, double punteggio);
    ~Giocatore();

    int getId() const;
    string getNome() const;
    string getCognome() const;
    int getEta() const;
    double getPunteggio() const;
    void setPunteggio(double punteggio);
    string toString() const;

    // Serializzazione CSV
    string toCSV() const;
    static Giocatore fromCSV(const string &line);
};

#endif 

