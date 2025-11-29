#ifndef STATSGIOCATORE_H
#define STATSGIOCATORE_H

struct StatsGiocatore {

    int placcaggiRiusciti = 0;
    int placcaggiMancati = 0;

    int metriCorsi = 0;
    int lineBreaks = 0;
    int difensoriBattuti = 0;

    int mete = 0;

    int turnover = 0;

    int calciPiazzatiSegnati = 0;
    int calciPiazzatiTentati = 0;

    int falliCommessi = 0;

    int offload = 0;
    double efficaciaRuck = 0.0;

    int minutiGiocati = 0;
    int partiteGiocate = 0;

    double percentualeCalciPiazzati() const{
		if(calciPiazzatiTentati == 0) return 0.0;
    	return (double)calciPiazzatiSegnati / calciPiazzatiTentati * 100.0;
	}
	
};

#endif

