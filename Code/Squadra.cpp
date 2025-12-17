#include "Squadra.h"
#include <algorithm>

// Costruttore con RESERVE per ottimizzazione
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

// MOVE CONSTRUCTOR
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

// COPY CONSTRUCTOR
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

// COPY ASSIGNMENT
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

// MOVE ASSIGNMENT
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
std::string Squadra::getNome() const { return nome; }
void Squadra::setNome(const std::string& n) { nome = n; }
std::string Squadra::getIndirizzo() const { return indirizzo; }
void Squadra::setIndirizzo(const std::string& i) { indirizzo = i; }
int Squadra::getId() const { return id; }
void Squadra::setId(int i) { id = i; }
int Squadra::getPunteggio() const { return punteggioClassifica; }
void Squadra::setPunteggio(int p) { punteggioClassifica = p; }

// Gestione giocatori
void Squadra::addGiocatore(const Giocatore& g) {
    giocatori.push_back(g);
}

void Squadra::removeGiocatore(int idGiocatore) {
    auto it = std::remove_if(giocatori.begin(), giocatori.end(),
        [idGiocatore](const Giocatore& g) { return g.getId() == idGiocatore; });
    if (it != giocatori.end()) {
        giocatori.erase(it, giocatori.end());
    }
}

// *** GESTIONE STAFF CON MOVE SEMANTICS ***

// Versione COPY (lvalue)
void Squadra::addStaff(const Staff& membro) {
    staffTecnico.push_back(membro);
}

// Versione MOVE (rvalue) - OTTIMIZZATO
void Squadra::addStaff(Staff&& membro) {
    staffTecnico.push_back(std::move(membro));
}

void Squadra::removeStaff(size_t index) {
    if (index < staffTecnico.size()) {
        staffTecnico.erase(staffTecnico.begin() + index);
    }
}

void Squadra::clearStaff() {
    staffTecnico.clear();
}

// Operatore di stampa
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
int Squadra::getPossessoPalla() const { return possessoPalla; }
void Squadra::setPossessoPalla(int value) { possessoPalla = value; }
double Squadra::getTerritorio() const { return territorio; }
void Squadra::setTerritorio(double value) { territorio = value; }
int Squadra::getPlaccaggiTotali() const { return placcaggiTotali; }
void Squadra::setPlaccaggiTotali(int value) { placcaggiTotali = value; }
int Squadra::getMetriGuadagnatiTotali() const { return metriGuadagnatiTotali; }
void Squadra::setMetriGuadagnatiTotali(int value) { metriGuadagnatiTotali = value; }
int Squadra::getMeteTotali() const { return meteTotali; }
void Squadra::setMeteTotali(int value) { meteTotali = value; }
int Squadra::getFalliTotali() const { return falliTotali; }
void Squadra::setFalliTotali(int value) { falliTotali = value; }
int Squadra::getMischieVinte() const { return mischieVinte; }
void Squadra::setMischieVinte(int value) { mischieVinte = value; }
int Squadra::getMischiePerse() const { return mischiePerse; }
void Squadra::setMischiePerse(int value) { mischiePerse = value; }
int Squadra::getToucheVinte() const { return toucheVinte; }
void Squadra::setToucheVinte(int value) { toucheVinte = value; }
int Squadra::getTouchePerse() const { return touchePerse; }
void Squadra::setTouchePerse(int value) { touchePerse = value; }

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

void Squadra::addMete(int delta) { meteTotali += delta; }
void Squadra::addPuntiClassifica(int delta) { punteggioClassifica += delta; }

