#ifndef STAFF_H
#define STAFF_H

#include "Persona.h"
#include <string>
#include <iostream>

// Rimuovere "using namespace std;" dai file header per evitare conflitti di nomi.

/**
 * @enum RuoloStaff
 * @brief Enumerazione che definisce i possibili ruoli del personale tecnico/amministrativo.
 * 
 * Elenca tutte le posizioni dello staff di una squadra di rugby:
 * - ALLENATORE: Allenatore principale
 * - AIUTANTE_ALLENATORE: Vice-allenatore o tecnico specializzato
 * - DS: Direttore Sportivo
 * - SEGRETERIA: Personale amministrativo
 * - ALLENATORE_MINI: Allenatore delle giovanili/mini-rugby
 */
enum RuoloStaff {
    ALLENATORE,           ///< Allenatore principale della prima squadra.
    AIUTANTE_ALLENATORE,  ///< Vice-allenatore o tecnico specializzato.
    DS,                   ///< Direttore Sportivo.
    SEGRETERIA,           ///< Personale amministrativo/segreteria.
    ALLENATORE_MINI       ///< Allenatore delle categorie giovanili/mini-rugby.
};

/**
 * @class Staff
 * @brief Rappresenta un membro dello staff tecnico/amministrativo di una squadra di rugby.
 * 
 * Estende la classe base Persona aggiungendo il ruolo specifico all'interno 
 * dell'organizzazione della squadra. Include i membri comuni (nome, cognome, età) 
 * più il ruolo professionale (allenatore, DS, segretario, ecc.).
 */
class Staff : public Persona {
protected:
    RuoloStaff ruolo; ///< Ruolo professionale del membro dello staff all'interno del club.

public:
    /**
     * @brief Costruttore della classe Staff.
     * 
     * Inizializza un membro dello staff con i dati anagrafici e il ruolo professionale.
     * 
     * @param nome Nome del membro dello staff.
     * @param cognome Cognome del membro dello staff.
     * @param eta Età del membro dello staff.
     * @param ruolo Ruolo professionale (enum RuoloStaff).
     */
    Staff(const std::string& nome, const std::string& cognome, int eta, RuoloStaff ruolo);

    /**
     * @brief Distruttore della classe.
     * 
     * Libera le risorse allocate e chiama il distruttore della classe base Persona.
     */
    ~Staff() = default;

    // *** METODI GETTER E SETTER ***

    /**
     * @brief Restituisce il ruolo professionale del membro dello staff.
     * @return Valore dell'enumerazione RuoloStaff.
     */
    RuoloStaff getRuolo() const;

    /**
     * @brief Modifica il ruolo professionale del membro dello staff.
     * 
     * @param nuovoRuolo Nuovo ruolo da assegnare (enum RuoloStaff).
     */
    void setRuolo(RuoloStaff nuovoRuolo);

    /**
     * @brief Operatore di output per la stampa delle informazioni dello staff.
     * 
     * Visualizza nome, cognome, età e ruolo in formato leggibile su uno stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Staff& s);

    /**
     * @brief Converte un valore di enumerazione RuoloStaff in stringa leggibile.
     * 
     * Metodo statico ausiliario per la visualizzazione del ruolo in formato testuale.
     * Utile per logging, interfacce utente o debug.
     * 
     * @param r Valore dell'enumerazione da convertire.
     * @return Stringa che rappresenta il ruolo (es. "ALLENATORE", "DS", ecc.).
     */
    static std::string ruoloToString(RuoloStaff r);
};

#endif

