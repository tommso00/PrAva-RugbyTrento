#ifndef STAFF_H
#define STAFF_H

#include "Persona.h"
#include <string>
#include <iostream>

/**
 * @enum RuoloStaff
 * @brief Enumerazione che definisce i possibili ruoli del personale tecnico/amministrativo.
 */
enum class RuoloStaff {
    ALLENATORE,           ///< Allenatore principale
    AIUTANTE_ALLENATORE,  ///< Vice-allenatore o tecnico specializzato
    DS,                   ///< Direttore Sportivo
    SEGRETERIA,           ///< Personale amministrativo
    ALLENATORE_MINI       ///< Allenatore delle giovanili/mini-rugby
};

/**
 * @class Staff
 * @brief Rappresenta un membro dello staff tecnico/amministrativo di una squadra di rugby.
 */
class Staff : public Persona {
protected:
    int id = 0;
    RuoloStaff ruolo;

public:
    /**
     * @brief Costruttore senza ID.
     * @param nome Nome staff
     * @param cognome Cognome staff
     * @param eta Età staff
     * @param ruolo Ruolo professionale
     */
    Staff(const std::string& nome, const std::string& cognome, int eta, RuoloStaff ruolo);
    
    /**
     * @brief Costruttore con ID.
     * @param id ID univoco
     * @param nome Nome staff
     * @param cognome Cognome staff
     * @param eta Età staff
     * @param ruolo Ruolo professionale
     */
    Staff(int id, const std::string& nome, const std::string& cognome, int eta, RuoloStaff ruolo);

    /**
     * @brief ID membro staff.
     * @return ID numerico
     */
    int getId() const;
    
    /**
     * @brief Imposta ID.
     * @param nuovoId Nuovo ID
     */
    void setId(int nuovoId);

    /**
     * @brief Ruolo professionale.
     * @return Enum RuoloStaff
     */
    RuoloStaff getRuolo() const;
    
    /**
     * @brief Imposta ruolo.
     * @param nuovoRuolo Nuovo ruolo
     */
    void setRuolo(RuoloStaff nuovoRuolo);

    /**
     * @brief Converte stringa ? RuoloStaff.
     * @param s Stringa ruolo
     * @return Enum corrispondente
     */
    static RuoloStaff stringToRuolo(const std::string& s);
    
    /**
     * @brief Converte RuoloStaff ? stringa.
     * @param r Enum ruolo
     * @return Stringa ruolo
     */
    static std::string ruoloToString(RuoloStaff r);

    /**
     * @brief Overload operator<< Staff.
     * @param os Stream output
     * @param s Staff da stampare
     * @return Stream modificato
     */
    friend std::ostream& operator<<(std::ostream& os, const Staff& s);
};

#endif

