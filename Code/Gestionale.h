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
		Stagione* selezionaStagione();// DA RIFARE: la lista stagioni la prendi dal DB (file .csv)
		
	public: 
		Gestionale() = default;
		~Gestionale() = default;
		void avvia();		

		void creaStagione();
	    void addSquadraToStagione();
	    void addPartitaToStagione();
	    void addGiocatoreToStagione();
		//void fetchStagioni(); //Va nel file .csv e prende lista stagioni per stamparla 
		//void modificaStagione(); // abbastanza "simile" a creaStagione(): menu con scelte per usare i metodi gia creati
		 
	    
		
};





#endif

