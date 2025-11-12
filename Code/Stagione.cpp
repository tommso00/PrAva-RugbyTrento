#include "Stagione.h"
#include <algorithm> // Per ordinamento e ricerca
#include <stdexcept>
#include <memory>

// Costruttore
Stagione::Stagione(int anno_) : anno(anno_) {}

// AddSquadra: prende ownership della squadra (occorre std::move!)
void Stagione::addSquadra(std::unique_ptr<Squadra> s) {
    squadre.push_back(std::move(s));
}

// AddPartita: copia una partita (snapshot nel calendario)
void Stagione::addPartita(const Partita& p) {
    partite.push_back(p);
}

int Stagione::getAnno() const {
    return anno;
}

const std::vector<std::unique_ptr<Squadra>>& Stagione::getSquadre() const {
    return squadre;
}

// Restituisce il calendario (snapshot, solo lettura)
const std::vector<Partita>& Stagione::getCalendario() const {
    return partite;
}

// Ricava la squadra (costante) con il miglior punteggio finale
const Squadra* Stagione::getClassificaFinale() const {
    if (squadre.empty()) return nullptr;
    // Esempio: supponiamo che Squadra abbia il metodo getPunteggio() costante.
    // Cerchiamo la squadra con il punteggio massimo.
    auto cmp = [](const std::unique_ptr<Squadra>& a, const std::unique_ptr<Squadra>& b) {
        return a->getPunteggio() < b->getPunteggio();
    };
    auto it = std::max_element(squadre.begin(), squadre.end(), cmp);
    // Restituiamo solo un puntatore const!
    return it != squadre.end() ? it->get() : nullptr;
}

// Operatore di stampa per la stagione
std::ostream& operator<<(std::ostream& os, const Stagione& s) {
    os << "Stagione " << s.anno << "\n";
    os << "Squadre:\n";
    for (const auto& sq : s.squadre) {
        if(sq) os << *sq << "\n"; // Richiede che Squadra abbia operator<<
    }
    os << "Calendario partite:\n";
    for (const auto& p : s.partite) {
        os << p << "\n"; // Richiede che Partita abbia operator<<
    }
    return os;
}

