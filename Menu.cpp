#include "Menu.h"
#include <sstream>
#include <limits>
#include <algorithm>

Menu::Menu() : nextGiocatoreId(1), nextPartitaId(1) {}
Menu::~Menu() {}

void Menu::mostraMenu() {
    cout << "=== PrAva_RugbyTrento ===\n";
    cout << "1) Aggiungi giocatore\n";
    cout << "2) Crea partita\n";
    cout << "3) Visualizza giocatori\n";
    cout << "4) Visualizza partite\n";
    cout << "5) Statistiche\n";
    cout << "6) Salva dati su CSV\n";
    cout << "7) Carica dati da CSV\n";
    cout << "0) Esci\n";
}

void Menu::gestisciInput() {
    int choice = -1;
    while (true) {
        mostraMenu();
        cout << "Scelta: ";
        if (!(cin >> choice)) {
            cin.clear();
            string dummy; getline(cin, dummy);
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice) {
            case 1: aggiungiGiocatore(); break;
            case 2: creaPartita(); break;
            case 3: mostraGiocatori(); break;
            case 4: mostraPartite(); break;
            case 5: mostraStatistiche(); break;
            case 6: salvaDati(); break;
            case 7: caricaDati(); break;
            case 0: return;
            default: cout << "Scelta non valida.\n"; break;
        }
    }
}

void Menu::aggiungiGiocatore() {
    string nome, cognome;
    int eta;
    double punti;
    cout << "Nome: "; getline(cin, nome);
    cout << "Cognome: "; getline(cin, cognome);
    cout << "Eta: "; cin >> eta; cin.ignore();
    cout << "Punteggio iniziale: "; cin >> punti; cin.ignore();
    Giocatore g(nextGiocatoreId++, nome, cognome, eta, punti);
    gestoreGiocatori.inserisci(g);
    cout << "Giocatore aggiunto: " << g.toString() << "\n";
}

void Menu::creaPartita() {
    string data;
    cout << "Data partita (AAAA-MM-GG): ";
    getline(cin, data);
    Partita p(nextPartitaId++, data);

    // costruiamo vettore di shared_ptr dai giocatori attualmente nel gestore
    vector<shared_ptr<Giocatore>> disponibili;
    for (auto &g : gestoreGiocatori.getAll()) {
        disponibili.push_back(make_shared<Giocatore>(g));
    }

    if (disponibili.empty()) {
        cout << "Nessun giocatore registrato. Aggiungi giocatori prima.\n";
        gestorePartite.inserisci(p);
        return;
    }

    cout << "Giocatori disponibili (id - nome cognome):\n";
    for (auto &sp : disponibili) cout << sp->getId() << " - " << sp->getNome() << " " << sp->getCognome() << "\n";

    cout << "Inserisci gli id dei giocatori partecipanti separati da spazi (termina con invio):\n";
    string line;
    getline(cin, line);
    istringstream iss(line);
    int gid;
    while (iss >> gid) {
        auto it = find_if(disponibili.begin(), disponibili.end(),
                          [gid](const shared_ptr<Giocatore> &g){ return g && g->getId() == gid; });
        if (it != disponibili.end()) {
            p.aggiungiGiocatore(*it);
            double punti;
            cout << "Punteggio per " << (*it)->getNome() << " " << (*it)->getCognome() << ": ";
            cin >> punti; cin.ignore();
            p.setPunteggio(*it, punti);
        } else {
            cout << "Id " << gid << " non trovato.\n";
        }
    }

    gestorePartite.inserisci(p);
    cout << "Partita creata: " << p.toString() << "\n";
}

void Menu::mostraGiocatori() const {
    cout << "=== Giocatori registrati ===\n";
    gestoreGiocatori.stampaTutti();
}

void Menu::mostraPartite() const {
    cout << "=== Partite registrate ===\n";
    for (auto &p : gestorePartite.getAll()) cout << p.toString() << "\n";
}

void Menu::mostraStatistiche() {
    vector<Partita> v = gestorePartite.getAll();
    Statistiche s(v);
    s.stampaStatistiche();
}

void Menu::salvaDati() {
    string fileG = "giocatori.csv";
    string fileP = "partite.csv";
    // salva giocatori (valori)
    vector<Giocatore> vg = gestoreGiocatori.getAll();
    if (fileManager.salvaGiocatoriCSV(fileG, vg)) cout << "Giocatori salvati in " << fileG << "\n";
    else cout << "Errore salvataggio giocatori\n";

    // salva partite (richiede vector<Partita>)
    vector<Partita> vp = gestorePartite.getAll();
    if (fileManager.salvaPartiteCSV(fileP, vp)) cout << "Partite salvate in " << fileP << "\n";
    else cout << "Errore salvataggio partite\n";
}

void Menu::caricaDati() {
    string fileG = "giocatori.csv";
    string fileP = "partite.csv";

    // carica giocatori
    vector<Giocatore> vg = fileManager.caricaGiocatoriCSV(fileG);
    gestoreGiocatori.clear();
    for (auto &g : vg) gestoreGiocatori.inserisci(g);
    cout << "Caricati " << vg.size() << " giocatori da " << fileG << "\n";

    // converti in shared_ptr per ricostruire le partite
    vector<shared_ptr<Giocatore>> disponibili;
    for (auto &g : gestoreGiocatori.getAll()) {
        disponibili.push_back(make_shared<Giocatore>(g));
    }

    // carica partite
    vector<Partita> vp = fileManager.caricaPartiteCSV(fileP, disponibili);
    gestorePartite.clear();
    for (auto &p : vp) gestorePartite.inserisci(p);
    cout << "Caricate " << vp.size() << " partite da " << fileP << "\n";
}

