#ifndef STAFF_H
#define STAFF_H

#include "Persona.h"
#include <string>
#include <iostream>
using namespace std;

enum RuoloStaff {
    ALLENATORE,
    AIUTANTE_ALLENATORE,
    DS,
    SEGRETERIA,
    ALLENATORE_MINI
};

class Staff : public Persona {
protected:
    RuoloStaff ruolo;

public:
    Staff(const string& nome,const string& cognome, int eta, RuoloStaff ruolo);
    ~Staff();

    RuoloStaff getRuolo() const;
    void setRuolo(RuoloStaff nuovoRuolo);

    friend ostream& operator<<(ostream& os, const Staff& s);

    // --- Metodo ausiliario per stampare il ruolo come stringa ---
    static string ruoloToString(RuoloStaff r);
};

#endif


