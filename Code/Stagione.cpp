#include "Stagione.h"
#include <algorithm> // Per ordinamento e ricerca
#include <stdexcept>
#include <memory>
#include <iostream>  // ? AGGIUNTO per std::cout
#include <numeric> 

/**
 * @brief Costruttore principale Stagione.
 */
Stagione::Stagione(int anno_) : anno(anno_) {}

/**
 * @brief Copy constructor Stagione (C++11 deep copy unique_ptr).
 */
Stagione::Stagione(const Stagione& other) 
    : anno(other.anno), partite(other.partite) {
    
    // Deep copy unique_ptr<Squadra>: usa new manuale
    for(const auto& sq : other.squadre) {
        squadre.push_back(std::unique_ptr<Squadra>(new Squadra(*sq)));
    }
    std::cout << "Copy constructor Stagione(" << anno << ")" << std::endl;
}

/**
 * @brief Copy assignment operator Stagione (C++11).
 */
Stagione& Stagione::operator=(const Stagione& other) {
    if(this != &other) {
        // Cleanup risorse esistenti
        squadre.clear();
        partite.clear();
        
        // Deep copy nuove risorse
        anno = other.anno;
        partite = other.partite;
        
        for(const auto& sq : other.squadre) {
            squadre.push_back(std::unique_ptr<Squadra>(new Squadra(*sq)));
        }
    }
    std::cout << "Copy assignment Stagione(" << anno << ")" << std::endl;
    return *this;
}

/**
 * @brief Move constructor Stagione (efficiente).
 */
Stagione::Stagione(Stagione&& other) noexcept 
    : anno(other.anno), 
      squadre(std::move(other.squadre)),
      partite(std::move(other.partite)) {
    
    other.anno = 0;
    std::cout << "Move constructor Stagione(" << anno << ")" << std::endl;
}

/**
 * @brief Move assignment operator Stagione.
 */
Stagione& Stagione::operator=(Stagione&& other) noexcept {
    if(this != &other) {
        // Cleanup
        squadre.clear();
        partite.clear();
        
        // Move risorse
        anno = other.anno;
        squadre = std::move(other.squadre);
        partite = std::move(other.partite);
        
        other.anno = 0;
    }
    std::cout << "Move assignment Stagione(" << anno << ")" << std::endl;
    return *this;
}

/**
 * @brief Template media statistiche (pointer-to-member).
 */
template<typename StatType>
StatType Stagione::calcolaMedia(const std::vector<std::unique_ptr<Squadra>>& squadre, 
                                StatType(Squadra::*getter)() const) const {
    if(squadre.empty()) return StatType{};
    
    StatType somma = StatType{};
    size_t count = 0;
    
    for(const auto& sq : squadre) {
        somma += (sq.get()->*getter)();  // ? TEMPLATE MAGIC: pointer-to-member!
        ++count;
    }
    
    return somma / static_cast<StatType>(count);
}

/**
 * @brief Template somma statistiche (pointer-to-member).
 */
template<typename StatType>
StatType Stagione::sommaStatistica(const std::vector<std::unique_ptr<Squadra>>& squadre, 
                                   StatType(Squadra::*getter)() const) const {
    StatType totale = StatType{};
    for(const auto& sq : squadre) {
        totale += (sq.get()->*getter)();
    }
    return totale;
}

/**
 * @brief Media punteggio squadre (template instantiation).
 */
double Stagione::mediaPunteggioTemplate() const {
    return calcolaMedia(getSquadre(), &Squadra::getPunteggio);
}

/**
 * @brief Somma totale mete squadre (template instantiation).
 */
int Stagione::sommaMeteTemplate() const {
    return sommaStatistica(getSquadre(), &Squadra::getMeteTotali);
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
 * @brief Squadra vincitrice classifica finale (max punteggio).
 */
const Squadra* Stagione::getClassificaFinale() const {
    if (squadre.empty()) return nullptr;
    
    auto cmp = [](const std::unique_ptr<Squadra>& a, const std::unique_ptr<Squadra>& b) {
        return a->getPunteggio() < b->getPunteggio();
    };
    auto it = std::max_element(squadre.begin(), squadre.end(), cmp);
    return it != squadre.end() ? it->get() : nullptr;
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
 * @brief Classifica squadre (std::sort + lambda descending).
 */
std::vector<const Squadra*> Stagione::classificaSquadre() const {
    std::vector<const Squadra*> classifica;
    for(const auto& sq : squadre) {
        classifica.push_back(sq.get());
    }
    
    // ORDINA per punteggio DESCENDENTE (STL algorithm + lambda)
    std::sort(classifica.begin(), classifica.end(), 
        [](const Squadra* a, const Squadra* b) {
            return a->getPunteggio() > b->getPunteggio();
        });
    
    return classifica;
}

/**
 * @brief Media punteggio squadre (std::accumulate).
 */
double Stagione::mediaPunteggioSquadre() const {
    if(squadre.empty()) return 0.0;
    
    // Crea vector punteggi
    std::vector<int> punteggi;
    for(const auto& sq : squadre) {
        punteggi.push_back(sq->getPunteggio());
    }
    
    // NUMERIC: std::accumulate
    int somma = std::accumulate(punteggi.begin(), punteggi.end(), 0);
    return static_cast<double>(somma) / punteggi.size();
}

/**
 * @brief Media mete totali squadre (std::accumulate).
 */
double Stagione::mediaMeteTotaliSquadre() const {
    if(squadre.empty()) return 0.0;
    
    std::vector<int> mete;
    for(const auto& sq : squadre) {
        mete.push_back(sq->getMeteTotali());
    }
    
    int somma = std::accumulate(mete.begin(), mete.end(), 0);
    return static_cast<double>(somma) / mete.size();
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

/**
 * @brief Top N squadre (std::partial_sort ottimizzato).
 */
std::vector<const Squadra*> Stagione::topSquadre(size_t n) const {
    std::vector<const Squadra*> top;
    for(const auto& sq : squadre) {
        top.push_back(sq.get());
    }
    
    if(top.size() > n) {
        // partial_sort: più efficiente di sort completo
        std::partial_sort(top.begin(), top.begin() + n, top.end(),
            [](const Squadra* a, const Squadra* b) {
                return a->getPunteggio() > b->getPunteggio();
            });
        top.resize(n);  
    }
    
    return top;
}

