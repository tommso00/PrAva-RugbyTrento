#include "Giocatore.h"
#include "StatsGiocatore.h"
// Costruttore
Giocatore::Giocatore(const std::string& nome, 
					 const std::string& cognome,
					 int eta,
                     const std::string& ruolo_,
					 int id_)
    : Persona(nome, cognome, eta),
	  ruolo(ruolo_), 
	  id(id_) 
	  {
	//tocca far così per le stats, viene supportata l'ereditarietà
	int placcaggiRiusciti=0;
	int placcaggiMancati=0;
	
	int metriCorsi=0;
	int lineBreaks=0;
	int difensoriBattuti=0;

	int metePartita=0;
	int meteStagione=0;

	int turnoverPartita=0;
	int turnoverStagione=0;

	int calciPiazzatiSegnatiPartita=0;
	int calciPiazzatiSegnatiStagione=0;
	
	int calciPiazzatiTentatiPartita=0;
	int calciPiazzatiTentatiStagione=0;

	int falliCommessiPartita=0;
	int falliCommessiStagione=0;

	int offload=0;
	double efficaciaRuck=0;

	int minutiGiocati=0;
	int partiteGiocate=0 ;
    

	}
    /*
    oppure posso fare un costruttore parametrico facendo un Giocatore(0param) che inizializza le stats a 0, e setnome/cognome/eta(nome/cognome/eta)
    
	Giocatore::Giocatore(const std::string& nome,
                     const std::string& cognome,
                     int eta,
                     const std::string& ruolo,
                     int id)
    : Giocatore()  
{
    Persona::setNome(nome);
    Persona::setCognome(cognome);
    Persona::setEta(eta);
    this->ruolo = ruolo;
    this->id = id;
}
    
    */

// Getter e setter base
std::string Giocatore::getRuolo() const {
    return ruolo;
}

void Giocatore::setRuolo(const std::string& nuovoRuolo) {
    ruolo = nuovoRuolo;
}

int Giocatore::getId() const {
    return id;
}

void Giocatore::setId(int nuovoId) {
    id = nuovoId;
}

//Statistiche - Getter e Setter
int Giocatore::getPlaccaggiRiusciti() const { return statsPartita.placcaggiRiusciti; }
void Giocatore::setPlaccaggiRiusciti(int v) { statsPartita.placcaggiRiusciti = v; }

int Giocatore::getPlaccaggiMancati() const { return statsPartita.placcaggiMancati; }
void Giocatore::setPlaccaggiMancati(int v) { statsPartita.placcaggiMancati = v; }

int Giocatore::getMetriCorsi() const { return statsPartita.metriCorsi; }
void Giocatore::setMetriCorsi(int v) { statsPartita.metriCorsi = v; }

int Giocatore::getLineBreaks() const { return statsPartita.lineBreaks; }
void Giocatore::setLineBreaks(int v) { statsPartita.lineBreaks = v; }

int Giocatore::getDifensoriBattuti() const { return statsPartita.difensoriBattuti; }
void Giocatore::setDifensoriBattuti(int v) { statsPartita.difensoriBattuti = v; }

int Giocatore::getMetePartita() const { return statsPartita.mete; }
void Giocatore::setMetePartita(int v) { statsPartita.mete = v; }

int Giocatore::getMeteStagione() const { return statsStagione.mete; }
void Giocatore::setMeteStagione(int v) { statsStagione.mete = v; }

int Giocatore::getTurnoverStagione() const { return statsStagione.turnover; }
void Giocatore::setTurnoverStagione(int v) { statsStagione.turnover = v; }

int Giocatore::getTurnoverPartita() const { return statsPartita.turnover; }
void Giocatore::setTurnoverPartita(int v) { statsPartita.turnover = v; }

int Giocatore::getFalliCommessiPartita() const { return statsPartita.falliCommessi; }
void Giocatore::setFalliCommessiPartita(int v) { statsPartita.falliCommessi = v; }

int Giocatore::getFalliCommessiStagione() const { return statsStagione.falliCommessi; }
void Giocatore::setFalliCommessiStagione(int v) { statsStagione.falliCommessi = v; }

int Giocatore::getCalciPiazzatiTentatiPartita() const{return statsPartita.calciPiazzatiTentati; }
void Giocatore::setCalciPiazzatiTentatiPartita(int c){ statsPartita.calciPiazzatiTentati = c; }

int Giocatore::getCalciPiazzatiTentatiStagione()const{return statsStagione.calciPiazzatiSegnati;}
void Giocatore::setCalciPiazzatiTentatiStagione(int c){ statsStagione.calciPiazzatiTentati= c; }

int Giocatore::getCalciPiazzatiSegnatiPartita() const{return statsPartita.calciPiazzatiSegnati; }
void Giocatore::setCalciPiazzatiSegnatiPartita(int c) {statsPartita.calciPiazzatiSegnati = c; }

int Giocatore::getCalciPiazzatiSegnatiStagione() const{return statsStagione.calciPiazzatiSegnati; }
void Giocatore::setCalciPiazzatiSegnatiStagione(int c) {statsStagione.calciPiazzatiSegnati = c; }


int Giocatore::getOffloadPartita() const { return statsPartita.offload; }
int Giocatore::getOffloadStagione() const { return statsStagione.offload; }

void Giocatore::setOffloadPartita(int v) { statsPartita.offload = v; }
void Giocatore::setOffloadStagione(int v) { statsStagione.offload = v; }

double Giocatore::getEfficaciaRuck() const { return statsPartita.efficaciaRuck; }
void Giocatore::setEfficaciaRuck(double v) { statsPartita.efficaciaRuck = v; }

int Giocatore::getMinutiGiocati() const { return statsPartita.minutiGiocati; }
void Giocatore::setMinutiGiocati(int v) { statsPartita.minutiGiocati = v; }

int Giocatore::getPartiteGiocate() const { return statsPartita.partiteGiocate; }
void Giocatore::setPartiteGiocate(int v) { statsPartita.partiteGiocate = v; }

double Giocatore::getPercentualeCalciPiazzatiPartita() const {
    if (statsPartita.calciPiazzatiTentati == 0)
        return 0.0;

    return (100.0 * statsPartita.calciPiazzatiSegnati) / statsPartita.calciPiazzatiTentati;
}

double Giocatore::getPercentualeCalciPiazzatiStagione() const {
    if (statsStagione.calciPiazzatiTentati == 0)
        return 0.0;

    return (100.0 * statsStagione.calciPiazzatiSegnati) / statsStagione.calciPiazzatiTentati;
}


// Operatore di stampa
std::ostream& operator<<(std::ostream& os, const Giocatore& g) {
    os << "Giocatore: " << g.getNome() << " " << g.getCognome()
       << ", Eta': " << g.getEta()
       << ", Ruolo: " << g.ruolo
       << ", ID: " << g.id;
    return os;
}


