#ifndef PARTITA_H
#define PARTITA_H

#include "Squadra.h"
#include <string>
#include <iostream>

/**
 * @class Partita
 * @brief Rappresenta un incontro sportivo tra due squadre di rugby.
 * 
 * La classe modella i dati fondamentali relativi a una partita:
 * - Informazioni identificative (id, data)
 * - Le due squadre coinvolte (locali e ospiti)
 * - Le principali statistiche di gioco (punteggi, cartellini, possesso palla, mete, ecc.)
 * 
 * Serve come unità logica per gestire e analizzare i risultati sportivi
 * all’interno di un sistema di gestione di campionati.
 */
class Partita {
private:
    // Dati identificativi della partita
    int id;     ///< Identificatore univoco della partita
    int data;   ///< Data della partita (si può rappresentare come intero o timestamp)
    
    // Squadre coinvolte
    Squadra locali;  ///< Squadra che gioca in casa
    Squadra ospiti;  ///< Squadra che gioca in trasferta
    
    // Statistiche di gioco e andamento della partita
	int cartellinoRossoLoc;  ///< Numero di cartellini rossi ricevuti dai locali
	int cartellinoRossoOsp;  ///< Numero di cartellini rossi ricevuti dagli ospiti
	int cartellinoGialloLoc; ///< Numero di cartellini gialli ricevuti dai locali
	int cartellinoGialloOsp; ///< Numero di cartellini gialli ricevuti dagli ospiti
	double possessoLoc;      ///< Percentuale di possesso palla dei locali
	double possessoOsp;      ///< Percentuale di possesso palla degli ospiti
	int ptLocali;            ///< Punti totali segnati dai locali
	int ptOspiti;            ///< Punti totali segnati dagli ospiti
	int meteLocali;          ///< Numero di mete segnate dai locali
	int meteOspiti;          ///< Numero di mete segnate dagli ospiti

public:
    /**
     * @brief Costruttore della classe Partita.
     * 
     * Inizializza un nuovo oggetto rappresentante una partita specificando
     * le due squadre e le principali informazioni organizzative.
     * 
     * @param id Identificatore univoco della partita.
     * @param data Data della partita (formato numerico o timestamp).
     * @param locali Squadra che gioca in casa.
     * @param ospiti Squadra che gioca fuori casa.
     */
    Partita(int id, int data, const Squadra& locali, const Squadra& ospiti);

    /**
     * @brief Distruttore di default.
     * 
     * Poiché non vengono gestite risorse dinamiche (puntatori o allocazioni manuali),
     * il distruttore predefinito è sufficiente.
     */
    ~Partita() = default;

    // *** METODI GETTER PRINCIPALI ***

    int getId() const;      ///< Restituisce l’identificatore univoco della partita.
    int getData() const;    ///< Restituisce la data dell’incontro.

    const Squadra& getLocali() const; ///< Restituisce un riferimento costante alla squadra di casa.
    const Squadra& getOspiti() const; ///< Restituisce un riferimento costante alla squadra ospite.

    // *** METODI PER GESTIRE IL PUNTEGGIO ***

	int getPuntiLocali() const;   ///< Punti totali segnati dai locali.
    int getPuntiOspiti() const;   ///< Punti totali segnati dagli ospiti.
	void setPuntiLocali(int value); ///< Imposta i punti segnati dai locali.
	void setPuntiOspiti(int value); ///< Imposta i punti segnati dagli ospiti.

    // *** METE E STATISTICHE DI GIOCO ***

    int getMeteLocali() const;     ///< Restituisce il numero di mete segnate dai locali.
    int getMeteOspiti() const;     ///< Restituisce il numero di mete segnate dagli ospiti.
    void setMeteLocali(int val);   ///< Imposta il numero di mete segnate dai locali.
    void setMeteOspiti(int val);   ///< Imposta il numero di mete segnate dagli ospiti.

    // *** CARTELLINI DISCIPLINARI ***

	int getCartellinoRossoLoc() const; ///< Cartellini rossi della squadra locale.
	void setCartellinoRossoLoc(int value);

	int getCartellinoRossoOsp() const; ///< Cartellini rossi della squadra ospite.
	void setCartellinoRossoOsp(int value);

	int getCartellinoGialloLoc() const; ///< Cartellini gialli della squadra locale.
	void setCartellinoGialloLoc(int value);
	
	int getCartellinoGialloOsp() const; ///< Cartellini gialli della squadra ospite.
	void setCartellinoGialloOsp(int value);

    // *** POSSESSO PALLA ***

	double getPossessoLoc() const; ///< Percentuale di possesso palla dei locali (0–100%).
	void setPossessoLoc(double value);

	double getPossessoOsp() const; ///< Percentuale di possesso palla degli ospiti.
	void setPossessoOsp(double value);

    // *** RISULTATO E STAMPA ***

    /**
     * @brief Restituisce una rappresentazione testuale del punteggio finale.
     * 
     * Il formato può essere, ad esempio: "Locali 27 - 22 Ospiti".
     */
    std::string getPunteggioPartita() const; 

    /**
     * @brief Imposta il risultato della partita.
     * 
     * @param ptLocali Punti totali segnati dalla squadra di casa.
     * @param ptOspiti Punti totali segnati dalla squadra ospite.
     */
    void setRisultato(int ptLocali, int ptOspiti);

    /**
     * @brief Operatore di output per la stampa della partita.
     * 
     * Permette di visualizzare in modo leggibile le principali informazioni 
     * della partita direttamente su uno stream di output (es. std::cout).
     */
    friend std::ostream& operator<<(std::ostream& os, const Partita& p);
};

#endif

