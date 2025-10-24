#include "Staff.h"
using namespace std;

Staff::Staff(const string& nome,const string& cognome ,int eta, RuoloStaff ruolo): Persona(nome, cognome, eta), ruolo(ruolo){}


Staff::~Staff() {
    cout << "Distruttore Staff chiamato per: " << nome << endl;
}

RuoloStaff Staff::getRuolo() const {
    return ruolo;
}

void Staff::setRuolo(RuoloStaff nuovoRuolo) {
    ruolo = nuovoRuolo;
}

string Staff::ruoloToString(RuoloStaff r) {
    switch (r) {
        case ALLENATORE: return "Allenatore";
        case AIUTANTE_ALLENATORE: return "Aiutante Allenatore";
        case DS: return "Direttore Sportivo";
        case SEGRETERIA: return "Segreteria";
        case ALLENATORE_MINI: return "Allenatore Mini";
        default: return "Sconosciuto";
    }
}

ostream& operator<<(ostream& os, const Staff& s) {
    os << "Staff: " << s.getNome() << " (" << s.getEta() << " anni), Ruolo: "
       << Staff::ruoloToString(s.getRuolo());
    return os;
}

/* 
Possibili aggiunte future:
- Metodo per assegnare un membro dello staff ad una squadra.
*/


