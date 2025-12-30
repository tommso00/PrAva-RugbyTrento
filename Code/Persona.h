#ifndef PERSONA_H
#define PERSONA_H

#include <string>

// Evitare "using namespace std;" nei file header per prevenire conflitti di nomi.
// Si utilizza invece il fully-qualified name (std::string)

/**
 * @class Persona
 * @brief Classe base che rappresenta una persona generica.
 * 
 * La classe definisce gli attributi fondamentali comuni a tutte le persone:
 * nome, cognome ed età. È pensata per essere una classe base astratta o 
 * generica, destinata a essere estesa da altre classi (es. Giocatore e Staff)
 * che aggiungono comportamenti o proprietà più specifiche.
 */
class Persona {
protected:
    std::string nome;    ///< Nome della persona.
    std::string cognome; ///< Cognome della persona.
    int eta;             ///< Età della persona espressa in anni.

public:
    /**
     * @brief Costruttore della classe Persona.
     * 
     * Inizializza un oggetto Persona con i dati anagrafici forniti.
     * 
     * @param nome Nome della persona.
     * @param cognome Cognome della persona.
     * @param eta Età della persona.
     */
    Persona(const std::string& nome, const std::string& cognome, int eta);

    /**
     * @brief Distruttore virtuale.
     * 
     * Dichiarato virtuale per assicurare il corretto comportamento 
     * in caso di distruzione attraverso puntatori alla classe base 
     * (polimorfismo). Permette una corretta deallocazione nelle classi derivate.
     */
    virtual ~Persona();

    // *** METODI GETTER ***

    /**
     * @brief Restituisce il nome della persona.
     * @return Nome come stringa.
     */
    std::string getNome() const;

    /**
     * @brief Restituisce il cognome della persona.
     * @return Cognome come stringa.
     */
    std::string getCognome() const;

    /**
     * @brief Restituisce l’età della persona.
     * @return Età espressa in anni.
     */
    int getEta() const;

    /**
     * @brief Metodo virtuale per la stampa delle informazioni della persona.
     * 
     * Può essere ridefinito nelle classi derivate per aggiungere ulteriori dettagli.
     * Esempio: nella classe Giocatore, questo metodo potrebbe visualizzare 
     * anche ruolo e statistiche.
     */
    virtual void stampaInfo() const;
};

#endif

