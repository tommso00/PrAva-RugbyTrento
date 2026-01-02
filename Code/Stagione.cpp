#include "Stagione.h"
#include <stdexcept>
#include <memory>
#include <iostream>

/**
 * @brief Costruttore principale Stagione.
 */
Stagione::Stagione(int anno_) : anno(anno_) {}

/**
 * @brief Costruttore di Copia Stagione (copia profonda unique_ptr).
 */
Stagione::Stagione(const Stagione& other) 
    : anno(other.anno), partite(other.partite) {
    
    // Copia profonda unique_ptr<Squadra>: usa new manuale
    for(const auto& sq : other.squadre) {
        squadre.push_back(std::unique_ptr<Squadra>(new Squadra(*sq)));
    }
}

/**
 * @brief Operatore assegnazione di copia Stagione.
 */
Stagione& Stagione::operator=(const Stagione& other) {
    if(this != &other) {
        // Cleanup risorse esistenti
        squadre.clear();
        partite.clear();
        
        // Copia profonda nuove risorse
        anno = other.anno;
        partite = other.partite;
        
        for(const auto& sq : other.squadre) {
            squadre.push_back(std::unique_ptr<Squadra>(new Squadra(*sq)));
        }
    }
    return *this;
}

/**
 * @brief Costruttore Move Stagione.
 */
Stagione::Stagione(Stagione&& other) noexcept 
    : anno(other.anno), 
      squadre(std::move(other.squadre)),
      partite(std::move(other.partite)) {
    
    other.anno = 0;
    //std::cout << "Move constructor Stagione(" << anno << ")" << std::endl; //DEBUG implementazioni future
}

/**
 * @brief Operatore di assegnazione Move Stagione.
 */
Stagione& Stagione::operator=(Stagione&& other) noexcept {
    if(this != &other) {
        // Cleanup
        squadre.clear();
        partite.clear();
        
        // Move
        anno = other.anno;
        squadre = std::move(other.squadre);
        partite = std::move(other.partite);
        
        other.anno = 0;
    }
    //std::cout << "Move assignment Stagione(" << anno << ")" << std::endl; //DEBUG implementazioni future
    return *this;
}

// Metodi pubblici

/**
 * @brief Aggiunge squadra alla stagione (move semantics).
 */
void Stagione::addSquadra(std::unique_ptr<Squadra> s) {
    squadre.push_back(std::move(s));
}

/**
 * @brief Aggiunge partita al calendario.
 */
void Stagione::addPartita(const Partita& p) {
    partite.push_back(p);
}

/**
 * @brief Anno della stagione.
 */
int Stagione::getAnno() const {
    return anno;
}

/**
 * @brief Vettore squadre (costante).
 */
const std::vector<std::unique_ptr<Squadra>>& Stagione::getSquadre() const {
    return squadre;
}

/**
 * @brief Calendario partite (costante).
 */
const std::vector<Partita>& Stagione::getCalendario() const {
    return partite;
}


/**
 * @brief Overload operator<< per stampa completa Stagione.
 */
std::ostream& operator<<(std::ostream& os, const Stagione& s) {
    os << "Stagione " << s.anno << "\n";
    os << "Squadre:\n";
    for (const auto& sq : s.squadre) {
        if(sq) os << *sq << "\n";
    }
    os << "Calendario partite:\n";
    for (const auto& p : s.partite) {
        os << p << "\n";
    }
    return os;
}

/**
 * @brief Cerca squadra per ID.
 */
Squadra* Stagione::trovaSquadraPerId(int id){
	for (auto& sqPtr : squadre){
		if(sqPtr && sqPtr->getId()== id){
			return sqPtr.get();
		}
	}
	return nullptr;
}

