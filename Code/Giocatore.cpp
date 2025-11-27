#include "Giocatore.h"

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
int Giocatore::getPlaccaggiRiusciti() const { return placcaggiRiusciti; }
void Giocatore::setPlaccaggiRiusciti(int v) { placcaggiRiusciti = v; }

int Giocatore::getPlaccaggiMancati() const { return placcaggiMancati; }
void Giocatore::setPlaccaggiMancati(int v) { placcaggiMancati = v; }

int Giocatore::getMetriCorsi() const { return metriCorsi; }
void Giocatore::setMetriCorsi(int v) { metriCorsi = v; }

int Giocatore::getLineBreaks() const { return lineBreaks; }
void Giocatore::setLineBreaks(int v) { lineBreaks = v; }

int Giocatore::getDifensoriBattuti() const { return difensoriBattuti; }
void Giocatore::setDifensoriBattuti(int v) { difensoriBattuti = v; }

int Giocatore::getMetePartita() const { return metePartita; }
void Giocatore::setMetePartita(int v) { metePartita = v; }

int Giocatore::getMeteStagione() const { return meteStagione; }
void Giocatore::setMeteStagione(int v) { meteStagione = v; }

int Giocatore::getTurnoverStagione() const { return turnoverStagione; }
void Giocatore::setTurnoverStagione(int v) { turnoverStagione = v; }

int Giocatore::getTurnoverPartita() const { return turnoverPartita; }
void Giocatore::setTurnoverPartita(int v) { turnoverPartita = v; }

int Giocatore::getFalliCommessiPartita() const { return falliCommessiPartita; }
void Giocatore::setFalliCommessiPartita(int v) { falliCommessiPartita = v; }

int Giocatore::getFalliCommessiStagione() const { return falliCommessiStagione; }
void Giocatore::setFalliCommessiStagione(int v) { falliCommessiStagione = v; }

int Giocatore::getOffload() const { return offload; }
void Giocatore::setOffload(int v) { offload = v; }

double Giocatore::getEfficaciaRuck() const { return efficaciaRuck; }
void Giocatore::setEfficaciaRuck(double v) { efficaciaRuck = v; }

int Giocatore::getMinutiGiocati() const { return minutiGiocati; }
void Giocatore::setMinutiGiocati(int v) { minutiGiocati = v; }

int Giocatore::getPartiteGiocate() const { return partiteGiocate; }
void Giocatore::setPartiteGiocate(int v) { partiteGiocate = v; }

double Giocatore::getPercentualeCalciPiazzatiPartita() const {
    if (calciPiazzatiTentatiPartita == 0)
        return 0.0;

    return (100.0 * calciPiazzatiSegnatiPartita) / calciPiazzatiTentatiPartita;
}

double Giocatore::getPercentualeCalciPiazzatiStagione() const {
    if (calciPiazzatiTentatiStagione == 0)
        return 0.0;

    return (100.0 * calciPiazzatiSegnatiStagione) / calciPiazzatiTentatiStagione;
}


// Operatore di stampa
std::ostream& operator<<(std::ostream& os, const Giocatore& g) {
    os << "Giocatore: " << g.getNome() << " " << g.getCognome()
       << ", Eta': " << g.getEta()
       << ", Ruolo: " << g.ruolo
       << ", ID: " << g.id;
    return os;
}


