#include "Staff.h"
using namespace std;

/**
 * @brief Costruttore Staff senza ID (da assegnare al salvataggio).
 */
Staff::Staff(const std::string& nome,
             const std::string& cognome,
             int eta,
             RuoloStaff ruolo)
    : Persona(nome, cognome, eta),
      id(0),
      ruolo(ruolo) {}          // <-- QUI

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
      ruolo(ruolo) {}          // <-- E QUI

/**
 * @brief Restituisce ID univoco staff.
 */
int Staff::getId() const { return id; }

/**
 * @brief Imposta ID univoco staff.
 */
void Staff::setId(int nuovoId) { id = nuovoId; }

/**
 * @brief Restituisce ruolo professionale.
 */
RuoloStaff Staff::getRuolo() const { return ruolo; }

/**
 * @brief Imposta ruolo professionale.
 */
void Staff::setRuolo(RuoloStaff nuovoRuolo) { ruolo = nuovoRuolo; }

/**
 * @brief Converte stringa in enum RuoloStaff.
 */
RuoloStaff Staff::stringToRuolo(const std::string& s) {
    if (s == "ALLENATORE")          return ALLENATORE;
    if (s == "AIUTANTE_ALLENATORE") return AIUTANTE_ALLENATORE;
    if (s == "DS")                  return DS;
    if (s == "SEGRETERIA")          return SEGRETERIA;
    if (s == "ALLENATORE_MINI")     return ALLENATORE_MINI;
    return ALLENATORE;
}

/**
 * @brief Converte enum RuoloStaff in stringa.
 */
std::string Staff::ruoloToString(RuoloStaff r) {
    switch (r) {
        case ALLENATORE:          return "ALLENATORE";
        case AIUTANTE_ALLENATORE: return "AIUTANTE_ALLENATORE";
        case DS:                  return "DS";
        case SEGRETERIA:          return "SEGRETERIA";
        case ALLENATORE_MINI:     return "ALLENATORE_MINI";
        default:                  return "SCONOSCIUTO";
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

