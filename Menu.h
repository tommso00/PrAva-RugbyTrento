#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include <memory>
#include "Giocatore.h"
#include "Partita.h"
#include "Statistiche.h"
#include "GestoreDati.h"
#include "FileManager.h"
using namespace std;

class Menu {
private:
    GestoreDati<Giocatore> gestoreGiocatori;
    GestoreDati<Partita> gestorePartite;
    Statistiche stats;
    FileManager fileManager;

    int nextGiocatoreId;
    int nextPartitaId;

public:
    Menu();
    ~Menu();

    void mostraMenu();
    void gestisciInput();
    void aggiungiGiocatore();
    void creaPartita();
    void mostraGiocatori() const;
    void mostraPartite() const;
    void mostraStatistiche();
    void salvaDati();
    void caricaDati();
};

#endif // MENU_H

