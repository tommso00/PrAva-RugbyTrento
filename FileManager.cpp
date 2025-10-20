#include "FileManager.h"
#include <sstream>

bool FileManager::salvaGiocatoriCSV(const string &filename, const vector<Giocatore> &giocatori) {
    ofstream ofs(filename);
    if (!ofs) return false;
    // header (opzionale)
    ofs << "id,nome,cognome,eta,punteggio\n";
    for (const auto &g : giocatori) {
        ofs << g.toCSV() << "\n";
    }
    ofs.close();
    return true;
}

vector<Giocatore> FileManager::caricaGiocatoriCSV(const string &filename) {
    vector<Giocatore> res;
    ifstream ifs(filename);
    if (!ifs) return res;
    string line;
    // salta header se presente
    if (getline(ifs, line)) {
        // se la prima riga contiene "id," consideriamola header e passiamo alla successiva
        if (line.rfind("id,", 0) != 0) {
            // non è header: processa la riga
            if (!line.empty()) res.push_back(Giocatore::fromCSV(line));
        }
    }
    // leggi il resto
    while (getline(ifs, line)) {
        if (line.empty()) continue;
        res.push_back(Giocatore::fromCSV(line));
    }
    ifs.close();
    return res;
}

bool FileManager::salvaPartiteCSV(const string &filename, const vector<Partita> &partite) {
    ofstream ofs(filename);
    if (!ofs) return false;
    ofs << "id,data,giocatori,punteggi\n";
    for (const auto &p : partite) {
        ofs << p.toCSV() << "\n";
    }
    ofs.close();
    return true;
}

vector<Partita> FileManager::caricaPartiteCSV(const string &filename, const vector<shared_ptr<Giocatore>> &giocatoriDisponibili) {
    vector<Partita> res;
    ifstream ifs(filename);
    if (!ifs) return res;
    string line;
    // salta header se presente
    if (getline(ifs, line)) {
        if (line.rfind("id,", 0) != 0) {
            if (!line.empty()) res.push_back(Partita::fromCSV(line, giocatoriDisponibili));
        }
    }
    while (getline(ifs, line)) {
        if (line.empty()) continue;
        res.push_back(Partita::fromCSV(line, giocatoriDisponibili));
    }
    ifs.close();
    return res;
}

