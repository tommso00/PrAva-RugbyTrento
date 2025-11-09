#ifndef GESTIONALE_H
#define GESTIONALE_H

#include "Giocatore.h"
#include "Partita.h"
#include "Staff.h"
#include "Squadra.h"
#include "Stagione.h"

#include <vector>
#include <memory>


class Gestionale {
	
	private:
		std::vector<std::unique_ptr<Stagione>> stagioni;	
		Stagione* selezionaStagione();
		
	public: 
		Gestionale() = default;
		~Gestionale() = default;
		void avvia();		

		void creaStagione();
	    void addSquadraToStagione();
	    void addPartitaToStagione();
	    void addGiocatoreToStagione();
		
};





#endif

