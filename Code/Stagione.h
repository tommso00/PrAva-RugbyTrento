#ifndef STAGIONE_H
#define STAGIONE_H

#include <vector>
#include <memory>
#include <ostream>
#include "Squadra.h"
#include "Partita.h"

class Stagione {
private:
    int anno;
    std::vector<std::unique_ptr<Squadra>> squadre;
    std::vector<Partita> partite;

public:
    explicit Stagione(int anno);
    
    Squadra* trovaSquadraPerId(int id);
    
    // ? COPY CONSTRUCTOR - Implementazione PROFONDA
    Stagione(const Stagione& other);
    
    // ? COPY ASSIGNMENT
    Stagione& operator=(const Stagione& other);
    
    // ? MOVE CONSTRUCTOR - Efficiente
    Stagione(Stagione&& other) noexcept;
    
    // ? MOVE ASSIGNMENT - Efficiente  
    Stagione& operator=(Stagione&& other) noexcept;
    
    // Ordina squadre per punteggio e restituisce classifica
    std::vector<const Squadra*> classificaSquadre() const;
    
    // Calcola media statistiche squadre (NUMERIC)
    double mediaPunteggioSquadre() const;
    double mediaMeteTotaliSquadre() const;
    
    // Trova top N squadre (ALGORITHM)
    std::vector<const Squadra*> topSquadre(size_t n) const;
    
    // ? TEMPLATE METAPROGRAMMING - Pointer to member function
	template<typename StatType>
	StatType calcolaMedia(const std::vector<std::unique_ptr<Squadra>>& squadre, 
	                      StatType(Squadra::*getter)() const) const;
	
	template<typename StatType>
	StatType sommaStatistica(const std::vector<std::unique_ptr<Squadra>>& squadre, 
	                         StatType(Squadra::*getter)() const) const;
	
	// Esempi di utilizzo concreti
	double mediaPunteggioTemplate() const;  // Usa template internamente
	int sommaMeteTemplate() const;

    
    ~Stagione() = default;

    const Squadra* getClassificaFinale() const;
    const std::vector<Partita>& getCalendario() const;
    const std::vector<std::unique_ptr<Squadra>>& getSquadre() const;
    const std::vector<Partita>& getPartite() const;
    int getAnno() const;

    void addPartita(const Partita& p);
    void addSquadra(std::unique_ptr<Squadra> s);

    friend std::ostream& operator<<(std::ostream& os, const Stagione& s);
};

#endif

