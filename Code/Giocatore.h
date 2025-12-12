#ifndef GIOCATORE_H
#define GIOCATORE_H

#include "Persona.h"
#include <iostream>

class Giocatore : public Persona {
private:
	
    // Attributi anagrafici e identificativi del giocatore
    std::string ruolo;		//ruolo nel campo (Es: "pilone" , "mediano", "ala")
    int id;					//identificazione univoca del giocatore
    
    // Statistiche sportive del giocatore

    int placcaggi;			//n. totale di placcaggi effettuati
    int metriCorsi;			//distanza totale percorsa in metri
    int mete;				//n. di mete
    int calciPiazzati;		//n. di calci piazzati riusciti
    int falliCommessi;		//n. di falli commessi
    int offload;			//n. di passaggi effettuati durante
    int minutiGiocati;		//tempo totali di gioco in minuti
    int partiteGiocate;		//n. complessivo di partite disputate

public:
    // Costruttori
    Giocatore(const std::string& nome, const std::string& cognome, int eta, 
              const std::string& ruolo, int id);
    
    // ? COPY CONSTRUCTOR--->Crea un nuovo oggetto duplicando tutti i dati di un’altra istanza.
    Giocatore(const Giocatore& other);
    
    // ? MOVE CONSTRUCTOR--->Trasferisce le risorse di un altro oggetto senza duplicazione di memoria.
    Giocatore(Giocatore&& other) noexcept;
    
    // ? COPY ASSIGNMENT--->Permette di copiare il contenuto da un altro oggetto della stessa classe.
    Giocatore& operator=(const Giocatore& other);
    
    // ? MOVE ASSIGNMENT--->Permette di trasferire i dati da un altro oggetto temporaneo, ottimizzando le prestazioni.
    Giocatore& operator=(Giocatore&& other) noexcept;
    
    //Distruttore virtuale predefinito. 
    //Libera le risorse allocate e consente la corretta distruzione delle classi derivate. 
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

	//Operatore di output per la stampa dei dati del giocatore.
    friend std::ostream& operator<<(std::ostream& os, const Giocatore& g);
};

#endif

