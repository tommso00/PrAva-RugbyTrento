#ifndef STAGIONE_H
#define STAGIONE_H

#include <vector>
#include <memory>
#include <ostream>
#include "Squadra.h"
#include "Partita.h"

// La classe Stagione possiede le squadre tramite unique_ptr, evitando memory leak.
// Le partite sono snapshot e vengono memorizzate per valore.
class Stagione {
private:
    int anno;
    std::vector<std::unique_ptr<Squadra>> squadre; // Ownership esclusiva sulle squadre
    std::vector<Partita> partite; // Snapshot: le partite contengono copie delle squadre
	

public:
    explicit Stagione(int anno);

    // Il distruttore di default gestisce correttamente unique_ptr e vector!
    ~Stagione() = default;

    // Restituisce la squadra vincente in classifica, non trasferisce la proprietà.
    // Modifica il tipo: const Squadra* (sola lettura, non ownership).
    const Squadra* getClassificaFinale() const;

    // Calendario delle partite (solo lettura)
    const std::vector<Partita>& getCalendario() const;
	const std::vector<std::unique_ptr<Squadra>>& getSquadre() const;
	const std::vector<Partita>& getPartite() const;

	int getAnno() const;
	
    // Inserisce una partita per valore (snapshot).
    void addPartita(const Partita& p);
    void addSquadra(std::unique_ptr<Squadra> s);

    // Stampa la stagione
    friend std::ostream& operator<<(std::ostream& os, const Stagione& s);
};

#endif

