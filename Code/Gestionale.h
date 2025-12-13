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

/**
 * @class Gestionale
 * @brief Classe principale per la gestione completa del sistema rugby.
 * 
 * CENTRALIZZA tutte le operazioni del software:
 * - Persistenza dati su file CSV
 * - Gestione multi-threaded dei salvataggi
 * - Interfaccia menu interattiva
 * - Caricamento/salvataggio stagioni, squadre, giocatori, partite
 * 
 * Implementa il pattern **Facade** per semplificare l'accesso alle funzionalità.
 */
class Gestionale {
private:
    std::vector<std::unique_ptr<Stagione>> stagioni; ///< Tutte le stagioni gestite dal sistema.

    // *** PERCORSI FILE CSV (CONFIGURABILI) ***
    std::string pathStagioni = "database/stagioni.csv";    ///< File per le stagioni.
    std::string pathSquadre  = "database/squadre.csv";     ///< File per le squadre.
    std::string pathGiocatori = "database/giocatori.csv";  ///< File per i giocatori.
    std::string pathPartite  = "database/partite.csv";     ///< File per le partite.

    // *** SYNCHRONIZATION PRIMITIVES (THREAD-SAFE) ***
    mutable std::mutex save_mutex;       ///< Mutex globale per salvataggi concorrenti.
    std::mutex mutex_stagioni;           ///< Mutex specifico per accesso alle stagioni.
    std::mutex mutex_squadre;            ///< Mutex specifico per accesso alle squadre.
    std::mutex mutex_giocatori;          ///< Mutex specifico per accesso ai giocatori.
    std::mutex mutex_partite;            ///< Mutex specifico per accesso alle partite.
    std::mutex mutex_cout;               ///< Mutex per output console thread-safe.

    // *** METODI AUSILIARI CSV ***
    /**
     * @brief Divide una riga CSV in campi individuali.
     * @param path Percorso del file (per debug).
     * @return Vettore di stringhe contenenti i campi.
     */
    std::vector<std::string> splitCSVLine(const std::string& path) const;

    /**
     * @brief Salva un vettore di righe CSV su file.
     * @param path Percorso del file di destinazione.
     * @param righe Righe CSV da scrivere.
     */
    void salvaSuFile(const std::string& path, const std::vector<std::string>& righe);

    /**
     * @brief Legge tutte le righe da un file CSV.
     * @param path Percorso del file da leggere.
     * @return Vettore di stringhe contenenti tutte le righe.
     */
    std::vector<std::string> leggiDaFile(const std::string& path);

    /**
     * @brief Cerca una stagione specifica per anno.
     * @param anno Anno della stagione da trovare.
     * @return Puntatore alla stagione, nullptr se non trovata.
     */
    Stagione* trovaStagione(int anno);

public:
    /**
     * @brief Costruttore di default.
     * Inizializza i percorsi file e i mutex.
     */
    Gestionale() = default;

    /**
     * @brief Distruttore di default.
     * std::unique_ptr gestisce automaticamente la memoria.
     */
    ~Gestionale() = default;

    // *** INTERFACCIA UTENTE (MENU PRINCIPALE) ***
    /**
     * @brief Avvia l'interfaccia interattiva a menu.
     * Ciclo principale del programma con scelta delle operazioni.
     */
    void avvia();

    void selezionaStagione();                    ///< Seleziona una stagione esistente.
    void creaStagione();                         ///< Crea una nuova stagione.
    void modificaStagione(Stagione& stagione);   ///< Modifica una stagione esistente.
    int recuperaStagione(const std::string& filename, int stagione); ///< Carica da file.

    // *** GESTIONE STAGIONI ***
    /**
     * @brief Carica tutte le stagioni da file CSV.
     * @param filename Percorso del file stagioni.csv.
     */
    void fetchStagioni(const std::string& filename);

    /**
     * @brief Salva una stagione su file CSV.
     * @param nuovaStagione Stagione da persistere.
     */
    void salvaStagioni(const Stagione& nuovaStagione);

    // *** GESTIONE SQUADRE ***
    /**
     * @brief Crea e restituisce una nuova squadra.
     * @return unique_ptr alla nuova squadra creata.
     */
    std::unique_ptr<Squadra> aggiungiSquadra();

    void fetchSquadre(Stagione& stagione);       ///< Carica squadre per una stagione.
    void salvaSquadre(const Stagione& stagione); ///< Salva tutte le squadre di una stagione.
    int getMaxSquadraId() const;                 ///< Trova il massimo ID squadra corrente.

    // *** GESTIONE GIOCATORI ***
    void fetchGiocatori(Squadra& squadra);       ///< Carica giocatori per una squadra.
    void salvaGiocatori(const Squadra& squadra); ///< Salva tutti i giocatori di una squadra.

    // *** GESTIONE PARTITE ***
    void fetchPartite(Stagione& stagione);       ///< Carica partite per una stagione.
    void salvaPartite(const Stagione& stagione); ///< Salva tutte le partite di una stagione.
    void aggiungiPartita(Stagione& stagione);    ///< Crea e aggiunge una nuova partita.

    // *** SALVATAGGIO PARALLELO (MULTI-THREAD) ***
    /**
     * @brief Salva stagione, squadre, giocatori e partite CONCORRENTE.
     * 
     * Utilizza std::async e std::future per parallelizzare i salvataggi
     * su file differenti, migliorando drasticamente le performance.
     * 
     * @param stagione Stagione completa da salvare.
     */
    void salvaParallel(const Stagione& stagione);
};

#endif

