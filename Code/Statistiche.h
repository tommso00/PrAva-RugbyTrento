#ifndef STATISTICHE_H
#define STATISTICHE_H

#include "Squadra.h"
#include "Stagione.h"
#include "Giocatore.h"
#include <vector>
#include <string>
#include <map>

/**
 * @class Statistiche
 * @brief Classe utility per calcolare statistiche avanzate usando algoritmi STL.
 * 
 * Dimostra l'uso di:
 * - std::max_element, std::min_element (Lezione 7)
 * - std::count_if, std::copy_if (Lezione 7)
 * - std::sort, std::partial_sort, std::nth_element (Lezione 7)
 * - std::accumulate (Lezione 7)
 * - Lambda expressions (Lezione 12)
 * - Pointer-to-member functions (Lezione 11)
 */
class Statistiche {
public:
    // ==================== STATISTICHE GIOCATORI ====================
    
    /**
     * @brief Trova il giocatore con più placcaggi usando std::max_element.
     */
    static const Giocatore* getMigliorPlaccaggitore(const Squadra& squadra);
    
    /**
     * @brief Trova il capocannoniere (più mete) usando std::max_element.
     */
    static const Giocatore* getCapocannoniere(const Squadra& squadra);
    
    /**
     * @brief Trova il giocatore con più metri percorsi.
     */
    static const Giocatore* getMigliorCorridore(const Squadra& squadra);
    
    /**
     * @brief Conta giocatori per ruolo specifico usando std::count_if.
     */
    static int contaGiocatoriPerRuolo(const Squadra& squadra, const std::string& ruolo);
    
    /**
     * @brief Filtra giocatori con almeno N mete usando std::copy_if.
     */
    static std::vector<Giocatore> giocatoriConMeteSopra(const Squadra& squadra, int soglia);
    
    /**
     * @brief Filtra giocatori con almeno N placcaggi.
     */
    static std::vector<Giocatore> giocatoriConPlaccaggiSopra(const Squadra& squadra, int soglia);
    
    /**
     * @brief Calcola la media mete per giocatore.
     */
    static double mediaMetePerGiocatore(const Squadra& squadra);
    
    /**
     * @brief Calcola la media placcaggi per giocatore.
     */
    static double mediaPlaccaggiPerGiocatore(const Squadra& squadra);
    
    /**
     * @brief Distribuzione giocatori per tutti i ruoli.
     */
    static std::map<std::string, int> distribuzioneRuoli(const Squadra& squadra);
    
    /**
     * @brief Stampa report statistico completo della squadra.
     */
    static void stampaReportSquadra(const Squadra& squadra);
    
    // ==================== STATISTICHE STAGIONE ====================
    
    /**
     * @brief Genera classifica completa ordinata per punteggio usando std::sort.
     */
    static std::vector<Squadra*> classificaCompleta(const Stagione& stagione);
    
    /**
     * @brief Trova le top N squadre usando std::partial_sort.
     */
    static std::vector<Squadra*> topNSquadre(const Stagione& stagione, size_t n);
    
    /**
     * @brief Trova il mediano della classifica usando std::nth_element.
     */
    static Squadra* squadraMediana(const Stagione& stagione);
    
    /**
     * @brief Confronta due squadre su metriche multiple.
     */
    static std::map<std::string, int> confrontaSquadre(const Squadra& sq1, const Squadra& sq2);
    
    /**
     * @brief Trova la squadra migliore per una metrica specifica.
     */
    static Squadra* squadraMigliorePerMetrica(const Stagione& stagione, const std::string& metrica);
    
    /**
     * @brief Calcola la media di una metrica per tutte le squadre.
     */
    static double mediaMetrica(const Stagione& stagione, int (Squadra::*getter)() const);
    
    /**
     * @brief Calcola deviazione standard di una metrica.
     */
    static double deviazioneStandard(const Stagione& stagione, int (Squadra::*getter)() const);
    
    /**
     * @brief Trova valore minimo di una metrica.
     */
    static int minimoMetrica(const Stagione& stagione, int (Squadra::*getter)() const);
    
    /**
     * @brief Trova valore massimo di una metrica.
     */
    static int massimoMetrica(const Stagione& stagione, int (Squadra::*getter)() const);
    
    /**
     * @brief Trova squadre bilanciate (attacco E difesa sopra media).
     */
    static std::vector<Squadra*> squadreBilanciate(const Stagione& stagione);
    
    /**
     * @brief Classifica squadre per efficienza (punti/mete).
     */
    static std::vector<std::pair<Squadra*, double>> classificaEfficienza(const Stagione& stagione);
    
    /**
     * @brief Stampa report statistico completo della stagione.
     */
    static void stampaReportStagione(const Stagione& stagione);

private:
    static const std::vector<std::string> RUOLI_STANDARD;
};

#endif

