#include "Gestionale.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <memory>


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
            case 1: //fetchStagioni("database/squadre_girone_rugby_trento.csv"); break;
            case 2: //creaStagione(); break;
            case 3: //salvaStagioni(); break;
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

    //stagioni.push_back(unique_ptr<Stagione>(new Stagione(anno)));
    cout << "Stagione " << anno << " creata correttamente!\n";
    
    Stagione tempStagione(anno); // Oggetto temporaneo per il caricamento
    modificaStagione(tempStagione);
    
}

// ==== CARICA STAGIONE ===
int Gestionale::recuperaStagione(const std::string& filename, int stagione) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Errore apertura file: " << filename << std::endl;
        return 0;
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
            std::cout << "Riga " << stagione << ": " << riga << std::endl;
            int anno = std::stoi(riga);
            //outStagione = Stagione(anno); // costruiamo la stagione con l'anno letto
            //std::cout << "Stagione " << outStagione.getAnno() << " caricata correttamente!" << std::endl;
            return anno;
        }
    }

    std::cout << "Riga " << stagione << " non trovata nel file." << std::endl;
    return 0;
}

// ====== MODIFICA STAGIONE ======

void Gestionale::modificaStagione(Stagione& stagione) {
	int lastSquadraId = 0;  
	for (const auto& s : stagione.getSquadre()) {
	    if (s->getId() > lastSquadraId) lastSquadraId = s->getId();
	}

    int azione, azgioc;
    int controllo=0;
    int c=0;
    string nome, cognome, ruolo;
    int eta;
	while(controllo==0){
		cout << endl << "Seleziona azione:" << endl;
	    cout << "1) Aggiungi squadra" << endl << "2) Aggiungi partita" << endl << "3) Stampa Stagione" << endl;
	    cin >> azione;
		switch (azione) {
	        case 1: {
	        	while(c==0){
	                 // Chiamata a aggiungiSquadra che ritorna unique_ptr
		            auto squadraPtr = aggiungiSquadra();
		            squadraPtr->setId(++lastSquadraId);  // assegna ID unico
		            //===========AGGIUNGERE LISTA GIOCATORI PRIMA DI AGGIUNGERE ALTRE SQUADRE 
		            cout<< "Vuoi Aggiungere Giocatori? 0=si / 1=no"<<endl;
		            cin>>azgioc;
		            int lastGiocatoreId = 0;  
					if (!squadraPtr->getGiocatori().empty()) {
					    for (const auto& g : squadraPtr->getGiocatori()) {
					        if (g.getId() > lastGiocatoreId) lastGiocatoreId = g.getId();
					    }
					}
		            while(azgioc==0){
		            	cout<<"Nome: ";
		            	cin>>nome;
		            	cout<<"Cognome: ";
		            	cin>>cognome;
		            	Giocatore g1(nome, cognome, 28, "Mediano", ++lastGiocatoreId);
		            	squadraPtr->addGiocatore(g1);
			            cout<< "Vuoi Aggiungere Giocatori? 0=si / 1=no"<<endl;
			            cin>>azgioc;
					}	            
		            
		            // Aggiunta della squadra alla stagione
		            stagione.addSquadra(move(squadraPtr));
		            
	
					cout<<"Vuoi aggiungere un'altra squadra?  0=si / 1=no"<<endl;
					cin>>c;	
				}
				//cout<<stagione;
	
	            break;
	        }
	        case 2:
	            // aggiungiPartita(stagione);
	            break;
	        case 3:
	            cout<<stagione;
	            break;
	        default:
	            cout << "Azione non valida." << endl;
	            break;
    	}
    	cout<<"Vuoi modificare ancora?  0=si / 1=no"<<endl;
    	cin>>controllo;
	}
	salvaStagioni(stagione);
	salvaSquadre(stagione);
	for (const auto& squadra : stagione.getSquadre()) {
	    salvaGiocatori(*squadra);
	}
    
}

// === AGGIUNGI SQUADRA ===

std::unique_ptr<Squadra> Gestionale::aggiungiSquadra() {
    string nome, indirizzo;
    cout << "Nome squadra: ";
    cin >> nome;
    cout << "Indirizzo squadra: ";
    cin >> indirizzo;

    std::unique_ptr<Squadra> s1(new Squadra(nome, indirizzo));
    return s1;
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
    fetchStagioni("database/stagioni.csv");
    
    int stag;
    std::cout << std::endl << "Seleziona numero stagione da caricare:" << std::endl;
    std::cin >> stag;

    std::cout << "Selezionata: " << stag << std::endl;

    Stagione tempStagione(recuperaStagione("database/stagioni.csv", stag)); // Oggetto temporaneo per il caricamento
    
    modificaStagione(tempStagione);
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
vector<string> Gestionale::splitCSVLine(const string& line)const {
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
void Gestionale::salvaStagioni(const Stagione& nuovaStagione)  {
    // 1. Ricarica tutte le stagioni esistenti
    vector<int> anni;
    
    ifstream lettura("database/stagioni.csv");
    string line;
    bool primaRiga = true;
    while (getline(lettura, line)) {
        if (primaRiga) { primaRiga = false; continue; } // salta intestazione
        if (!line.empty()) {
            anni.push_back(stoi(line));
        }
    }
    lettura.close();

    // 2. Aggiungi la nuova stagione se non c'è già
    int annoNuova = nuovaStagione.getAnno();
    if (find(anni.begin(), anni.end(), annoNuova) == anni.end()) {
        anni.push_back(annoNuova);
    }
    
    // 3. Riscrivi tutto il file con tutte le stagioni (inclusa la nuova)
    ofstream scrittura("database/stagioni.csv");
    if (!scrittura.is_open()) {
        throw runtime_error("Errore apertura file: database/stagioni.csv");
    }
    scrittura << "anno\n"; // intestazione
    for (int anno : anni) {
        scrittura << anno << "\n";
    }
    scrittura.close();
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
        stagione.addSquadra(unique_ptr<Squadra>(new Squadra(nome, indirizzo)));
    }
    file.close();
}

void Gestionale::salvaSquadre(const Stagione& stagione) const {
    // 1. Carica tutte le squadre esistenti
    std::vector<std::tuple<int, int, std::string, std::string>> squadreEsistenti; // (id, stagione_anno, nome, indirizzo)

    std::ifstream lettura("database/squadre.csv");
    std::string line;
    bool primaRiga = true;
    while (std::getline(lettura, line)) {
        if (primaRiga) { primaRiga = false; continue; } // Salta intestazione
        if (!line.empty()) {
            std::vector<std::string> tokens = splitCSVLine(line);
            if (tokens.size() >= 4) {
                int id = std::stoi(tokens[0]);
                int anno = std::stoi(tokens[1]);
                std::string nome = tokens[2];
                std::string indirizzo = tokens[3];
                squadreEsistenti.emplace_back(id, anno, nome, indirizzo);
            }
        }
    }
    lettura.close();

    // 2. Aggiungi le squadre della stagione passata come parametro che non sono già presenti
    for (const auto& squadraPtr : stagione.getSquadre()) {
        int id = squadraPtr->getId();
        int anno = stagione.getAnno();
        std::string nome = squadraPtr->getNome();
        std::string indirizzo = squadraPtr->getIndirizzo();

        bool presente = false;
        for (const auto& s : squadreEsistenti) {
            if (std::get<0>(s) == id && std::get<1>(s) == anno) {
                presente = true;
                break;
            }
        }
        if (!presente) {
            squadreEsistenti.emplace_back(id, anno, nome, indirizzo);
        }
    }

    // 3. Riscrivi tutto il file
    std::ofstream scrittura("database/squadre.csv");
    if (!scrittura.is_open()) {
        throw std::runtime_error("Errore apertura file: database/squadre.csv");
    }
    scrittura << "squadra_id,stagione_anno,nome,indirizzo\n";
    for (const auto& s : squadreEsistenti) {
        scrittura << std::get<0>(s) << "," << std::get<1>(s) << ","
                  << std::get<2>(s) << "," << std::get<3>(s) << "\n";
    }
    scrittura.close();
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

void Gestionale::salvaGiocatori(const Squadra& squadra) const {
    // 1. Carica tutti i giocatori esistenti
    std::vector<std::tuple<int, int, std::string, std::string, int, std::string>> giocatoriEsistenti; 
    // (giocatore_id, squadra_id, nome, cognome, eta, ruolo)

    std::ifstream lettura("database/giocatori.csv");
    std::string line;
    bool primaRiga = true;
    while (std::getline(lettura, line)) {
        if (primaRiga) { primaRiga = false; continue; } // Salta intestazione
        if (!line.empty()) {
            std::vector<std::string> tokens = splitCSVLine(line);
            if (tokens.size() >= 6) {
                int id = std::stoi(tokens[0]);
                int squadra_id = std::stoi(tokens[1]);
                std::string nome = tokens[2];
                std::string cognome = tokens[3];
                int eta = std::stoi(tokens[4]);
                std::string ruolo = tokens[5];
                giocatoriEsistenti.emplace_back(id, squadra_id, nome, cognome, eta, ruolo);
            }
        }
    }
    lettura.close();

    // 2. Aggiungi i giocatori della squadra passata come parametro se non sono già presenti
    int squadraId = squadra.getId();
    for (const auto& g : squadra.getGiocatori()) {
        int id = g.getId();
        std::string nome = g.getNome();
        std::string cognome = g.getCognome();
        int eta = g.getEta();
        std::string ruolo = g.getRuolo();

        bool presente = false;
        for (const auto& player : giocatoriEsistenti) {
            if (std::get<0>(player) == id && std::get<1>(player) == squadraId) {
                presente = true;
                break;
            }
        }
        if (!presente) {
            giocatoriEsistenti.emplace_back(id, squadraId, nome, cognome, eta, ruolo);
        }
    }

    // 3. Riscrivi tutto il file
    std::ofstream scrittura("database/giocatori.csv");
    if (!scrittura.is_open()) {
        throw std::runtime_error("Errore apertura file: database/giocatori.csv");
    }
    scrittura << "giocatore_id,squadra_id,nome,cognome,eta,ruolo\n";
    for (const auto& g : giocatoriEsistenti) {
        scrittura << std::get<0>(g) << "," << std::get<1>(g) << ","
                  << std::get<2>(g) << "," << std::get<3>(g) << ","
                  << std::get<4>(g) << "," << std::get<5>(g) << "\n";
    }
    scrittura.close();
}



// ==================== FETCH / SAVE PARTITE ====================
void Gestionale::fetchPartite(Stagione& stagione) {
    /*ifstream file(pathPartite);
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
    file.close();*/
}

void Gestionale::salvaPartite(const Stagione& stagione) const {
    /*ofstream file(pathPartite);
    for (const auto& p : stagione.getCalendario())
        file << p.getId() << "," << p.getData() << ","
             << p.getLocali().getId() << "," << p.getOspiti().getId() << ","
             << p.getPuntiLocali() << "," << p.getPuntiOspiti() << "\n";
    file.close();*/
}

