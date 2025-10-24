#ifndef GIOCATORE_H
#define GIOCATORE_H

#include "Persona.h"
#include <iostream>
using namespace std;

class Giocatore : public Persona {
private:
    string ruolo;
    int id;

public:
    Giocatore(const string& nome,const string& cognome ,int eta, const string& ruolo, int id);
    ~Giocatore();

    string getRuolo() const;
    void setRuolo(const string& nuovoRuolo);
    int getId() const;
    void setId(int nuovoId);

    friend ostream& operator<<(ostream& os, const Giocatore& g);
};

#endif


