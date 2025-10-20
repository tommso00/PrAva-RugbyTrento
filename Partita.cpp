#include "Partita.h"
#include "Giocatore.h"
#include <sstream>
#include <algorithm>

Partita::Partita() : id(0), data("") {}
Partita::Partita(int id, string data) : id(id), data(data) {}
Partita::~Partita() {}

int Partita::getId() const { return id; }
string Partita::getData() const { return data; }

void Partita::aggiungiGiocatore(shared_ptr<Giocatore> g) {
    if (!g) return;
    for (auto &p : giocatori) if (p->getId() == g->getId()) return; // evita duplicati
    giocatori.push_back(g);
    if (punteggi.find(g->getId()) == punteggi.end()) punteggi[g->getId()] = 0.0;
}

void Partita::setPunteggio(shared_ptr<Giocatore> g, double punti) {
    if (!g) return;
    punteggi[g->getId()] = punti;
}

double Partita::getPunteggio(shared_ptr<Giocatore> g) const {
    if (!g) return 0.0;
    auto it = punteggi.find(g->getId());
    if (it == punteggi.end()) return 0.0;
    return it->second;
}

vector<shared_ptr<Giocatore>> Partita::getGiocatori() const { return giocatori; }

string Partita::toString() const {
    ostringstream oss;
    oss << "Partita [" << id << "] data=" << data << " giocatori=" << giocatori.size() << "\n";
    for (auto &g : giocatori) {
        double p = 0.0;
        auto it = punteggi.find(g->getId());
        if (it != punteggi.end()) p = it->second;
        oss << "  " << g->getNome() << " " << g->getCognome() << " -> " << p << "\n";
    }
    return oss.str();
}

string Partita::toCSV() const {
    // formato: id,data,player1|player2|...,id1:score1|id2:score2|...
    ostringstream oss;
    oss << id << "," << data << ",";
    for (size_t i = 0; i < giocatori.size(); ++i) {
        if (i) oss << "|";
        oss << giocatori[i]->getId();
    }
    oss << ",";
    bool first = true;
    for (auto &kv : punteggi) {
        if (!first) oss << "|";
        oss << kv.first << ":" << kv.second;
        first = false;
    }
    return oss.str();
}

Partita Partita::fromCSV(const string &line, const vector<shared_ptr<Giocatore>> &giocatoriDisponibili) {
    istringstream iss(line);
    string token;

    auto next = [&](string &out) {
        if (!getline(iss, out, ',')) out = "";
    };

    next(token);
    int pid = token.empty() ? 0 : stoi(token);
    string data;
    next(data);
    string listaIds;
    next(listaIds);
    string punteggiStr;
    next(punteggiStr);

    Partita p(pid, data);

    // parse listaIds separated by '|'
    if (!listaIds.empty()) {
        istringstream sIds(listaIds);
        string idTok;
        while (getline(sIds, idTok, '|')) {
            if (idTok.empty()) continue;
            int gid = stoi(idTok);
            // cerca shared_ptr nei disponibili
            auto it = find_if(giocatoriDisponibili.begin(), giocatoriDisponibili.end(),
                              [gid](const shared_ptr<Giocatore> &g){ return g && g->getId() == gid; });
            if (it != giocatoriDisponibili.end()) {
                p.aggiungiGiocatore(*it);
            }
        }
    }

    // parse punteggi id:val separated by '|'
    if (!punteggiStr.empty()) {
        istringstream sP(punteggiStr);
        string kv;
        while (getline(sP, kv, '|')) {
            if (kv.empty()) continue;
            size_t pos = kv.find(':');
            if (pos == string::npos) continue;
            int gid = stoi(kv.substr(0, pos));
            double val = stod(kv.substr(pos + 1));
            // set punteggio (se il giocatore è presente nella partita)
            auto itg = find_if(p.giocatori.begin(), p.giocatori.end(),
                [gid](const shared_ptr<Giocatore> &g){ return g && g->getId() == gid; });
            if (itg != p.giocatori.end()) {
                p.punteggi[gid] = val;
            } else {
                // se non è presente, aggiungiamo comunque il valore (senza shared_ptr)
                p.punteggi[gid] = val;
            }
        }
    }

    return p;
}

