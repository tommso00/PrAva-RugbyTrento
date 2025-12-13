#ifndef GIOCATORE_H
#define GIOCATORE_H

#include "Persona.h"
#include <iostream>

/**
 * @class Giocatore
 * @brief Rappresenta un giocatore di rugby che eredita le caratteristiche di una Persona.
 * 
 * Questa classe estende la classe base Persona aggiungendo informazioni specifiche 
 * relative al ruolo sportivo del giocatore e alle sue statistiche di gioco. 
 * È progettata per fornire un modello solido da utilizzare all’interno di software 
 * di gestione di squadre, tornei o analisi delle prestazioni.
 */
class Giocatore : public Persona {
private:
    // Attributi anagrafici e identificativi del giocatore
    std::string ruolo;   ///< Ruolo nel campo (es. "pilone", "mediano", "ala", ecc.)
    int id;              ///< Identificatore univoco del giocatore
    
    // Statistiche sportive del giocatore
    int placcaggi;       ///< Numero totale di placcaggi effettuati
    int metriCorsi;      ///< Distanza totale percorsa in metri
    int mete;            ///< Numero di mete segnate
    int calciPiazzati;   ///< Numero di calci piazzati riusciti
    int falliCommessi;   ///< Numero di falli commessi
    int offload;         ///< Numero di passaggi effettuati durante il contatto
    int minutiGiocati;   ///< Tempo totale di gioco espresso in minuti
    int partiteGiocate;  ///< Numero complessivo di partite disputate

public:
    /**
     * @brief Costruttore principale della classe Giocatore.
     * 
     * @param nome Nome del giocatore (ereditato da Persona)
     * @param cognome Cognome del giocatore
     * @param eta Età del giocatore
     * @param ruolo Ruolo in campo (es. "mediano di mischia")
     * @param id Identificatore univoco del giocatore
     */
    Giocatore(const std::string& nome, const std::string& cognome, int eta,
              const std::string& ruolo, int id);
    
    /**
     * @brief Costruttore di copia.
     * Crea un nuovo oggetto duplicando tutti i dati di un’altra istanza.
     */
    Giocatore(const Giocatore& other);
    
    /**
     * @brief Costruttore di move.
     * Trasferisce le risorse di un altro oggetto senza duplicazione di memoria.
     */
    Giocatore(Giocatore&& other) noexcept;
    
    /**
     * @brief Operatore di assegnazione per copia.
     * Permette di copiare il contenuto da un altro oggetto della stessa classe.
     */
    Giocatore& operator=(const Giocatore& other);
    
    /**
     * @brief Operatore di assegnazione per move.
     * Permette di trasferire i dati da un altro oggetto temporaneo, ottimizzando le prestazioni.
     */
    Giocatore& operator=(Giocatore&& other) noexcept;
    
    /**
     * @brief Distruttore virtuale predefinito.
     * Libera le risorse allocate e consente la corretta distruzione delle classi derivate.
     */
    ~Giocatore() = default;

    // *** Metodi di accesso agli attributi ***

    // Ruolo e identificatore
    std::string getRuolo() const; 
    void setRuolo(const std::string& nuovoRuolo);

    int getId() const; 
    void setId(int nuovoId);

    // Statistiche di gioco
    int getPlaccaggi() const; void setPlaccaggi(int value);
    int getMetriCorsi() const; void setMetriCorsi(int value);
    int getMete() const; void setMete(int value);
    int getCalciPiazzati() const; void setCalciPiazzati(int value);
    int getFalliCommessi() const; void setFalliCommessi(int value);
    int getOffload() const; void setOffload(int value);
    int getMinutiGiocati() const; void setMinutiGiocati(int value);
    int getPartiteGiocate() const; void setPartiteGiocate(int value);

    /**
     * @brief Operatore di output per la stampa dei dati del giocatore.
     * 
     * Permette di inviare a uno stream (es. std::cout) una descrizione formattata 
     * dell’oggetto Giocatore, mostrando informazioni rilevanti per il debug o la visualizzazione.
     */
    friend std::ostream& operator<<(std::ostream& os, const Giocatore& g);
};

#endif

