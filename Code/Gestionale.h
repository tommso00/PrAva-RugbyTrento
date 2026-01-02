#ifndef GESTIONALE_H
#define GESTIONALE_H

#include "Giocatore.h"
#include "Partita.h"
#include "Staff.h"
#include "Squadra.h"
#include "Stagione.h"

#include <thread>
#include <vector>
#include <mutex>
#include <memory>
#include <string>
#include <algorithm>

/**
 * @class Gestionale
 * @brief Classe principale per la gestione completa del sistema rugby.
 * 
 * Gestisce caricamento/salvataggio CSV parallelo, stagioni, squadre, 
 * giocatori, staff e partite con threading e move semantics.
 */
class Gestionale {
private:
    std::vector<std::unique_ptr<Stagione>> stagioni;

    /** @brief Percorsi file CSV per persistenza dati. */
    std::string pathStagioni = "database/stagioni.csv";
    std::string pathSquadre  = "database/squadre.csv";
    std::string pathGiocatori = "database/giocatori.csv";
    std::string pathPartite  = "database/partite.csv";
    std::string pathStaff    = "database/staff.csv";

    /**
     * @brief Divide riga CSV in campi usando delimitatore virgola.
     * @param line Riga CSV da splittare
     * @return Vettore di stringhe con i campi estratti
     */
    std::vector<std::string> splitCSVLine(const std::string& line) const;
    
    /**
     * @brief Cerca stagione per anno nella collezione.
     * @param anno Anno della stagione da trovare
     * @return Puntatore alla Stagione o nullptr
     */
    Stagione* trovaStagione(int anno);

public:
    /** @brief Costruttore di default. */
    Gestionale() = default;
    
    /** @brief Distruttore di default. */
    ~Gestionale() = default;

    /**
     * @brief Menu interattivo per selezione stagione esistente.
     */
    void selezionaStagione();
    
    /**
     * @brief Crea nuova stagione con input utente.
     */
    void creaStagione();
    
    /**
     * @brief Modifica dati di una stagione esistente.
     * @param stagione Riferimento alla stagione da modificare
     */
    void modificaStagione(Stagione& stagione);
    
    /**
     * @brief Carica stagione da file CSV.
     * @param filename Percorso file stagioni.csv
     * @param stagione Anno della stagione da recuperare
     * @return ID della stagione caricata
     */
    int recuperaStagione(const std::string& filename, int stagione);

    // *** GESTIONE STAGIONI ***
    /**
     * @brief Carica tutte le stagioni da file CSV.
     * @param filename Percorso file stagioni.csv
     */
    void fetchStagioni(const std::string& filename);
    
    /**
     * @brief Salva una stagione nel file CSV.
     * @param nuovaStagione Stagione da persistere
     */
    void salvaStagioni(const Stagione& nuovaStagione);

    // *** GESTIONE SQUADRE ***
    /**
     * @brief Crea nuova squadra con input utente (move semantics).
     * @return Unique_ptr alla nuova Squadra creata
     */
    std::unique_ptr<Squadra> aggiungiSquadra();
    
    /**
     * @brief Carica tutte le squadre di una stagione da CSV.
     * @param stagione Stagione contenitore delle squadre
     */
    void fetchSquadre(Stagione& stagione);
    
    /**
     * @brief Salva tutte le squadre della stagione su CSV.
     * @param stagione Stagione contenitore delle squadre
     */
    void salvaSquadre(const Stagione& stagione);
    
    /**
     * @brief Trova massimo ID assegnato alle squadre.
     * @return Massimo ID corrente + 1 per nuovo
     */
    int getMaxSquadraId() const;

    // *** GESTIONE GIOCATORI ***
    /**
     * @brief Carica roster completo squadra da CSV.
     * @param squadra Squadra contenitore dei giocatori
     */
    void fetchGiocatori(Squadra& squadra);
    
    /**
     * @brief Salva roster squadra su file CSV.
     * @param squadra Squadra con giocatori da persistere
     */
    void salvaGiocatori(const Squadra& squadra);

    // *** GESTIONE STAFF ***
    /**
     * @brief Carica staff tecnico squadra da CSV.
     * @param squadra Squadra contenitore dello staff
     */
    void fetchStaff(Squadra& squadra);
    
    /**
     * @brief Salva staff squadra su file CSV.
     * @param squadra Squadra con staff da persistere
     */
    void salvaStaff(const Squadra& squadra);

    // *** GESTIONE PARTITE ***
    /**
     * @brief Carica calendario partite della stagione.
     * @param stagione Stagione contenitore delle partite
     */
    void fetchPartite(Stagione& stagione);
    
    /**
     * @brief Salva calendario partite su CSV.
     * @param stagione Stagione con partite da persistere
     */
    void salvaPartite(const Stagione& stagione);
    
    /**
     * @brief Aggiunge nuova partita al calendario stagione.
     * @param stagione Stagione dove inserire la partita
     */
    void aggiungiPartita(Stagione& stagione);

    /**
     * @brief Salva stagione completa usando thread paralleli.
     * @param stagione Stagione da salvare (squadre/giocatori/staff/partite)
     */
    void salvaParallel(const Stagione& stagione);
    
    /**
     * @brief Restituisce la string senza spazi, punteggiatura o bordi
     * @param stringa str da ripulire/tagliare
     */
    static std::string trim(const std::string& str);
};

#endif

