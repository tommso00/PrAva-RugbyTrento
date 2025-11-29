#include "Partita.h"

// Costruttore
Partita::Partita(int id_, int data_, const Squadra& locali_, const Squadra& ospiti_) 
    : id(id_), data(data_), locali(locali_), ospiti(ospiti_), ptLocali(0), ptOspiti(0) {}

int Partita::getPunteggioPartita() const {
    return ptLocali + ptOspiti;	//dovremmo farlo ritornare una stringa??? ptlocali << ":" << ptospiti?
}

void Partita::setRisultato(int ptLocali_, int ptOspiti_) {
    ptLocali = ptLocali_;
    ptOspiti = ptOspiti_;
}

int Partita::getPuntiOspiti() const {
    return ptOspiti;
}

int Partita::getPuntiLocali() const {
    return ptLocali;
}

const Squadra& Partita::getOspiti() const {
    return ospiti;
}

int Partita::getData() const {
    return data;
}

const Squadra& Partita::getLocali() const {
    return locali;
}

int Partita::getId() const {
    return id;
}

//GETTER STATS
const StatsSquadra& Partita::getStatsLocali() const { return statsLocali; }
const StatsSquadra& Partita::getStatsOspiti() const { return statsOspiti; }

//calcolo automarico statistiche
void Partita::calcolaStatsDaGiocatori(){
	statsLocali = StatsSquadra();

	for(const auto& g : locali.getGiocatori()){
		
		statsLocali.placcaggiTotali += g.getPlaccaggiRiusciti();
		statsLocali.placcaggiTotali += g.getPlaccaggiMancati();
		
		statsLocali.metriGuadagnatiTotali += g.getMetriCorsi();
		
		statsLocali.turnoverVinti += g.getTurnoverPartita();

        statsLocali.calciPiazzatiSegnati += g.getCalciPiazzatiSegnatiPartita();
		statsLocali.calciPiazzatiTentati += g.getCalciPiazzatiTentatiPartita();
        
        statsLocali.meteSegnate += g.getMetePartita();

        statsLocali.falliCommessi += g.getFalliCommessiPartita();
					
	}
	
	statsOspiti = StatsSquadra();
	for (const Giocatore& g : ospiti.getGiocatori()) {

        statsOspiti.placcaggiTotali += g.getPlaccaggiRiusciti();
        statsOspiti.placcaggiTotali += g.getPlaccaggiMancati();

        statsOspiti.metriGuadagnatiTotali += g.getMetriCorsi();

        statsOspiti.turnoverVinti += g.getTurnoverPartita();

        statsOspiti.calciPiazzatiSegnati += g.getCalciPiazzatiSegnatiPartita();

        statsOspiti.meteSegnate += g.getMetePartita();

        statsOspiti.falliCommessi += g.getFalliCommessiPartita();
    }
	
	

}



// Operatore di stampa per mostrare informazioni della partita
std::ostream& operator<<(std::ostream& os, const Partita& p) {
 	os << "Partita ID: " << p.id << ", Data: " << p.data << "\n";
	os << "Squadre: " << p.locali.getNome() << " vs " << p.ospiti.getNome() << "\n";
	os << "Punteggio partita: " << p.ptLocali << ":" << p.ptOspiti;

/* 	os << "Partita ID: " << p.id << ", Data: " << p.data << "\n";
	os << "Locali: " << p.locali << " - Punti: " << p.ptLocali << "\n";
    os << "Ospiti: " << p.ospiti << " - Punti: " << p.ptOspiti;
*/  return os;
}


/*
Secondo me possiamo far ritornare una stringa a getPunteggioPartita() 
del tipo cout << ptLocali << "-" << ptOspiti << endl;
:)

*/

