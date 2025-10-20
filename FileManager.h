#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include "Giocatore.h"
#include "Partita.h"
using namespace std;

class FileManager {
public:
    FileManager() = default;
    ~FileManager() = default;

    // Giocatori
    bool salvaGiocatoriCSV(const string &filename, const vector<Giocatore> &giocatori);
    vector<Giocatore> caricaGiocatoriCSV(const string &filename);

    // Partite (richiede vector<shared_ptr<Giocatore>> disponibili per collegare id->shared_ptr)
    bool salvaPartiteCSV(const string &filename, const vector<Partita> &partite);
    vector<Partita> caricaPartiteCSV(const string &filename, const vector<shared_ptr<Giocatore>> &giocatoriDisponibili);
};

#endif // FILEMANAGER_H

