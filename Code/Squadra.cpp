#include "Squadra.h"
#include <algorithm>

/**
 * @brief Costruttore principale Squadra con reserve ottimizzato.
 */
Squadra::Squadra(int id_, const std::string& nome_, const std::string& indirizzo_)
    : id(id_), nome(nome_), indirizzo(indirizzo_), punteggioClassifica(0),
      possessoPalla(0), territorio(0.0),
      placcaggiTotali(0), metriGuadagnatiTotali(0), meteTotali(0), falliTotali(0),
      mischieVinte(0), mischiePerse(0), toucheVinte(0), touchePerse(0) 
{
    // Pre-alloca spazio per evitare riallocazioni del vector
    giocatori.reserve(25);    // Capacità tipica per una squadra di rugby
    staffTecnico.reserve(5);  // Staff tecnico (allenatore + assistenti)
}

/**
 * @brief Costruttore Move Squadra (efficiente).
 */
Squadra::Squadra(Squadra&& other) noexcept
    : id(other.id),
      nome(std::move(other.nome)), 
      indirizzo(std::move(other.indirizzo)),
      possessoPalla(other.possessoPalla),
      territorio(other.territorio),
      placcaggiTotali(other.placcaggiTotali),
      metriGuadagnatiTotali(other.metriGuadagnatiTotali),
      meteTotali(other.meteTotali),
      falliTotali(other.falliTotali),
      mischieVinte(other.mischieVinte),
      mischiePerse(other.mischiePerse),
      toucheVinte(other.toucheVinte),
      touchePerse(other.touchePerse),
      punteggioClassifica(other.punteggioClassifica),
      giocatori(std::move(other.giocatori)),
      staffTecnico(std::move(other.staffTecnico))
{
    other.id = 0;
    other.nome.clear();
    other.indirizzo.clear();
    other.possessoPalla = 0;
}

/**
 * @brief Costruttore di Copia Squadra (copia profonda).
 */
Squadra::Squadra(const Squadra& other)
    : id(other.id),
      nome(other.nome), 
      indirizzo(other.indirizzo),
      possessoPalla(other.possessoPalla),
      territorio(other.territorio),
      placcaggiTotali(other.placcaggiTotali),
      metriGuadagnatiTotali(other.metriGuadagnatiTotali),
      meteTotali(other.meteTotali),
      falliTotali(other.falliTotali),
      mischieVinte(other.mischieVinte),
      mischiePerse(other.mischiePerse),
      toucheVinte(other.toucheVinte),
      touchePerse(other.touchePerse),
      punteggioClassifica(other.punteggioClassifica),
      giocatori(other.giocatori),
      staffTecnico(other.staffTecnico)
{}

/**
 * @brief Operatore assegnazione copia Squadra.
 */
Squadra& Squadra::operator=(const Squadra& other) {
    if(this != &other) {
        id = other.id;
        nome = other.nome;
        indirizzo = other.indirizzo;
        possessoPalla = other.possessoPalla;
        territorio = other.territorio;
        placcaggiTotali = other.placcaggiTotali;
        metriGuadagnatiTotali = other.metriGuadagnatiTotali;
        meteTotali = other.meteTotali;
        falliTotali = other.falliTotali;
        mischieVinte = other.mischieVinte;
        mischiePerse = other.mischiePerse;
        toucheVinte = other.toucheVinte;
        touchePerse = other.touchePerse;
        punteggioClassifica = other.punteggioClassifica;
        giocatori = other.giocatori;
        staffTecnico = other.staffTecnico;
    }
    return *this;
}

/**
 * @brief Operatore assegnazione Move Squadra.
 */
Squadra& Squadra::operator=(Squadra&& other) noexcept {
    if(this != &other) {
        giocatori.clear();
        staffTecnico.clear();
        
        id = other.id;
        nome = std::move(other.nome);
        indirizzo = std::move(other.indirizzo);
        possessoPalla = other.possessoPalla;
        territorio = other.territorio;
        placcaggiTotali = other.placcaggiTotali;
        metriGuadagnatiTotali = other.metriGuadagnatiTotali;
        meteTotali = other.meteTotali;
        falliTotali = other.falliTotali;
        mischieVinte = other.mischieVinte;
        mischiePerse = other.mischiePerse;
        toucheVinte = other.toucheVinte;
        touchePerse = other.touchePerse;
        punteggioClassifica = other.punteggioClassifica;
        giocatori = std::move(other.giocatori);
        staffTecnico = std::move(other.staffTecnico);
        
        other.id = 0;
        other.nome.clear();
        other.indirizzo.clear();
    }
    return *this;
}

// Getter/Setter info principali

/**
 * @brief Getter nome squadra.
 */
std::string Squadra::getNome() const { return nome; }

/**
 * @brief Setter nome squadra.
 */
void Squadra::setNome(const std::string& n) { nome = n; }

/**
 * @brief Getter indirizzo squadra.
 */
std::string Squadra::getIndirizzo() const { return indirizzo; }

/**
 * @brief Setter indirizzo squadra.
 */
void Squadra::setIndirizzo(const std::string& i) { indirizzo = i; }

/**
 * @brief Getter ID squadra.
 */
int Squadra::getId() const { return id; }

/**
 * @brief Setter ID squadra.
 */
void Squadra::setId(int i) { id = i; }

/**
 * @brief Getter punteggio classifica.
 */
int Squadra::getPunteggio() const { return punteggioClassifica; }

/**
 * @brief Setter punteggio classifica.
 */
void Squadra::setPunteggio(int p) { punteggioClassifica = p; }

// Gestione giocatori

/**
 * @brief Aggiunge giocatore al roster (copia).
 */
void Squadra::addGiocatore(const Giocatore& g) {
    giocatori.push_back(g);
}

/**
 * @brief Rimuove giocatore per ID usando std::remove_if.
 */
void Squadra::removeGiocatore(int idGiocatore) {
    auto it = std::remove_if(giocatori.begin(), giocatori.end(),
        [idGiocatore](const Giocatore& g) { return g.getId() == idGiocatore; });
    if (it != giocatori.end()) {
        giocatori.erase(it, giocatori.end());
    }
}

// *** GESTIONE STAFF CON MOVE SEMANTICS ***

/**
 * @brief Aggiunge staff (versione copy - lvalue).
 */
void Squadra::addStaff(const Staff& membro) {
    staffTecnico.push_back(membro);
}

/**
 * @brief Aggiunge staff (versione move - rvalue, ottimizzato).
 */
void Squadra::addStaff(Staff&& membro) {
    staffTecnico.push_back(std::move(membro));
}

/**
 * @brief Rimuove staff per indice.
 */
void Squadra::removeStaff(size_t index) {
    if (index < staffTecnico.size()) {
        staffTecnico.erase(staffTecnico.begin() + index);
    }
}

/**
 * @brief Svuota completamente roster staff.
 */
void Squadra::clearStaff() {
    staffTecnico.clear();
}

/**
 * @brief Overload operator<< per stampa completa Squadra.
 */
std::ostream& operator<<(std::ostream& os, const Squadra& s) {
    os << "Squadra: " << s.nome << ", Indirizzo: " << s.indirizzo 
       << ", ID: " << s.getId() << "\n";
    os << "Punteggio Classifica: " << s.punteggioClassifica << "\n";
    
    os << "\n=== STAFF TECNICO (" << s.staffTecnico.size() << ") ===\n";
    for (const auto& staff : s.staffTecnico) {
        os << "  " << staff << "\n";
    }
    
    os << "\n=== GIOCATORI (" << s.giocatori.size() << ") ===\n";
    for (const auto& g : s.giocatori) {
        os << "  " << g << "\n";
    }
    return os;
}

// Statistiche di squadra (dati grezzi, non calcoli)

/**
 * @brief Getter possesso palla.
 */
int Squadra::getPossessoPalla() const { return possessoPalla; }

/**
 * @brief Setter possesso palla.
 */
void Squadra::setPossessoPalla(int value) { possessoPalla = value; }

/**
 * @brief Getter territorio.
 */
double Squadra::getTerritorio() const { return territorio; }

/**
 * @brief Setter territorio.
 */
void Squadra::setTerritorio(double value) { territorio = value; }

/**
 * @brief Getter placcaggi totali.
 */
int Squadra::getPlaccaggiTotali() const { return placcaggiTotali; }

/**
 * @brief Setter placcaggi totali.
 */
void Squadra::setPlaccaggiTotali(int value) { placcaggiTotali = value; }

/**
 * @brief Getter metri guadagnati totali.
 */
int Squadra::getMetriGuadagnatiTotali() const { return metriGuadagnatiTotali; }

/**
 * @brief Setter metri guadagnati totali.
 */
void Squadra::setMetriGuadagnatiTotali(int value) { metriGuadagnatiTotali = value; }

/**
 * @brief Getter mete totali.
 */
int Squadra::getMeteTotali() const { return meteTotali; }

/**
 * @brief Setter mete totali.
 */
void Squadra::setMeteTotali(int value) { meteTotali = value; }

/**
 * @brief Getter falli totali.
 */
int Squadra::getFalliTotali() const { return falliTotali; }

/**
 * @brief Setter falli totali.
 */
void Squadra::setFalliTotali(int value) { falliTotali = value; }

/**
 * @brief Getter mischie vinte.
 */
int Squadra::getMischieVinte() const { return mischieVinte; }

/**
 * @brief Setter mischie vinte.
 */
void Squadra::setMischieVinte(int value) { mischieVinte = value; }

/**
 * @brief Getter mischie perse.
 */
int Squadra::getMischiePerse() const { return mischiePerse; }

/**
 * @brief Setter mischie perse.
 */
void Squadra::setMischiePerse(int value) { mischiePerse = value; }

/**
 * @brief Getter touche vinte.
 */
int Squadra::getToucheVinte() const { return toucheVinte; }

/**
 * @brief Setter touche vinte.
 */
void Squadra::setToucheVinte(int value) { toucheVinte = value; }

/**
 * @brief Getter touche perse.
 */
int Squadra::getTouchePerse() const { return touchePerse; }

/**
 * @brief Setter touche perse.
 */
void Squadra::setTouchePerse(int value) { touchePerse = value; }

/**
 * @brief Ricalcola statistiche aggregate da roster giocatori.
 */
void Squadra::aggiornaStatistiche() {
    placcaggiTotali = 0;
    metriGuadagnatiTotali = 0;
    meteTotali = 0;
    falliTotali = 0;

    for (const auto& g : giocatori) {
        placcaggiTotali += g.getPlaccaggi();
        metriGuadagnatiTotali += g.getMetriCorsi();
        meteTotali += g.getMete();
        falliTotali += g.getFalliCommessi();
    }
}

/**
 * @brief Incrementa contatore mete totali.
 */
void Squadra::addMete(int delta) { meteTotali += delta; }

/**
 * @brief Incrementa punteggio classifica.
 */
void Squadra::addPuntiClassifica(int delta) { punteggioClassifica += delta; }

