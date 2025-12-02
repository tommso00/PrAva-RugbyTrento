#ifndef SQUADRA_H
#define SQUADRA_H

#include <string>
#include <vector>
#include <iostream>
#include "Giocatore.h"
#include "Staff.h"

// Evitare "using namespace std;" negli header
class Squadra {
private:
    std::string nome;
    std::string indirizzo;
    int id;
    int punteggioClassifica;
    std::vector<Giocatore> giocatori;
    
/*
	int possessoPalla;               // percentuale 0-100
    double territorio;            // percentuale 0-100

    int placcaggiTotali;
    int metriGuadagnatiTotali;

    int turnoverVinti;

    int mischieVinte;
    int mischiePerse;

    int toucheVinte;
    int touchePerse;

    int calciPiazzatiSegnati;
    int calciPiazzatiTentati;

    int meteSegnate;
    int falliCommessi;

    // Percentuale calci piazzati
    double getPercentualeCalciPiazzati() const {
        if (calciPiazzatiTentati == 0)
            return 0.0;
        return 100.0 * calciPiazzatiSegnati / calciPiazzatiTentati;
    }

*/    
    
    

public:
    Squadra(int id_, const std::string& nome, const std::string& indirizzo);

    // Distruttore di default, poiché vector e string gestiscono la memoria automaticamente
    ~Squadra() = default;

    std::string getNome() const;
    std::string getIndirizzo() const;
    int getId() const;
    int getPunteggio() const;
	const std::vector<Giocatore>& getGiocatori() const{return giocatori;}
	
    void setNome(const std::string& n);
    void setIndirizzo(const std::string& i);
    void setId(int i);
    void setPunteggio(int p);

    void addGiocatore(const Giocatore& g);
    void removeGiocatore(int id);

    friend std::ostream& operator<<(std::ostream& os, const Squadra& s);
};

#endif

