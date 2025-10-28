#ifndef GIOCATORE_H
#define GIOCATORE_H

#include "Persona.h"
#include <iostream>

// Evitare "using namespace std;" in header
class Giocatore : public Persona {
private:
    std::string ruolo;
    int id;

public:
    Giocatore(const std::string& nome, const std::string& cognome, int eta, const std::string& ruolo, int id);

    // Distruttore di default sufficiente
    ~Giocatore() = default;

    std::string getRuolo() const;
    void setRuolo(const std::string& nuovoRuolo);
    int getId() const;
    void setId(int nuovoId);

    friend std::ostream& operator<<(std::ostream& os, const Giocatore& g);
};

#endif

