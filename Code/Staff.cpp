#include "Staff.h"
using namespace std;

// Nuovi membri (id da assegnare al salvataggio)
Staff::Staff(const std::string& nome,
             const std::string& cognome,
             int eta,
             RuoloStaff ruolo)
    : Persona(nome, cognome, eta),
      id(0),
      ruolo(ruolo) {}          // <-- QUI

// Membri letti dal CSV (id noto)
Staff::Staff(int id,
             const std::string& nome,
             const std::string& cognome,
             int eta,
             RuoloStaff ruolo)
    : Persona(nome, cognome, eta),
      id(id),
      ruolo(ruolo) {}          // <-- E QUI

int Staff::getId() const { return id; }
void Staff::setId(int nuovoId) { id = nuovoId; }

RuoloStaff Staff::getRuolo() const { return ruolo; }
void Staff::setRuolo(RuoloStaff nuovoRuolo) { ruolo = nuovoRuolo; }

RuoloStaff Staff::stringToRuolo(const std::string& s) {
    if (s == "ALLENATORE")          return ALLENATORE;
    if (s == "AIUTANTE_ALLENATORE") return AIUTANTE_ALLENATORE;
    if (s == "DS")                  return DS;
    if (s == "SEGRETERIA")          return SEGRETERIA;
    if (s == "ALLENATORE_MINI")     return ALLENATORE_MINI;
    return ALLENATORE;
}

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

std::ostream& operator<<(std::ostream& os, const Staff& s) {
    os << "Staff: " << s.getNome() << " (" << s.getEta() << " anni), Ruolo: "
       << Staff::ruoloToString(s.getRuolo());
    return os;
}

