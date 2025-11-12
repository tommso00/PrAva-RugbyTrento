#ifndef PARTITA_H
#define PARTITA_H

#include "Squadra.h"
#include <iostream>

// Non usare "using namespace std;" nei file header
class Partita {
private:
    int id, data;
    Squadra locali;
    Squadra ospiti;
    int ptLocali, ptOspiti;

public:
    Partita(int id, int data, const Squadra& locali, const Squadra& ospiti);

    // Il distruttore di default è sufficiente: nessun puntatore o risorsa gestita manualmente
    ~Partita() = default;

	// GETTER aggiunti
    int getId() const;
    int getData() const;
    const Squadra& getLocali() const;
    const Squadra& getOspiti() const;
    int getPuntiLocali() const;
    int getPuntiOspiti() const;
    int getPunteggioPartita() const; 

    void setRisultato(int ptLocali, int ptOspiti);

    // Serve lo scope std:: per ostream, non "using namespace std;"
    friend std::ostream& operator<<(std::ostream& os, const Partita& p);
};

#endif

