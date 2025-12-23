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
    int id = 0;
    RuoloStaff ruolo;

public:
    Staff(const std::string& nome, const std::string& cognome, int eta, RuoloStaff ruolo);
    Staff(int id, const std::string& nome, const std::string& cognome, int eta, RuoloStaff ruolo);

    int getId() const;
    void setId(int nuovoId);

    RuoloStaff getRuolo() const;
    void setRuolo(RuoloStaff nuovoRuolo);

    static RuoloStaff stringToRuolo(const std::string& s);
    static std::string ruoloToString(RuoloStaff r);

    friend std::ostream& operator<<(std::ostream& os, const Staff& s);
};



#endif

