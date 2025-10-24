#ifndef STAGIONE_H
#define STAGIONE_H

#include <vector>
#include <iostream>
#include <memory> //vedere bene cosa fa' questa lib, potrebbe tornarci utile
#include "Squadra.h"
#include "Partita.h"
using namespace std;

class Stagione {
private:
    int anno;
    vector<unique_ptr<Squadra>> squadre; // Ownership esclusiva: Stagione possiede le squadre
										//si l'ho cercato su chat, l'alternativa era un memory leak
    vector<Partita> partite;			//non so' se far lo stesso anche qui
										//riga 16:Le partite contengono copie di squadre (snapshot)

public:
    Stagione(int anno);
    ~Stagione();
	
    Squadra* getClassificaFinale(); 
    
	// Ritorna riferimento costante per evitare copia
    const vector<Partita>& getCalendario() const;
	
    void addSquadra(unique_ptr<Squadra> s);
    void addPartita(const Partita& p);

    friend ostream& operator<<(ostream& os, const Stagione& s);
};

#endif


