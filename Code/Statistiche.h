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
 */
class Statistiche {
public:
    // ==================== STATISTICHE GIOCATORI ====================
    
    /**
     * @brief Trova il giocatore con più placcaggi usando std::max_element.
     * @param squadra Squadra da analizzare
     * @return Puntatore al miglior placcaggiatore
     */
    static const Giocatore* getMigliorPlaccaggitore(const Squadra& squadra);
    
    /**
     * @brief Trova il capocannoniere (più mete) usando std::max_element.
     * @param squadra Squadra da analizzare
     * @return Puntatore al capocannoniere
     */
    static const Giocatore* getCapocannoniere(const Squadra& squadra);
    
    /**
     * @brief Trova il giocatore con più metri percorsi.
     * @param squadra Squadra da analizzare
     * @return Puntatore al miglior corridore
     */
    static const Giocatore* getMigliorCorridore(const Squadra& squadra);
    
    /**
     * @brief Conta giocatori per ruolo specifico usando std::count_if.
     * @param squadra Squadra da analizzare
     * @param ruolo Ruolo da contare
     * @return Numero giocatori con quel ruolo
     */
    static int contaGiocatoriPerRuolo(const Squadra& squadra, const std::string& ruolo);
    
    /**
     * @brief Filtra giocatori con almeno N mete usando std::copy_if.
     * @param squadra Squadra da filtrare
     * @param soglia Soglia minima mete
     * @return Vettore giocatori sopra soglia
     */
    static std::vector<Giocatore> giocatoriConMeteSopra(const Squadra& squadra, int soglia);
    
    /**
     * @brief Filtra giocatori con almeno N placcaggi.
     * @param squadra Squadra da filtrare
     * @param soglia Soglia minima placcaggi
     * @return Vettore giocatori sopra soglia
     */
    static std::vector<Giocatore> giocatoriConPlaccaggiSopra(const Squadra& squadra, int soglia);
    
    /**
     * @brief Calcola la media mete per giocatore.
     * @param squadra Squadra da analizzare
     * @return Media mete per giocatore
     */
    static double mediaMetePerGiocatore(const Squadra& squadra);
    
    /**
     * @brief Calcola la media placcaggi per giocatore.
     * @param squadra Squadra da analizzare
     * @return Media placcaggi per giocatore
     */
    static double mediaPlaccaggiPerGiocatore(const Squadra& squadra);
    
    /**
     * @brief Distribuzione giocatori per tutti i ruoli.
     * @param squadra Squadra da analizzare
     * @return Map ruolo?conteggio
     */
    static std::map<std::string, int> distribuzioneRuoli(const Squadra& squadra);
    
    /**
     * @brief Stampa report statistico completo della squadra.
     * @param squadra Squadra da riportare
     */
    static void stampaReportSquadra(const Squadra& squadra);
    
    // ==================== STATISTICHE STAGIONE ====================
    
    /**
     * @brief Genera classifica completa ordinata per punteggio usando std::sort.
     * @param stagione Stagione da classificare
     * @return Vettore squadre ordinate
     */
    static std::vector<Squadra*> classificaCompleta(const Stagione& stagione);
    
    /**
     * @brief Trova le top N squadre usando std::partial_sort.
     * @param stagione Stagione da analizzare
     * @param n Numero squadre top
     * @return Prime N squadre
     */
    static std::vector<Squadra*> topNSquadre(const Stagione& stagione, size_t n);
    
    /**
     * @brief Trova il mediano della classifica usando std::nth_element.
     * @param stagione Stagione da analizzare
     * @return Squadra mediana
     */
    static Squadra* squadraMediana(const Stagione& stagione);
    
    /**
     * @brief Confronta due squadre su metriche multiple.
     * @param sq1 Prima squadra
     * @param sq2 Seconda squadra
     * @return Map metrica?differenza
     */
    static std::map<std::string, int> confrontaSquadre(const Squadra& sq1, const Squadra& sq2);
    
    /**
     * @brief Trova la squadra migliore per una metrica specifica.
     * @param stagione Stagione da analizzare
     * @param metrica Nome metrica
     * @return Squadra migliore
     */
    static Squadra* squadraMigliorePerMetrica(const Stagione& stagione, const std::string& metrica);
    
    /**
     * @brief Calcola la media di una metrica per tutte le squadre.
     * @param stagione Stagione da analizzare
     * @param getter Pointer-to-member getter
     * @return Media metrica
     */
    static double mediaMetrica(const Stagione& stagione, int (Squadra::*getter)() const);
    
    /**
     * @brief Calcola deviazione standard di una metrica.
     * @param stagione Stagione da analizzare
     * @param getter Pointer-to-member getter
     * @return Deviazione standard
     */
    static double deviazioneStandard(const Stagione& stagione, int (Squadra::*getter)() const);
    
    /**
     * @brief Trova valore minimo di una metrica.
     * @param stagione Stagione da analizzare
     * @param getter Pointer-to-member getter
     * @return Valore minimo
     */
    static int minimoMetrica(const Stagione& stagione, int (Squadra::*getter)() const);
    
    /**
     * @brief Trova valore massimo di una metrica.
     * @param stagione Stagione da analizzare
     * @param getter Pointer-to-member getter
     * @return Valore massimo
     */
    static int massimoMetrica(const Stagione& stagione, int (Squadra::*getter)() const);
    
    /**
     * @brief Trova squadre bilanciate (attacco E difesa sopra media).
     * @param stagione Stagione da analizzare
     * @return Squadre bilanciate
     */
    static std::vector<Squadra*> squadreBilanciate(const Stagione& stagione);
    
    /**
     * @brief Classifica squadre per efficienza (punti/mete).
     * @param stagione Stagione da analizzare
     * @return Classifica efficienza
     */
    static std::vector<std::pair<Squadra*, double>> classificaEfficienza(const Stagione& stagione);
    
    /**
     * @brief Stampa report statistico completo della stagione.
     * @param stagione Stagione da riportare
     */
    static void stampaReportStagione(const Stagione& stagione);

private:
    /**
     * @brief Ruoli standard rugby.
     */
    static const std::vector<std::string> RUOLI_STANDARD;
};

#endif

