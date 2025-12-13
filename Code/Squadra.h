#ifndef SQUADRA_H
#define SQUADRA_H

#include <string>
#include <vector>
#include <iostream>
#include "Giocatore.h"
#include "Staff.h"

// Evitare "using namespace std;" nei file header per prevenire conflitti di nomi.

/**
 * @class Squadra
 * @brief Rappresenta una squadra di rugby composta da giocatori e staff.
 * 
 * La classe incapsula i dati principali relativi a una squadra:
 * - Informazioni di identificazione (nome, indirizzo, id)
 * - Roster (elenco dei giocatori)
 * - Statistiche complessive di squadra (placcaggi, metri guadagnati, mete, falli, ecc.)
 * 
 * È progettata per essere utilizzata in software di gestione sportiva,
 * analisi delle prestazioni o simulazione di campionati.
 */
class Squadra {
private:
    // Identificativi e dati anagrafici della squadra
    std::string nome;        ///< Nome ufficiale della squadra.
    std::string indirizzo;   ///< Sede o indirizzo della società sportiva.
    int id;                  ///< Identificatore univoco della squadra.
    int punteggioClassifica; ///< Punteggio accumulato in classifica (campionato o torneo).

    // Roster della squadra
    std::vector<Giocatore> giocatori; ///< Elenco dei giocatori che fanno parte della squadra.

    // Statistiche di gioco generali
    int possessoPalla;             ///< Percentuale media di possesso palla (0–100%).
    double territorio;             ///< Percentuale di presenza territoriale (0–100%).

    // Statistiche aggregate derivate dai singoli giocatori
    int placcaggiTotali;           ///< Totale dei placcaggi sommati per tutta la squadra.
    int metriGuadagnatiTotali;     ///< Totale dei metri corsi da tutti i giocatori.
    int meteTotali;                ///< Totale delle mete segnate dalla squadra.
    int falliTotali;               ///< Totale dei falli commessi dalla squadra.

    // Performance in fasi statiche di gioco
    int mischieVinte;              ///< Numero di mischie vinte.
    int mischiePerse;              ///< Numero di mischie perse.
    int toucheVinte;               ///< Numero di touche vinte.
    int touchePerse;               ///< Numero di touche perse.

public:
    /**
     * @brief Costruttore della classe Squadra.
     * 
     * @param id_ Identificatore della squadra.
     * @param nome Nome della squadra.
     * @param indirizzo Indirizzo o sede del club.
     */
    Squadra(int id_, const std::string& nome, const std::string& indirizzo);

    // *** COPY & MOVE SEMANTICS ***
    Squadra(const Squadra& other);              ///< Costruttore di copia.
    Squadra(Squadra&& other) noexcept;          ///< Costruttore di move.
    Squadra& operator=(const Squadra& other);   ///< Operatore di assegnazione per copia.
    Squadra& operator=(Squadra&& other) noexcept; ///< Operatore di assegnazione per move.

    /**
     * @brief Distruttore di default.
     * 
     * Le classi std::string e std::vector si occupano automaticamente
     * della gestione della memoria, quindi non sono necessarie azioni personalizzate.
     */
    ~Squadra() = default;

    // *** METODI GETTER E SETTER DI BASE ***

    std::string getNome() const;              ///< Restituisce il nome della squadra.
    std::string getIndirizzo() const;         ///< Restituisce l’indirizzo del club.
    int getId() const;                        ///< Restituisce l’identificatore numerico.
    int getPunteggio() const;                 ///< Restituisce il punteggio totale in classifica.

    const std::vector<Giocatore>& getGiocatori() const { return giocatori; } ///< Accesso in sola lettura al vettore di giocatori.

    void setNome(const std::string& n);       ///< Imposta un nuovo nome per la squadra.
    void setIndirizzo(const std::string& i);  ///< Imposta un nuovo indirizzo.
    void setId(int i);                        ///< Imposta l’identificatore della squadra.
    void setPunteggio(int p);                 ///< Aggiorna il punteggio di classifica.

    // *** GESTIONE GIOCATORI ***

    void addGiocatore(const Giocatore& g);    ///< Aggiunge un nuovo giocatore al roster.
    void removeGiocatore(int id);             ///< Rimuove un giocatore dal roster tramite il suo ID.

    // *** STATISTICHE DI SQUADRA ***

	int getPossessoPalla() const;             ///< Percentuale di possesso palla.
	void setPossessoPalla(int value);         ///< Aggiorna la percentuale di possesso palla.

	double getTerritorio() const;             ///< Percentuale di dominio territoriale.
	void setTerritorio(double value);         ///< Imposta la percentuale di territorio.

	int getPlaccaggiTotali() const;           ///< Restituisce il totale dei placcaggi.
	void setPlaccaggiTotali(int value);       ///< Imposta il totale dei placcaggi.

	int getMetriGuadagnatiTotali() const;     ///< Restituisce i metri complessivi guadagnati.
	void setMetriGuadagnatiTotali(int value); ///< Imposta i metri guadagnati totali.

	int getMeteTotali() const;                ///< Restituisce il numero di mete totali.
	void setMeteTotali(int value);            ///< Imposta il numero di mete totali.

	int getFalliTotali() const;               ///< Restituisce il numero di falli totali.
	void setFalliTotali(int value);           ///< Imposta il numero di falli totali.

    /**
     * @brief Aggiunge punti al punteggio di classifica.
     * 
     * @param delta Quantità di punti da aggiungere (può essere anche negativa).
     */
	void aggiungiPuntiClassifica(int delta) { punteggioClassifica += delta; }

    /**
     * @brief Incrementa il numero di mete totali.
     * 
     * @param delta Numero di mete da aggiungere (solitamente 1 a partita).
     */
	void aggiungiMete(int delta) { meteTotali += delta; }

    // *** MISCHIE E TOUCHE ***

	int getMischieVinte() const;
	void setMischieVinte(int value);

	int getMischiePerse() const;
	void setMischiePerse(int value);

	int getToucheVinte() const;
	void setToucheVinte(int value);

	int getTouchePerse() const;
	void setTouchePerse(int value);

    /**
     * @brief Aggiorna le statistiche generali della squadra
     *        a partire dai dati raccolti dai singoli giocatori.
     * 
     * Tipicamente utilizzato dopo una partita per sincronizzare
     * i valori aggregati (es. somma dei placcaggi o dei metri corsi).
     */
	void aggiornaStatistiche();

	// Metodi alternativi per aggiornare classifiche o punteggi
	void addPuntiClassifica(int delta);
	void addMete(int delta);

    /**
     * @brief Operatore di output per la stampa delle informazioni sulla squadra.
     * 
     * Consente di visualizzare i dati principali della squadra
     * (nome, id, punteggio e statistiche) in modo leggibile tramite stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Squadra& s);
};

#endif

