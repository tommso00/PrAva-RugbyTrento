#include "Gestionale.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>


//Ho pensato molto al fatto che fstream e sstream non bastino per la comunicazione tra .cpp e .csv 
//per ora ho implementato così
//non so' cosa hai in mente con Statistiche.h since

using namespace std;

// ==================== MENU PRINCIPALE ====================
void Gestionale::avvia() {
    int scelta = -1;
    do {
        cout << "\n=== MENU GESTIONALE ===\n";
        cout << "1) Carica dati da CSV\n";
        cout << "2) Crea nuova stagione\n";
        cout << "3) Salva dati su CSV\n";
        cout << "0) Esci\n";
        cout << "Scelta: ";
        cin >> scelta;

        switch (scelta) {
            case 1: fetchStagioni("database/squadre_girone_rugby_trento.csv"); break;
            case 2: creaStagione(); break;
            case 3: salvaStagioni(); break;
            case 0: cout << "Uscita...\n"; break;
            default: cout << "Scelta non valida.\n"; break;
        }
    } while (scelta != 0);
}

// ==================== CREA STAGIONE ====================
void Gestionale::creaStagione() {
    int anno;
    cout << "Inserisci anno stagione: ";
    cin >> anno;

    if (trovaStagione(anno) != NULL) {
        cout << "Stagione " << anno << " già esistente.\n";
        return;
    }

    stagioni.push_back(unique_ptr<Stagione>(new Stagione(anno)));
    cout << "Stagione " << anno << " creata correttamente!\n";
    
    //dopo averla creata che si fa'? :) 
    //bisognerebbe indicare un calendario -> partite->vari set partite
    //bisognerebbe anche indicare quante squadre composto (del tipo che segna quante ne mettiamo noi, non ho sbatta di poi dover inserire da terminale nome per nome di una squadra ;| )
    
}

// ==== CARICA STAGIONE ===
void Gestionale::caricaStagione(const std::string& filename, int stagione) {
	std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Errore apertura file: " << filename << std::endl;
        return;
    }

    std::string riga;
    int contoRighe = 0;
    bool intestazioneSaltata = false;

    while (std::getline(file, riga)) {
        if (!intestazioneSaltata) {
            intestazioneSaltata = true; // salta intestazione
            continue;
        }
        contoRighe++;
        if (contoRighe == stagione) {
            // Stampa la riga richiesta
            std::cout << "Riga " << stagione << ": " << riga << std::endl;
            int anno = std::stoi(riga);
            stagioni.push_back(unique_ptr<Stagione>(new Stagione(anno)));
    		cout << "Stagione " << anno << " CARICATA correttamente!"<<endl;
            return;
        }
    }

    std::cout << "Riga " << stagione << " non trovata nel file." << std::endl;
}

// ====== MODIFICA STAGIONE ======

void Gestionale::modificaStagione(){
	int azione;
	cout<<endl<<"Seleziona azione:"<<endl;
	cout<<"1) Aggiungi squadra"<<endl<<"2) Aggiungi partita"<<endl<<"3) Salva stagione"<<endl;
	cin>>azione;
}

// ==================== RICERCA STAGIONE ====================
Stagione* Gestionale::trovaStagione(int anno) {
    for (size_t i = 0; i < stagioni.size(); ++i) {
        if (stagioni[i]->getAnno() == anno)
            return stagioni[i].get();
    }
    return NULL;
}

// ==================== SELEZIONA STAGIONE ====================
void Gestionale::selezionaStagione() {
	int stag;
    fetchStagioni("database/stagioni.csv");
    cout<<endl;
    cout<<"Seleziona numero stagione da caricare:"<<endl;
    cin>>stag;
    cout<<"selezionata: "<<stag<<endl;
    caricaStagione("database/stagioni.csv", stag);
    
}

// ==================== LETTURA CSV ====================
vector<string> Gestionale::leggiDaFile(const string& path) {
    ifstream file(path.c_str());
    vector<string> righe;

    if (!file.is_open()) {
        cout << "?? Impossibile aprire " << path << endl;
        return righe;
    }

    string line;
    while (getline(file, line)) {
        if (!line.empty())
            righe.push_back(line);
    }
    file.close();
    return righe;
}

// ==================== SCRITTURA CSV ====================
void Gestionale::salvaSuFile(const string& path, const vector<string>& righe) {
    ofstream file(path.c_str());
    if (!file.is_open()) {
        throw runtime_error("Errore apertura file: " + path);
    }

    for (size_t i = 0; i < righe.size(); ++i)
        file << righe[i] << "\n";

    file.close();
}

// ==================== SPLIT RIGA CSV ====================
/*
prende una stringa tipo "Rugby Trenti, Via Verdi 21, 101"
e la restituisce:
	riga[0] = "Rugby Trento"
	riga[1] = "Via verdi 21"
	riga[2] = 101
	
	da far coincidere con la raccolta dati nostra
*/
vector<string> Gestionale::splitCSVLine(const string& line) {
    vector<string> tokens;
    stringstream ss(line);
    string cell;
    while (getline(ss, cell, ','))
        tokens.push_back(cell);
    return tokens;
}

// ==================== FETCH STAGIONI ====================
void Gestionale::fetchStagioni(const std::string& filename) {
    std::ifstream file(filename);
    std::string riga;
    int numeroRiga=1;
    std::cout <<endl<< "=== Elenco Stagioni ==="<<endl;
    bool prima = true;
    while (std::getline(file, riga)) {
        if (prima) { // salta intestazione
            prima = false;
            continue;
        }
        std::cout << numeroRiga<< ". " << riga << std::endl;
        ++numeroRiga;
    }
    file.close();
}

// ==================== SALVA STAGIONI ====================
void Gestionale::salvaStagioni() const{
    ofstream file(pathStagioni);
    for (const auto& sPtr : stagioni) file << sPtr->getAnno() << "\n";
    file.close();

}

// ==================== FETCH / SAVE SQUADRE ====================
void Gestionale::fetchSquadre(Stagione& stagione) {
    ifstream file(pathSquadre);
    string line;
    while (getline(file, line)) {
        vector<string> t = splitCSVLine(line);
        if (t.size() < 3) continue;
        string nome = t[0];
        string indirizzo = t[1];
        int id = atoi(t[2].c_str());
        stagione.addSquadra(unique_ptr<Squadra>(new Squadra(nome, indirizzo, id)));
    }
    file.close();
}

void Gestionale::salvaSquadre(const Stagione& stagione) const{
    ofstream file(pathSquadre);
    for (const auto& sPtr : stagione.getSquadre())
        file << sPtr->getNome() << "," << sPtr->getIndirizzo() << "," << sPtr->getId() << "\n";
    file.close();
}

// ==================== FETCH / SAVE GIOCATORI ====================
void Gestionale::fetchGiocatori(Squadra& squadra) {
    ifstream file(pathGiocatori);
    string line;
    while (getline(file, line)) {
        vector<string> t = splitCSVLine(line);
        if (t.size() < 5) continue;
        string nome = t[0];
        string cognome = t[1];
        int eta = atoi(t[2].c_str());
        string ruolo = t[3];
        int id = atoi(t[4].c_str());
        Giocatore g(nome, cognome, eta, ruolo, id);
        squadra.addGiocatore(g);
    }
    file.close();
}

void Gestionale::salvaGiocatori(const Squadra& squadra) const{
    ofstream file(pathGiocatori);
    for (const auto& g : squadra.getGiocatori())
        file << g.getNome() << "," << g.getCognome() << "," << g.getEta()
             << "," << g.getRuolo() << "," << g.getId() << "\n";
    file.close();
}

// ==================== FETCH / SAVE PARTITE ====================
void Gestionale::fetchPartite(Stagione& stagione) {
    ifstream file(pathPartite);
    string line;
    while (getline(file, line)) {
        vector<string> t = splitCSVLine(line);
        if (t.size() < 6) continue;

        int id = atoi(t[0].c_str());
        int data = atoi(t[1].c_str());
        int idLocali = atoi(t[2].c_str());
        int idOspiti = atoi(t[3].c_str());
        int ptLocali = atoi(t[4].c_str());
        int ptOspiti = atoi(t[5].c_str());

        // Trova squadre dalla stagione
        Squadra* locali = nullptr;
        Squadra* ospiti = nullptr;
        for (const auto& sPtr : stagione.getSquadre()) {
            if (sPtr->getId() == idLocali) locali = sPtr.get();
            if (sPtr->getId() == idOspiti) ospiti = sPtr.get();
        }
        if (!locali || !ospiti) continue;

        Partita p(id, data, *locali, *ospiti);
        p.setRisultato(ptLocali, ptOspiti);
        stagione.addPartita(p);
    }
    file.close();
}

void Gestionale::salvaPartite(const Stagione& stagione) const {
    ofstream file(pathPartite);
    for (const auto& p : stagione.getCalendario())
        file << p.getId() << "," << p.getData() << ","
             << p.getLocali().getId() << "," << p.getOspiti().getId() << ","
             << p.getPuntiLocali() << "," << p.getPuntiOspiti() << "\n";
    file.close();
}

