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
    Squadra(const Squadra& other);
    Squadra(Squadra&& other) noexcept;
    Squadra& operator=(const Squadra& other);
    Squadra& operator=(Squadra&& other) noexcept;

    ~Squadra() = default;

    // *** METODI GETTER E SETTER DI BASE ***
    std::string getNome() const;
    std::string getIndirizzo() const;
    int getId() const;
    int getPunteggio() const;

    const std::vector<Giocatore>& getGiocatori() const { return giocatori; }
    const std::vector<Staff>& getStaff() const { return staffTecnico; }

    void setNome(const std::string& n);
    void setIndirizzo(const std::string& i);
    void setId(int i);
    void setPunteggio(int p);

    // *** GESTIONE GIOCATORI ***
    void addGiocatore(const Giocatore& g);
    void removeGiocatore(int id);

    // *** GESTIONE STAFF (con Move Semantics) ***
    void addStaff(const Staff& membro);
    void addStaff(Staff&& membro);
    void removeStaff(size_t index);
    void clearStaff();

    // *** STATISTICHE DI SQUADRA ***
    int getPossessoPalla() const;
    void setPossessoPalla(int value);

    double getTerritorio() const;
    void setTerritorio(double value);

    int getPlaccaggiTotali() const;
    void setPlaccaggiTotali(int value);

    int getMetriGuadagnatiTotali() const;
    void setMetriGuadagnatiTotali(int value);

    int getMeteTotali() const;
    void setMeteTotali(int value);

    int getFalliTotali() const;
    void setFalliTotali(int value);

    void aggiungiPuntiClassifica(int delta) { punteggioClassifica += delta; }
    void aggiungiMete(int delta) { meteTotali += delta; }

    // *** MISCHIE E TOUCHE ***
    int getMischieVinte() const;
    void setMischieVinte(int value);

    int getMischiePerse() const;
    void setMischiePerse(int value);

    int getToucheVinte() const;
    void setToucheVinte(int value);

    int getTouchePerse() const;
    void setTouchePerse(int value);

    void aggiornaStatistiche();
    void addPuntiClassifica(int delta);
    void addMete(int delta);

    friend std::ostream& operator<<(std::ostream& os, const Squadra& s);
};

#endif

