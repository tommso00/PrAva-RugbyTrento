#include "Staff.h"

/**
 * @brief Costruttore Staff senza ID (da assegnare al salvataggio).
 */
Staff::Staff(const std::string& nome,
             const std::string& cognome,
             int eta,
             RuoloStaff ruolo)
    : Persona(nome, cognome, eta),
      id(0),
      ruolo(ruolo) {}

/**
 * @brief Costruttore Staff con ID (letto da CSV).
 */
Staff::Staff(int id,
             const std::string& nome,
             const std::string& cognome,
             int eta,
             RuoloStaff ruolo)
    : Persona(nome, cognome, eta),
      id(id),
      ruolo(ruolo) {}

/**
 * @brief Restituisce ID univoco staff.
 */
int Staff::getId() const { return id; }

/**
 * @brief Imposta ID univoco staff.
 */
void Staff::setId(int nuovoId) { id = nuovoId; }

/**
 * @brief Restituisce ruolo.
 */
RuoloStaff Staff::getRuolo() const { return ruolo; }

/**
 * @brief Imposta ruolo.
 */
void Staff::setRuolo(RuoloStaff nuovoRuolo) { ruolo = nuovoRuolo; }

/**
 * @brief Converte stringa in enum RuoloStaff.
 */
RuoloStaff Staff::stringToRuolo(const std::string& s) {
    if (s == "ALLENATORE")          return RuoloStaff::ALLENATORE;
    if (s == "AIUTANTE_ALLENATORE") return RuoloStaff::AIUTANTE_ALLENATORE;
    if (s == "DS")                  return RuoloStaff::DS;
    if (s == "SEGRETERIA")          return RuoloStaff::SEGRETERIA;
    if (s == "ALLENATORE_MINI")     return RuoloStaff::ALLENATORE_MINI;
    return RuoloStaff::ALLENATORE;  //Default esplicito
}

/**
 * @brief Converte enum RuoloStaff in stringa.
 */
std::string Staff::ruoloToString(RuoloStaff r) {
    switch (r) {
        case RuoloStaff::ALLENATORE:          return "ALLENATORE";
        case RuoloStaff::AIUTANTE_ALLENATORE: return "AIUTANTE_ALLENATORE";
        case RuoloStaff::DS:                  return "DS";
        case RuoloStaff::SEGRETERIA:          return "SEGRETERIA";
        case RuoloStaff::ALLENATORE_MINI:     return "ALLENATORE_MINI";
        default:                              return "SCONOSCIUTO";
    }
}

/**
 * @brief Overload operator<< per stampa Staff.
 */
std::ostream& operator<<(std::ostream& os, const Staff& s) {
    os << "Staff: " << s.getNome() << " (" << s.getEta() << " anni), Ruolo: "
       << Staff::ruoloToString(s.getRuolo());
    return os;
}

