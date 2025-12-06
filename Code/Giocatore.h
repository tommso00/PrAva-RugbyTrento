#ifndef GIOCATORE_H
#define GIOCATORE_H

#include "Persona.h"
#include <iostream>

class Giocatore : public Persona {
private:
    std::string ruolo;
    int id;
    
    // STATS GIOCATORE
    int placcaggi;
    int metriCorsi;
    int mete;
    int calciPiazzati;
    int falliCommessi;
    int offload;
    int minutiGiocati;
    int partiteGiocate;	

public:
    // Costruttori
    Giocatore(const std::string& nome, const std::string& cognome, int eta, 
              const std::string& ruolo, int id);
    
    // ? COPY CONSTRUCTOR
    Giocatore(const Giocatore& other);
    
    // ? MOVE CONSTRUCTOR
    Giocatore(Giocatore&& other) noexcept;
    
    // ? COPY ASSIGNMENT
    Giocatore& operator=(const Giocatore& other);
    
    // ? MOVE ASSIGNMENT
    Giocatore& operator=(Giocatore&& other) noexcept;
    
    ~Giocatore() = default;

    // Getters/Setters esistenti...
    std::string getRuolo() const;
    void setRuolo(const std::string& nuovoRuolo);
    int getId() const;
    void setId(int nuovoId);

    int getPlaccaggi() const; void setPlaccaggi(int value);
    int getMetriCorsi() const; void setMetriCorsi(int value);
    int getMete() const; void setMete(int value);
    int getCalciPiazzati() const; void setCalciPiazzati(int value);
    int getFalliCommessi() const; void setFalliCommessi(int value);
    int getOffload() const; void setOffload(int value);
    int getMinutiGiocati() const; void setMinutiGiocati(int value);
    int getPartiteGiocate() const; void setPartiteGiocate(int value);

    friend std::ostream& operator<<(std::ostream& os, const Giocatore& g);
};

#endif

