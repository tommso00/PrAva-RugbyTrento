#ifndef GESTIONALE_H
#define GESTIONALE_H

#include "Giocatore.h"
#include "Partita.h"
#include "Staff.h"
#include "Squadra.h"
#include "Stagione.h"

#include <thread>
#include <vector>
#include <future>
#include <mutex>
#include <memory>
#include <string>
#include <algorithm>

class Gestionale {
	
	private:
		std::vector<std::unique_ptr<Stagione>> stagioni;	
		
		//percorsi dei CSV (potremmo mezzo configurarli in un file de setup data.csv) :)
		std::string pathStagioni = "database/stagioni.csv";
    	std::string pathSquadre = "database/squadre.csv";
    	std::string pathGiocatori = "database/giocatori.csv";
    	std::string pathPartite = "database/partite.csv";
		
		// Mutex per sincronizzazione salvataggi
		mutable std::mutex save_mutex;
		
		//metodi ausiliari CSV
		std::vector<std::string> splitCSVLine(const std::string& path) const;
    	void salvaSuFile(const std::string& path, const std::vector<std::string>& righe);
    	std::vector<std::string> leggiDaFile(const std::string& path);
		
	    Stagione* trovaStagione(int anno);
		
	public: 
		Gestionale() = default;
		~Gestionale() = default;
		
		//menu
		void avvia();	
		
		void selezionaStagione();
		void creaStagione();
		void modificaStagione(Stagione& stagione);
		int recuperaStagione(const std::string& filename, int stagione);
		
		//STAGIONI
		void fetchStagioni(const std::string& filename);
		void salvaStagioni(const Stagione& nuovaStagione) const;

		//SQUADRE
		std::unique_ptr<Squadra> aggiungiSquadra();
	    void fetchSquadre(Stagione& stagione);
   		void salvaSquadre(const Stagione& stagione) const;
   		int getMaxSquadraId() const;
   		
   		//GIOCATORI
    	void fetchGiocatori(Squadra& squadra);
    	void salvaGiocatori(const Squadra& squadra) const;
    	
    	//PARTITE
    	void fetchPartite(Stagione& stagione);
    	void salvaPartite(const Stagione& stagione) const;
    	void aggiungiPartita(Stagione& stagione);
    	
    	// SALVATAGGIO PARALLELO
    	void salvaParallel(const Stagione& stagione) const;
		
};

#endif

