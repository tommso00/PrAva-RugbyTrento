#ifndef PARTITA_H
#define PARTITA_H

#include "Squadra.h"
#include <string>
#include <iostream>




// Non usare "using namespace std;" nei file header
class Partita {
private:
	
	//dati identificativi della partita
    int id;				//identificatore univoco della partita
	int data;			//data della partita
    
    //squadre coinvolte
	Squadra locali;		//squadra che gioca in casa
    Squadra ospiti;		//squadra che gioca in trasferta
    
//Statistiche di gioco e andamento della partita
	int cartellinoRossoLoc;  	// Numero di cartellini rossi ricevuti dai locali
	int cartellinoRossoOsp;  	// Numero di cartellini rossi ricevuti dagli ospiti
	int cartellinoGialloLoc; 	// Numero di cartellini gialli ricevuti dai locali
	int cartellinoGialloOsp; 	// Numero di cartellini gialli ricevuti dagli ospiti
	
	double possessoLoc;      // Percentuale di possesso palla dei locali
	double possessoOsp;      // Percentuale di possesso palla degli ospiti
	
	int ptLocali;            ///< Punti totali segnati dai locali
	int ptOspiti;            ///< Punti totali segnati dagli ospiti
	int meteLocali;          ///< Numero di mete segnate dai locali
	int meteOspiti;          ///< Numero di mete segnate dagli ospiti
    
public:

	//Costruttore della classe Partita
    Partita(int id, int data, const Squadra& locali, const Squadra& ospiti);

    // Il distruttore di default è sufficiente: nessun puntatore o risorsa dinamica gestita manualmente
    ~Partita() = default;

	
	// ***METODI GETTER PRINCIPALI***
    
	int getId() const;		//Restituisce identificatore univodo della partita
    int getData() const;	//Restituisce la data dell’incontro.
        
    const Squadra& getLocali() const;	//Restituisce un riferimento costante alla squadra di casa.
    const Squadra& getOspiti() const;	//Restituisce un riferimento costante alla squadra ospite.


    // *** METODI PER GESTIRE IL PUNTEGGIO ***

	int getPuntiLocali() const;			//Punti totali degnati dai locali
    int getPuntiOspiti() const;			//Punti totali segnati dagli ospiti
	void setPuntiLocali(int value);		//Imposta i punti segnati dai locali
	void setPuntiOspiti(int value);		//Imposta i punti segnati dagli ospiti

    
    // *** METE E STATISTICHE DI GIOCO ***

    int getMeteLocali() const;     //Restituisce il numero di mete segnate dai locali.
    int getMeteOspiti() const;     //Restituisce il numero di mete segnate dagli ospiti.
    void setMeteLocali(int val);   //Imposta il numero di mete segnate dai locali.
    void setMeteOspiti(int val);   //Imposta il numero di mete segnate dagli ospiti.

    
    // *** CARTELLINI DISCIPLINARI ***
    
	int getCartellinoRossoLoc() const;
	void setCartellinoRossoLoc(int value);

	int getCartellinoRossoOsp() const;
	void setCartellinoRossoOsp(int value);

	int getCartellinoGialloLoc() const;
	void setCartellinoGialloLoc(int value);
	
	int getCartellinoGialloOsp() const;
	void setCartellinoGialloOsp(int value);

	double getPossessoLoc() const;
	void setPossessoLoc(double value);

	double getPossessoOsp() const;
	void setPossessoOsp(double value);

    std::string getPunteggioPartita() const; 
    void setRisultato(int ptLocali, int ptOspiti);
	

	
	
	




    // Serve lo scope std:: per ostream, non "using namespace std;"
    friend std::ostream& operator<<(std::ostream& os, const Partita& p);
};

#endif

