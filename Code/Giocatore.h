#ifndef GIOCATORE_H
#define GIOCATORE_H

#include "Persona.h"
#include "StatsGiocatore.h"
#include <iostream>

// Evitare "using namespace std;" in header
class Giocatore : public Persona {
private:
    std::string ruolo;
    int id;
	
/*	
	//STATS GIOCATORE
	int placcaggiRiusciti;
	int placcaggiMancati;
	
	int metriCorsi;
	int lineBreaks;
	int difensoriBattuti;

	int metePartita;
	int meteStagione;

	int turnoverPartita;
	int turnoverStagione;

	int calciPiazzatiSegnatiPartita;
	int calciPiazzatiSegnatiStagione;

	int calciPiazzatiTentatiPartita;
	int calciPiazzatiTentatiStagione;

	int falliCommessiPartita;
	int falliCommessiStagione;

	int offload;
	double efficaciaRuck;

	int minutiGiocati;
	int partiteGiocate;
*/

	
public:
    Giocatore(const std::string& nome, const std::string& cognome, int eta, const std::string& ruolo, int id);

//aggiunto da ciaka
	StatsGiocatore statsPartita;
	StatsGiocatore statsStagione;

    ~Giocatore() = default;

    std::string getRuolo() const;
    void setRuolo(const std::string& nuovoRuolo);
    int getId() const;
    void setId(int nuovoId);
    
    //get/set x stats
    int getPlaccaggiRiusciti() const;
    void setPlaccaggiRiusciti(int v);

    int getPlaccaggiMancati() const;
    void setPlaccaggiMancati(int v);

    // Attacco
    int getMetriCorsi() const;
    void setMetriCorsi(int v);

    int getLineBreaks() const;
    void setLineBreaks(int v);

    int getDifensoriBattuti() const;
    void setDifensoriBattuti(int v);

    // Mete
    int getMetePartita() const;
    void setMetePartita(int v);

    int getMeteStagione() const;
    void setMeteStagione(int v);

    // Turnover
    int getTurnoverPartita() const;
    void setTurnoverPartita(int v);

    int getTurnoverStagione() const;
    void setTurnoverStagione(int v);

    // Calci piazzati
    int getCalciPiazzatiSegnatiPartita()const;
    void setCalciPiazzatiSegnatiPartita(int c);

    int getCalciPiazzatiSegnatiStagione() const;
    void setCalciPiazzatiSegnatiStagione(int c);

	int getCalciPiazzatiTentatiPartita()const;
	void setCalciPiazzatiTentatiPartita(int c);

	void setCalciPiazzatiTentatiStagione(int c);
	int getCalciPiazzatiTentatiStagione() const;


    // Falli
    int getFalliCommessiPartita() const;
    void setFalliCommessiPartita(int v);

    int getFalliCommessiStagione() const;
    void setFalliCommessiStagione(int v);

    // Altro
    int getOffloadPartita() const;
	int getOffloadStagione() const;
    void setOffloadPartita(int v);
	void setOffloadStagione(int v);

    double getEfficaciaRuck() const;
    void setEfficaciaRuck(double v);

    int getMinutiGiocati() const;
    void setMinutiGiocati(int v);

    int getPartiteGiocate() const;
    void setPartiteGiocate(int v);

	//metodo percentuale calcipiazzati
    double getPercentualeCalciPiazzatiStagione() const; 
	double getPercentualeCalciPiazzatiPartita() const; 

	
	
    friend std::ostream& operator<<(std::ostream& os, const Giocatore& g);
};

#endif

