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
    

	int possessoPalla;               // percentuale 0-100
    double territorio;            // percentuale 0-100

//somma delle stats dei singoli per squadra
    int placcaggiTotali;
    int metriGuadagnatiTotali;	//metriCorsiTot
	int meteTotali;
    int falliTotali;

//set e get imprtanti 
    int mischieVinte;
    int mischiePerse;

    int toucheVinte;
    int touchePerse;    
    

public:
    Squadra(int id_, const std::string& nome, const std::string& indirizzo);
    
    // ? COPY/MOVE
    Squadra(const Squadra& other);
    Squadra(Squadra&& other) noexcept;
    Squadra& operator=(const Squadra& other);
    Squadra& operator=(Squadra&& other) noexcept;

    // Distruttore di default, poiché vector e string gestiscono la memoria automaticamente
    ~Squadra() = default;

	//GET-SET dati
    std::string getNome() const;
    std::string getIndirizzo() const;
    int getId() const;
    int getPunteggio() const;
	const std::vector<Giocatore>& getGiocatori() const{return giocatori;}
	
    void setNome(const std::string& n);
    void setIndirizzo(const std::string& i);
    void setId(int i);
    void setPunteggio(int p);

	//ADD-REMOVE giocatore
    void addGiocatore(const Giocatore& g);
    void removeGiocatore(int id);
    
    // Statistiche generali di squadra
	int getPossessoPalla() const;
	void setPossessoPalla(int value);

	double getTerritorio() const;
	void setTerritorio(double value);

	int getPlaccaggiTotali() const;
	void setPlaccaggiTotali(int value);

	int getMetriGuadagnatiTotali() const;
	void setMetriGuadagnatiTotali(int value);

	int getMeteTotali() const;
	void setMeteTotali(int value);

	int getFalliTotali() const;
	void setFalliTotali(int value);

	void aggiungiPuntiClassifica(int delta){punteggioClassifica += delta;}
	void aggiungiMete(int delta){meteTotali +=delta;}
	
	// Mischie e touche
	int getMischieVinte() const;
	void setMischieVinte(int value);

	int getMischiePerse() const;
	void setMischiePerse(int value);

	int getToucheVinte() const;
	void setToucheVinte(int value);

	int getTouchePerse() const;
	void setTouchePerse(int value);

	void aggiornaStatistiche();
	
	//metodi per classifica
	void addPuntiClassifica(int delta);
	void addMete(int delta);


    friend std::ostream& operator<<(std::ostream& os, const Squadra& s);
};

#endif

