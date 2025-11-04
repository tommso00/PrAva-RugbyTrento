#ifndef PERSONA_H
#define PERSONA_H

#include <string>
using namespace std;

class Persona {
protected:
    string nome, cognome;
    int eta;

public:
    Persona(const string& nome, const string& cognome , int eta);
    virtual ~Persona();

    string getNome() const;
    string getCognome() const;
    int getEta() const;
    virtual void stampaInfo() const;
};

#endif


