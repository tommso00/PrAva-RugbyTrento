#ifndef GESTIONALE_H
#define GESTIONALE_H

#include "Giocatore.h"
#include "Partita.h"
#include "Staff.h"
#include "Squadra.h"
#include "Stagione.h"

#include <vector>
#include <memory>
#include <string>


class Gestionale {
	
	private:
		std::vector<std::unique_ptr<Stagione>> stagioni;	
		
		//percorsi dei CSV (potremmo mezzo configurarli in un file de setup data.csv) :)
		std::string pathStagioni = "stagioni.csv";
    	std::string pathSquadre = "squadre.csv";
    	std::string pathGiocatori = "giocatori.csv";
    	std::string pathPartite = "partite.csv";
		
		//metodi ausiliari CSV
		std::vector<std::string> splitCSVLine(const std::string& path);
    	void salvaSuFile(const std::string& path, const std::vector<std::string>& righe);
    	std::vector<std::string> leggiDaFile(const std::string& path);
		
	    //Stagione* selezionaStagione(); // seleziona stagione già caricata :)
	    Stagione* trovaStagione(int anno);

		
	public: 
		Gestionale() = default;
		~Gestionale() = default;
		
		//menu
		void avvia();	
		
		void selezionaStagione();
		void creaStagione();
		void caricaStagione(const std::string& filename, int stagione);
		
		//metodi CSV I/O
		void fetchStagioni(const std::string& filename); //legge stagioni e relative squadre/partite dal CSV :)
		void salvaStagioni()const; //sovrascrive i CSV con i dati correnti in memoria

	
	    void fetchSquadre(Stagione& stagione);
   		void salvaSquadre(const Stagione& stagione)const;

    	void fetchGiocatori(Squadra& squadra);
    	void salvaGiocatori(const Squadra& squadra)const;

    	void fetchPartite(Stagione& stagione);
    	void salvaPartite(const Stagione& stagione)const;
		
};





#endif

