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
 */
class Gestionale {
private:
    std::vector<std::unique_ptr<Stagione>> stagioni;

    // *** PERCORSI FILE CSV ***
    std::string pathStagioni = "database/stagioni.csv";
    std::string pathSquadre  = "database/squadre.csv";
    std::string pathGiocatori = "database/giocatori.csv";
    std::string pathPartite  = "database/partite.csv";
    std::string pathStaff    = "database/staff.csv";  // NUOVO

    // *** METODI AUSILIARI CSV ***
    std::vector<std::string> splitCSVLine(const std::string& line) const;
    Stagione* trovaStagione(int anno);

public:
    Gestionale() = default;
    ~Gestionale() = default;

    void selezionaStagione();
    void creaStagione();
    void modificaStagione(Stagione& stagione);
    int recuperaStagione(const std::string& filename, int stagione);

    // *** GESTIONE STAGIONI ***
    void fetchStagioni(const std::string& filename);
    void salvaStagioni(const Stagione& nuovaStagione);

    // *** GESTIONE SQUADRE ***
    std::unique_ptr<Squadra> aggiungiSquadra();
    void fetchSquadre(Stagione& stagione);
    void salvaSquadre(const Stagione& stagione);
    int getMaxSquadraId() const;

    // *** GESTIONE GIOCATORI ***
    void fetchGiocatori(Squadra& squadra);
    void salvaGiocatori(const Squadra& squadra);

    // *** GESTIONE STAFF (NUOVO) ***
    void fetchStaff(Squadra& squadra);       ///< Carica staff per una squadra.
    void salvaStaff(const Squadra& squadra); ///< Salva tutto lo staff di una squadra.

    // *** GESTIONE PARTITE ***
    void fetchPartite(Stagione& stagione);
    void salvaPartite(const Stagione& stagione);
    void aggiungiPartita(Stagione& stagione);

    // *** SALVATAGGIO PARALLELO ***
    void salvaParallel(const Stagione& stagione);
};

#endif

