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

    // *** COPY & MOVE SEMANTICS ***
    /**
     * @brief Costruttore di copia con implementazione PROFONDA.
     * Crea una copia completa di tutte le squadre (copia profonda dei dati).
     */
    Stagione(const Stagione& other);

    /**
     * @brief Operatore di assegnazione per copia.
     * Implementazione profonda per copiare tutti i dati.
     */
    Stagione& operator=(const Stagione& other);

    /**
     * @brief Costruttore di move.
     * Trasferisce ownership delle risorse senza duplicazione.
     */
    Stagione(Stagione&& other) noexcept;

    /**
     * @brief Operatore di assegnazione di move.
     * Trasferisce le risorse in modo ottimizzato.
     */
    Stagione& operator=(Stagione&& other) noexcept;

    /**
     * @brief Distruttore di default.
     * std::unique_ptr gestisce automaticamente la deallocazione delle squadre.
     */
    ~Stagione() = default;

    // *** GETTER PER ACCESSO IN SOLA LETTURA ***
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

