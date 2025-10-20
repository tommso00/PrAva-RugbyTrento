#include "Statistiche.h"
#include "Giocatore.h"
#include <map>

Statistiche::Statistiche() : partite() {}
Statistiche::Statistiche(const vector<Partita> &p) : partite(p) {}
Statistiche::~Statistiche() {}

double Statistiche::mediaPunteggi() const {
    double sum = 0.0;
    size_t count = 0;
    for (const auto &p : partite) {
        for (auto &gptr : p.getGiocatori()) {
            if (gptr) {
                sum += p.getPunteggio(gptr);
                ++count;
            }
        }
    }
    return (count == 0) ? 0.0 : (sum / count);
}

shared_ptr<Giocatore> Statistiche::migliorGiocatore() const {
/*
    map<int, double> accum;
    map<int, shared_ptr<Giocatore>> ref;
    for (const auto &p : partite) {
        for (const auto &gptr : p.getGiocatori()) {
            if (!gptr) continue;
            int id = gptr->getId();
            accum[id] += p.getPunteggio(gptr);
            ref[id] = gptr;
        }
    }
    int bestId = -1;
    double bestVal = -numeric_limits<double>::infinity();
    for (const auto &kv : accum) {
        if (kv.second > bestVal) {
            bestVal = kv.second;
            bestId = kv.first;
        }
    }
    if (bestId == -1) return nullptr;
    return ref.at(bestId);
*/
}

int Statistiche::totalePartite() const {
    return static_cast<int>(partite.size());
}

void Statistiche::stampaStatistiche() const {
    cout << "Totale partite: " << totalePartite() << "\n";
    cout << "Media punteggi: " << mediaPunteggi() << "\n";
    auto best = migliorGiocatore();
    if (best) cout << "Miglior giocatore: " << best->toString() << "\n";
    else cout << "Nessun miglior giocatore (dati insufficienti).\n";
}

