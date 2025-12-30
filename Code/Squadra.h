#ifndef SQUADRA_H
#define SQUADRA_H

#include <string>
#include <vector>
#include <iostream>
#include "Giocatore.h"
#include "Staff.h"

/**
 * @class Squadra
 * @brief Rappresenta una squadra di rugby composta da giocatori e staff.
 */
class Squadra {
private:
    // Identificativi e dati anagrafici della squadra
    std::string nome;
    std::string indirizzo;
    int id;
    int punteggioClassifica;

    // Roster della squadra
    std::vector<Giocatore> giocatori;
    std::vector<Staff> staffTecnico;

    // Statistiche di gioco generali
    int possessoPalla;
    double territorio;

    // Statistiche aggregate
    int placcaggiTotali;
    int metriGuadagnatiTotali;
    int meteTotali;
    int falliTotali;

    // Performance in fasi statiche di gioco
    int mischieVinte;
    int mischiePerse;
    int toucheVinte;
    int touchePerse;

public:
    /**
     * @brief Costruttore della classe Squadra.
     */
    Squadra(int id_, const std::string& nome, const std::string& indirizzo);

    // *** COPY & MOVE SEMANTICS ***
    /**
     * @brief Costruttore di Copia.
     */
    Squadra(const Squadra& other);
    /**
     * @brief Costruttore Move.
     */
    Squadra(Squadra&& other) noexcept;
    /**
     * @brief Assegnazione di Copia.
     */
    Squadra& operator=(const Squadra& other);
    /**
     * @brief Assegnazione Move.
     */
    Squadra& operator=(Squadra&& other) noexcept;

    ~Squadra() = default;

    // *** METODI GETTER E SETTER DI BASE ***
    /**
     * @brief Getter nome squadra.
     */
    std::string getNome() const;
    /**
     * @brief Getter indirizzo squadra.
     */
    std::string getIndirizzo() const;
    /**
     * @brief Getter ID squadra.
     */
    int getId() const;
    /**
     * @brief Getter punteggio classifica.
     */
    int getPunteggio() const;

    /**
     * @brief Getter roster giocatori.
     */
    const std::vector<Giocatore>& getGiocatori() const { return giocatori; }
    /**
     * @brief Getter roster staff.
     */
    const std::vector<Staff>& getStaff() const { return staffTecnico; }

    /**
     * @brief Setter nome squadra.
     */
    void setNome(const std::string& n);
    /**
     * @brief Setter indirizzo squadra.
     */
    void setIndirizzo(const std::string& i);
    /**
     * @brief Setter ID squadra.
     */
    void setId(int i);
    /**
     * @brief Setter punteggio classifica.
     */
    void setPunteggio(int p);

    // *** GESTIONE GIOCATORI ***
    /**
     * @brief Aggiunge giocatore al roster.
     */
    void addGiocatore(const Giocatore& g);
    /**
     * @brief Rimuove giocatore per ID.
     */
    void removeGiocatore(int id);

    // *** GESTIONE STAFF (con Move Semantics) ***
    /**
     * @brief Aggiunge staff (copy).
     */
    void addStaff(const Staff& membro);
    /**
     * @brief Aggiunge staff (move).
     */
    void addStaff(Staff&& membro);
    /**
     * @brief Rimuove staff per indice.
     */
    void removeStaff(size_t index);
    /**
     * @brief Svuota roster staff.
     */
    void clearStaff();

    // *** STATISTICHE DI SQUADRA ***
    /**
     * @brief Getter possesso palla.
     */
    int getPossessoPalla() const;
    /**
     * @brief Setter possesso palla.
     */
    void setPossessoPalla(int value);

    /**
     * @brief Getter territorio.
     */
    double getTerritorio() const;
    /**
     * @brief Setter territorio.
     */
    void setTerritorio(double value);

    /**
     * @brief Getter placcaggi totali.
     */
    int getPlaccaggiTotali() const;
    /**
     * @brief Setter placcaggi totali.
     */
    void setPlaccaggiTotali(int value);

    /**
     * @brief Getter metri guadagnati.
     */
    int getMetriGuadagnatiTotali() const;
    /**
     * @brief Setter metri guadagnati.
     */
    void setMetriGuadagnatiTotali(int value);

    /**
     * @brief Getter mete totali.
     */
    int getMeteTotali() const;
    /**
     * @brief Setter mete totali.
     */
    void setMeteTotali(int value);

    /**
     * @brief Getter falli totali.
     */
    int getFalliTotali() const;
    /**
     * @brief Setter falli totali.
     */
    void setFalliTotali(int value);

    /**
     * @brief Incrementa punteggio classifica.
     */
    void aggiungiPuntiClassifica(int delta) { punteggioClassifica += delta; }
    /**
     * @brief Incrementa mete totali.
     */
    void aggiungiMete(int delta) { meteTotali += delta; }

    // *** MISCHIE E TOUCHE ***
    /**
     * @brief Getter mischie vinte.
     */
    int getMischieVinte() const;
    /**
     * @brief Setter mischie vinte.
     */
    void setMischieVinte(int value);

    /**
     * @brief Getter mischie perse.
     */
    int getMischiePerse() const;
    /**
     * @brief Setter mischie perse.
     */
    void setMischiePerse(int value);

    /**
     * @brief Getter touche vinte.
     */
    int getToucheVinte() const;
    /**
     * @brief Setter touche vinte.
     */
    void setToucheVinte(int value);

    /**
     * @brief Getter touche perse.
     */
    int getTouchePerse() const;
    /**
     * @brief Setter touche perse.
     */
    void setTouchePerse(int value);

    /**
     * @brief Ricalcola statistiche aggregate.
     */
    void aggiornaStatistiche();
    /**
     * @brief Alias aggiungiPuntiClassifica.
     */
    void addPuntiClassifica(int delta);
    /**
     * @brief Alias aggiungiMete.
     */
    void addMete(int delta);

    /**
     * @brief Overload operator<< per Squadra.
     */
    friend std::ostream& operator<<(std::ostream& os, const Squadra& s);
};

#endif

