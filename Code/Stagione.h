#ifndef STAGIONE_H
#define STAGIONE_H

#include <vector>
#include <memory>
#include <ostream>
#include "Squadra.h"
#include "Partita.h"

/**
 * @class Stagione
 * @brief Gestisce un'intera stagione sportiva di rugby.
 * 
 * Classe principale che rappresenta una stagione completa, contenendo:
 * - Tutte le squadre partecipanti (gestite con unique_ptr per ownership esclusivo)
 * - Tutte le partite disputate (gestite per valore)
 * - Algoritmi per analisi statistiche e classifiche
 * 
 * Include template metaprogramming per calcoli generici sulle statistiche.
 */
class Stagione {
private:
    int anno;                                    ///< Anno della stagione (es. 2025).
    std::vector<std::unique_ptr<Squadra>> squadre; ///< Squadre partecipanti (ownership esclusivo).
    std::vector<Partita> partite;                ///< Calendario completo delle partite.

public:
    /**
     * @brief Costruttore esplicito della stagione.
     * @param anno Anno della stagione sportiva.
     */
    explicit Stagione(int anno);

    /**
     * @brief Cerca una squadra tramite il suo ID univoco.
     * @param id Identificatore numerico della squadra.
     * @return Puntatore alla squadra trovata, nullptr se non esistente.
     */
    Squadra* trovaSquadraPerId(int id);

    // *** COPY & MOVE SEMANTICS (IMPLEMENTAZIONE AVANZATA) ***
    /**
     * @brief Costruttore di copia con implementazione PROFONDA.
     * Crea una copia completa di tutte le squadre (deep copy dei dati).
     */
    Stagione(const Stagione& other);

    /**
     * @brief Operatore di assegnazione per copia.
     * Implementazione profonda per copiare tutti i dati.
     */
    Stagione& operator=(const Stagione& other);

    /**
     * @brief Costruttore di move (EFFICIENTE).
     * Trasferisce ownership delle risorse senza duplicazione.
     */
    Stagione(Stagione&& other) noexcept;

    /**
     * @brief Operatore di assegnazione di move (EFFICIENTE).
     * Trasferisce le risorse in modo ottimizzato.
     */
    Stagione& operator=(Stagione&& other) noexcept;

    // *** ALGORITMI PER CLASSIFICHE E ANALISI ***

    /**
     * @brief Genera la classifica completa ordinata per punteggio.
     * @return Vettore di puntatori costanti alle squadre ordinate.
     */
    std::vector<const Squadra*> classificaSquadre() const;

    /**
     * @brief Calcola la media del punteggio di tutte le squadre.
     * @return Media aritmetica dei punteggi di classifica.
     */
    double mediaPunteggioSquadre() const;

    /**
     * @brief Calcola la media delle mete totali di tutte le squadre.
     * @return Media aritmetica delle mete segnate.
     */
    double mediaMeteTotaliSquadre() const;

    /**
     * @brief Trova le prime N squadre della classifica.
     * @param n Numero di squadre da restituire (top N).
     * @return Vettore delle migliori N squadre.
     */
    std::vector<const Squadra*> topSquadre(size_t n) const;

    // *** TEMPLATE METAPROGRAMMING - POINTER TO MEMBER FUNCTION ***
    /**
     * @brief Template generico per calcolare la MEDIA di una statistica.
     * Usa pointer to member function per applicare lo stesso algoritmo
     * a qualsiasi statistica numerica della classe Squadra.
     * 
     * @tparam StatType Tipo della statistica (int, double, ecc.).
     * @param squadre Vettore di squadre da analizzare.
     * @param getter Pointer al metodo getter della statistica.
     * @return Media aritmetica della statistica specificata.
     */
    template<typename StatType>
    StatType calcolaMedia(const std::vector<std::unique_ptr<Squadra>>& squadre,
                          StatType(Squadra::*getter)() const) const;

    /**
     * @brief Template generico per calcolare la SOMMA di una statistica.
     * 
     * @tparam StatType Tipo della statistica.
     * @param squadre Vettore di squadre da analizzare.
     * @param getter Pointer al metodo getter della statistica.
     * @return Somma totale della statistica specificata.
     */
    template<typename StatType>
    StatType sommaStatistica(const std::vector<std::unique_ptr<Squadra>>& squadre,
                             StatType(Squadra::*getter)() const) const;

    // *** ESempi pratici di utilizzo dei template ***
    double mediaPunteggioTemplate() const;  ///< Usa calcolaMedia<> internamente.
    int sommaMeteTemplate() const;          ///< Usa sommaStatistica<> internamente.

    /**
     * @brief Distruttore di default.
     * std::unique_ptr gestisce automaticamente la deallocazione delle squadre.
     */
    ~Stagione() = default;

    // *** GETTER PER ACCESSO IN SOLA LETTURA ***
    const Squadra* getClassificaFinale() const;    ///< Prima squadra della classifica.
    const std::vector<Partita>& getCalendario() const; ///< Tutte le partite programmate.
    const std::vector<std::unique_ptr<Squadra>>& getSquadre() const; ///< Tutte le squadre.
    const std::vector<Partita>& getPartite() const; ///< Partite disputate.
    int getAnno() const;                           ///< Anno della stagione.

    // *** METODI PER MODIFICA DELLA STAGIONE ***

    /**
     * @brief Aggiunge una nuova partita al calendario.
     * @param p Partita da inserire.
     */
    void addPartita(const Partita& p);

    /**
     * @brief Aggiunge una nuova squadra alla stagione.
     * @param s Squadra da inserire (unique_ptr trasferisce ownership).
     */
    void addSquadra(std::unique_ptr<Squadra> s);

    /**
     * @brief Operatore di output per stampa completa della stagione.
     * Visualizza anno, squadre, classifica e statistiche principali.
     */
    friend std::ostream& operator<<(std::ostream& os, const Stagione& s);
};

#endif

