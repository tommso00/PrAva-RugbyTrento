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

//dovrebbe essere inutile sto if in quanto trovaStagione controlla stagioni caricate in RAM, non nel csv
    if (trovaStagione(anno) != NULL) {
        cout << "Stagione " << anno << " già esistente.\n";
        return;
    }

    //stagioni.push_back(unique_ptr<Stagione>(new Stagione(anno)));
    cout << "Stagione " << anno << " creata correttamente!\n";
    
    Stagione tempStagione(anno); // Oggetto temporaneo per il caricamento
    modificaStagione(tempStagione);
    
}

// ==== RECUPERA STAGIONE ===
//abbiamo un indicizzazione per riga fragile
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
	int lastSquadraId = getMaxSquadraId();  
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
		            	//aggiustare per aggiungere eta e ruolo da cin >>
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
	            aggiungiPartita(stagione);
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
	salvaPartite(stagione);
    
}

// === AGGIUNGI SQUADRA ===

std::unique_ptr<Squadra> Gestionale::aggiungiSquadra() {
	int newId = getMaxSquadraId() + 1;
    string nome, indirizzo;
    cout << "Nome squadra: ";
    cin >> nome;
    cout << "Indirizzo squadra: ";
    cin >> indirizzo;

    std::unique_ptr<Squadra> s1(new Squadra(newId, nome, indirizzo));
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
    fetchSquadre(tempStagione);
    for (auto& squadraPtr : tempStagione.getSquadre()) {
        fetchGiocatori(*squadraPtr);
    }
    fetchPartite(tempStagione);
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
    std::ifstream file("database/squadre.csv");
    if (!file.is_open()) {
        std::cerr << "Impossibile aprire il file squadre.csv" << std::endl;
        return;
    }

    std::string line;
    bool primaRiga = true;
    int stagioneAnno = stagione.getAnno(); // l'anno della stagione corrente (ID)

    while (std::getline(file, line)) {
        if (primaRiga) { // salta intestazione
            primaRiga = false;
            continue;
        }

        if (line.empty()) continue;

        // Dividi la riga in tokens
        std::vector<std::string> tokens = splitCSVLine(line);
        if (tokens.size() >= 15) {  // Nuova struttura completa
            int id = std::stoi(tokens[0]);
            int anno = std::stoi(tokens[1]);
            string nome = tokens[2];
            string indirizzo = tokens[3];
            int possessoPalla = std::stoi(tokens[4]);
            double territorio = std::stod(tokens[5]);
            int placcaggiTotali = std::stoi(tokens[6]);
            int metriGuadagnatiTotali = std::stoi(tokens[7]);
            int meteTotali = std::stoi(tokens[8]);
            int falliTotali = std::stoi(tokens[9]);
            int mischieVinte = std::stoi(tokens[10]);
            int mischiePerse = std::stoi(tokens[11]);
            int toucheVinte = std::stoi(tokens[12]);
            int touchePerse = std::stoi(tokens[13]);
            int punteggio = std::stoi(tokens[14]);

            // Se la squadra appartiene alla stagione corrente
            if (anno == stagioneAnno) {
                // Crea e aggiungi la squadra se non già presente
                auto squadraPtr = unique_ptr<Squadra> (new Squadra(id, nome, indirizzo));
                
                // Imposta tutti i nuovi campi
                squadraPtr->setPossessoPalla(possessoPalla);
                squadraPtr->setTerritorio(territorio);
                squadraPtr->setPlaccaggiTotali(placcaggiTotali);
                squadraPtr->setMetriGuadagnatiTotali(metriGuadagnatiTotali);
                squadraPtr->setMeteTotali(meteTotali);
                squadraPtr->setFalliTotali(falliTotali);
                squadraPtr->setMischieVinte(mischieVinte);
                squadraPtr->setMischiePerse(mischiePerse);
                squadraPtr->setToucheVinte(toucheVinte);
                squadraPtr->setTouchePerse(touchePerse);
                squadraPtr->setPunteggio(punteggio);
                
                stagione.addSquadra(std::move(squadraPtr));
            }
        }
    }

    file.close();
}



void Gestionale::salvaSquadre(const Stagione& stagione) const {
    // 1. Carica tutte le squadre esistenti
    std::vector<std::tuple<int, int, std::string, std::string, int, double, int, int, int, int, 
                          int, int, int, int, int>> squadreEsistenti;
    // (id, anno, nome, indirizzo, possesso_palla, territorio, placcaggi, metri, mete, falli,
    //  mischieVinte, mischiePerse, toucheVinte, touchePerse, punteggio)

    std::ifstream lettura("database/squadre.csv");
    std::string line;
    bool primaRiga = true;
    while (std::getline(lettura, line)) {
        if (primaRiga) { primaRiga = false; continue; } // Salta intestazione
        if (!line.empty()) {
            std::vector<std::string> tokens = splitCSVLine(line);
            if (tokens.size() >= 15) {  // Nuova struttura completa
                int id = std::stoi(tokens[0]);
                int anno = std::stoi(tokens[1]);
                std::string nome = tokens[2];
                std::string indirizzo = tokens[3];
                int possessoPalla = std::stoi(tokens[4]);
                double territorio = std::stod(tokens[5]);
                int placcaggiTotali = std::stoi(tokens[6]);
                int metriGuadagnatiTotali = std::stoi(tokens[7]);
                int meteTotali = std::stoi(tokens[8]);
                int falliTotali = std::stoi(tokens[9]);
                int mischieVinte = std::stoi(tokens[10]);
                int mischiePerse = std::stoi(tokens[11]);
                int toucheVinte = std::stoi(tokens[12]);
                int touchePerse = std::stoi(tokens[13]);
                int punteggio = std::stoi(tokens[14]);
                
                squadreEsistenti.emplace_back(id, anno, nome, indirizzo, possessoPalla, territorio,
                                            placcaggiTotali, metriGuadagnatiTotali, meteTotali, falliTotali,
                                            mischieVinte, mischiePerse, toucheVinte, touchePerse, punteggio);
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
        int possessoPalla = squadraPtr->getPossessoPalla();
        double territorio = squadraPtr->getTerritorio();
        int placcaggiTotali = squadraPtr->getPlaccaggiTotali();
        int metriGuadagnatiTotali = squadraPtr->getMetriGuadagnatiTotali();
        int meteTotali = squadraPtr->getMeteTotali();
        int falliTotali = squadraPtr->getFalliTotali();
        int mischieVinte = squadraPtr->getMischieVinte();
        int mischiePerse = squadraPtr->getMischiePerse();
        int toucheVinte = squadraPtr->getToucheVinte();
        int touchePerse = squadraPtr->getTouchePerse();
        int punteggio = squadraPtr->getPunteggio();

        bool presente = false;
        for (const auto& s : squadreEsistenti) {
            if (std::get<0>(s) == id && std::get<1>(s) == anno) {
                presente = true;
                break;
            }
        }
        if (!presente) {
            squadreEsistenti.emplace_back(id, anno, nome, indirizzo, possessoPalla, territorio,
                                        placcaggiTotali, metriGuadagnatiTotali, meteTotali, falliTotali,
                                        mischieVinte, mischiePerse, toucheVinte, touchePerse, punteggio);
        }
    }

    // 3. Riscrivi tutto il file
    std::ofstream scrittura("database/squadre.csv");
    if (!scrittura.is_open()) {
        throw std::runtime_error("Errore apertura file: database/squadre.csv");
    }
    scrittura << "squadra_id,stagione_anno,nome,indirizzo,possesso_palla,territorio,"
              << "placcaggi_totali,metri_guadagnati_totali,mete_totali,falli_totali,"
              << "mischie_vinte,mischie_perse,touche_vinte,touche_perse,punteggio_classifica\n";
    
    for (const auto& s : squadreEsistenti) {
        scrittura << std::get<0>(s) << "," << std::get<1>(s) << ","
                  << "\"" << std::get<2>(s) << "\"," << "\"" << std::get<3>(s) << "\","
                  << std::get<4>(s) << "," << std::get<5>(s) << ","
                  << std::get<6>(s) << "," << std::get<7>(s) << ","
                  << std::get<8>(s) << "," << std::get<9>(s) << ","
                  << std::get<10>(s) << "," << std::get<11>(s) << ","
                  << std::get<12>(s) << "," << std::get<13>(s) << ","
                  << std::get<14>(s) << "\n";
    }
    scrittura.close();
}



// ==================== FETCH / SAVE GIOCATORI ====================
void Gestionale::fetchGiocatori(Squadra& squadra) {
    std::ifstream file("database/giocatori.csv");
    if (!file.is_open()) {
        std::cerr << "Impossibile aprire il file giocatori.csv" << std::endl;
        return;
    }

    std::string line;
    bool primaRiga = true;
    int squadraId = squadra.getId(); // ID della squadra corrente

    while (std::getline(file, line)) {
        if (primaRiga) { // salta intestazione
            primaRiga = false;
            continue;
        }

        if (line.empty()) continue;

        std::vector<std::string> tokens = splitCSVLine(line);

        if (tokens.size() >= 14) {  // Nuova struttura completa
            int id = std::stoi(tokens[0]);
            int idSquadra = std::stoi(tokens[1]);
            std::string nome = tokens[2];
            std::string cognome = tokens[3];
            int eta = std::stoi(tokens[4]);
            std::string ruolo = tokens[5];
            int placcaggi = std::stoi(tokens[6]);
            int metriCorsi = std::stoi(tokens[7]);
            int mete = std::stoi(tokens[8]);
            int calciPiazzati = std::stoi(tokens[9]);
            int falliCommessi = std::stoi(tokens[10]);
            int offload = std::stoi(tokens[11]);
            int minutiGiocati = std::stoi(tokens[12]);
            int partiteGiocate = std::stoi(tokens[13]);

            if (idSquadra == squadraId) {
                Giocatore g(nome, cognome, eta, ruolo, id);
                
                // Imposta tutte le statistiche
                g.setPlaccaggi(placcaggi);
                g.setMetriCorsi(metriCorsi);
                g.setMete(mete);
                g.setCalciPiazzati(calciPiazzati);
                g.setFalliCommessi(falliCommessi);
                g.setOffload(offload);
                g.setMinutiGiocati(minutiGiocati);
                g.setPartiteGiocate(partiteGiocate);
                
                squadra.addGiocatore(g);
            }
        }
    }

    file.close();
}


void Gestionale::salvaGiocatori(const Squadra& squadra) const {
    // 1. Carica tutti i giocatori esistenti
    std::vector<std::tuple<int, int, std::string, std::string, int, std::string, 
                          int, int, int, int, int, int, int, int>> giocatoriEsistenti; 
    // (giocatore_id, squadra_id, nome, cognome, eta, ruolo, placcaggi, metriCorsi, 
    //  mete, calciPiazzati, falliCommessi, offload, minutiGiocati, partiteGiocate)

    std::ifstream lettura("database/giocatori.csv");
    std::string line;
    bool primaRiga = true;
    while (std::getline(lettura, line)) {
        if (primaRiga) { primaRiga = false; continue; } // Salta intestazione
        if (!line.empty()) {
            std::vector<std::string> tokens = splitCSVLine(line);
            if (tokens.size() >= 14) {
                int id = std::stoi(tokens[0]);
                int squadra_id = std::stoi(tokens[1]);
                std::string nome = tokens[2];
                std::string cognome = tokens[3];
                int eta = std::stoi(tokens[4]);
                std::string ruolo = tokens[5];
                int placcaggi = std::stoi(tokens[6]);
                int metriCorsi = std::stoi(tokens[7]);
                int mete = std::stoi(tokens[8]);
                int calciPiazzati = std::stoi(tokens[9]);
                int falliCommessi = std::stoi(tokens[10]);
                int offload = std::stoi(tokens[11]);
                int minutiGiocati = std::stoi(tokens[12]);
                int partiteGiocate = std::stoi(tokens[13]);
                
                giocatoriEsistenti.emplace_back(id, squadra_id, nome, cognome, eta, ruolo,
                                              placcaggi, metriCorsi, mete, calciPiazzati,
                                              falliCommessi, offload, minutiGiocati, partiteGiocate);
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
        int placcaggi = g.getPlaccaggi();
        int metriCorsi = g.getMetriCorsi();
        int mete = g.getMete();
        int calciPiazzati = g.getCalciPiazzati();
        int falliCommessi = g.getFalliCommessi();
        int offload = g.getOffload();
        int minutiGiocati = g.getMinutiGiocati();
        int partiteGiocate = g.getPartiteGiocate();

        bool presente = false;
        for (const auto& player : giocatoriEsistenti) {
            if (std::get<0>(player) == id && std::get<1>(player) == squadraId) {
                presente = true;
                break;
            }
        }
        if (!presente) {
            giocatoriEsistenti.emplace_back(id, squadraId, nome, cognome, eta, ruolo,
                                          placcaggi, metriCorsi, mete, calciPiazzati,
                                          falliCommessi, offload, minutiGiocati, partiteGiocate);
        }
    }

    // 3. Riscrivi tutto il file
    std::ofstream scrittura("database/giocatori.csv");
    if (!scrittura.is_open()) {
        throw std::runtime_error("Errore apertura file: database/giocatori.csv");
    }
    scrittura << "giocatore_id,squadra_id,nome,cognome,eta,ruolo,"
              << "placcaggi,metri_corsi,mete,calci_piazzati,"
              << "falli_commessi,offload,minuti_giocati,partite_giocate\n";
    
    for (const auto& g : giocatoriEsistenti) {
        scrittura << std::get<0>(g) << "," << std::get<1>(g) << ","
                  << std::get<2>(g) << "," << std::get<3>(g) << ","
                  << std::get<4>(g) << "," << std::get<5>(g) << ","
                  << std::get<6>(g) << "," << std::get<7>(g) << ","
                  << std::get<8>(g) << "," << std::get<9>(g) << ","
                  << std::get<10>(g) << "," << std::get<11>(g) << ","
                  << std::get<12>(g) << "," << std::get<13>(g) << "\n";
    }
    scrittura.close();
}


// ==================== FETCH / SAVE PARTITE ====================
void Gestionale::fetchPartite(Stagione& stagione) {
    std::ifstream file("database/partite.csv");
    if (!file.is_open()) {
        std::cerr << "Impossibile aprire partite.csv" << std::endl;
        return;
    }

    std::string line;
    bool primaRiga = true;
    int stagioneAnno = stagione.getAnno();

    // Accedi alle squadre esistenti della stagione per trovare i riferimenti giusti
    const auto& squadre = stagione.getSquadre();

    while (getline(file, line)) {
        if (primaRiga) { primaRiga = false; continue; }
        if (line.empty()) continue;

        auto tokens = splitCSVLine(line);
        if (tokens.size() >= 13) {  // Nuova struttura completa
            int id = std::stoi(tokens[0]);
            int anno = std::stoi(tokens[1]);
            int data = std::stoi(tokens[2]);
            int idLocali = std::stoi(tokens[3]);
            int idOspiti = std::stoi(tokens[4]);
            int ptLocali = std::stoi(tokens[5]);
            int ptOspiti = std::stoi(tokens[6]);
            int cartellinoRossoLoc = std::stoi(tokens[7]);
            int cartellinoRossoOsp = std::stoi(tokens[8]);
            int cartellinoGialloLoc = std::stoi(tokens[9]);
            int cartellinoGialloOsp = std::stoi(tokens[10]);
            double possessoLoc = std::stod(tokens[11]);
            double possessoOsp = std::stod(tokens[12]);

            if (anno == stagioneAnno) {
                Squadra* locali = nullptr;
                Squadra* ospiti = nullptr;
                for (const auto& sqPtr : squadre) {
                    if (sqPtr->getId() == idLocali) locali = sqPtr.get();
                    if (sqPtr->getId() == idOspiti) ospiti = sqPtr.get();
                }
                if (locali && ospiti) {
                    Partita p(id, data, *locali, *ospiti);
                    p.setRisultato(ptLocali, ptOspiti);
                    
                    // Imposta tutte le statistiche aggiuntive
                    p.setCartellinoRossoLoc(cartellinoRossoLoc);
                    p.setCartellinoRossoOsp(cartellinoRossoOsp);
                    p.setCartellinoGialloLoc(cartellinoGialloLoc);
                    p.setCartellinoGialloOsp(cartellinoGialloOsp);
                    p.setPossessoLoc(possessoLoc);
                    p.setPossessoOsp(possessoOsp);
                    
                    stagione.addPartita(p);
                }
            }
        }
    }
    file.close();
}


void Gestionale::salvaPartite(const Stagione& stagione) const {
    // 1. Carica tutte le partite esistenti
    std::vector<std::tuple<int, int, int, int, int, int, int, int, int, int, int, double, double>> partiteEsistenti;
    // (partita_id, stagione_anno, data, id_locali, id_ospiti, pt_locali, pt_ospiti,
    //  cartellino_rosso_loc, cartellino_rosso_osp, cartellino_giallo_loc, cartellino_giallo_osp,
    //  possesso_loc, possesso_osp)
    
    std::ifstream lettura("database/partite.csv");
    std::string line;
    bool primaRiga = true;
    while (std::getline(lettura, line)) {
        if (primaRiga) { primaRiga = false; continue; }
        if (!line.empty()) {
            auto tokens = splitCSVLine(line);
            if (tokens.size() >= 13) {
                int id = std::stoi(tokens[0]);
                int anno = std::stoi(tokens[1]);
                int data = std::stoi(tokens[2]);
                int idLocali = std::stoi(tokens[3]);
                int idOspiti = std::stoi(tokens[4]);
                int ptLocali = std::stoi(tokens[5]);
                int ptOspiti = std::stoi(tokens[6]);
                int cartellinoRossoLoc = std::stoi(tokens[7]);
                int cartellinoRossoOsp = std::stoi(tokens[8]);
                int cartellinoGialloLoc = std::stoi(tokens[9]);
                int cartellinoGialloOsp = std::stoi(tokens[10]);
                double possessoLoc = std::stod(tokens[11]);
                double possessoOsp = std::stod(tokens[12]);
                
                partiteEsistenti.emplace_back(id, anno, data, idLocali, idOspiti, ptLocali, ptOspiti,
                                            cartellinoRossoLoc, cartellinoRossoOsp,
                                            cartellinoGialloLoc, cartellinoGialloOsp,
                                            possessoLoc, possessoOsp);
            }
        }
    }
    lettura.close();

    // 2. Aggiungi tutte le partite della stagione, solo se non già presenti (controllo su id e anno)
    for (const auto& p : stagione.getCalendario()) {
        int id = p.getId();
        int anno = stagione.getAnno();
        int data = p.getData();
        int idLocali = p.getLocali().getId();
        int idOspiti = p.getOspiti().getId();
        int ptLocali = p.getPuntiLocali();
        int ptOspiti = p.getPuntiOspiti();
        int cartellinoRossoLoc = p.getCartellinoRossoLoc();
        int cartellinoRossoOsp = p.getCartellinoRossoOsp();
        int cartellinoGialloLoc = p.getCartellinoGialloLoc();
        int cartellinoGialloOsp = p.getCartellinoGialloOsp();
        double possessoLoc = p.getPossessoLoc();
        double possessoOsp = p.getPossessoOsp();

        bool presente = false;
        for (const auto& pe : partiteEsistenti) {
            if (std::get<0>(pe) == id && std::get<1>(pe) == anno) {
                presente = true;
                break;
            }
        }
        if (!presente) {
            partiteEsistenti.emplace_back(id, anno, data, idLocali, idOspiti, ptLocali, ptOspiti,
                                        cartellinoRossoLoc, cartellinoRossoOsp,
                                        cartellinoGialloLoc, cartellinoGialloOsp,
                                        possessoLoc, possessoOsp);
        }
    }

    // 3. Riscrivi tutto il file
    std::ofstream scrittura("database/partite.csv");
    if (!scrittura.is_open()) {
        throw std::runtime_error("Errore apertura file: database/partite.csv");
    }
    scrittura << "partita_id,stagione_anno,data,id_locali,id_ospiti,pt_locali,pt_ospiti,"
              << "cartellino_rosso_loc,cartellino_rosso_osp,cartellino_giallo_loc,cartellino_giallo_osp,"
              << "possesso_loc,possesso_osp\n";
    
    for (const auto& p : partiteEsistenti) {
        scrittura << std::get<0>(p) << "," << std::get<1>(p) << "," << std::get<2>(p) << ","
                  << std::get<3>(p) << "," << std::get<4>(p) << "," << std::get<5>(p) << ","
                  << std::get<6>(p) << "," << std::get<7>(p) << "," << std::get<8>(p) << ","
                  << std::get<9>(p) << "," << std::get<10>(p) << "," << std::get<11>(p) << ","
                  << std::get<12>(p) << "\n";
    }
    scrittura.close();
}


// === AGGIUNGI PARTITA ===
void Gestionale::aggiungiPartita(Stagione& stagione) {
    int idPartita = stagione.getCalendario().size() + 1; // ID partita incrementale
    int dataPartita;
    int idSquadraLocale, idSquadraOspite;
    int puntiLocali, puntiOspiti;

    // Mostra elenco squadre per selezionare
    std::cout << "Elenco squadre disponibili:\n";
    for (const auto& squadraPtr : stagione.getSquadre()) {
        std::cout << "ID: " << squadraPtr->getId() << " - " << squadraPtr->getNome() << std::endl;
    }

    // Input dati partita
    std::cout << "Inserisci data della partita (formato numerico e.g. AAAAMMGG): ";
    std::cin >> dataPartita;

    std::cout << "Inserisci ID squadra locale: ";
    std::cin >> idSquadraLocale;
    std::cout << "Inserisci ID squadra ospite: ";
    std::cin >> idSquadraOspite;

    // Trova puntatori alle squadre dalla stagione
    Squadra* locali = nullptr;
    Squadra* ospiti = nullptr;

    for (const auto& squadraPtr : stagione.getSquadre()) {
        if (squadraPtr->getId() == idSquadraLocale) locali = squadraPtr.get();
        if (squadraPtr->getId() == idSquadraOspite) ospiti = squadraPtr.get();
    }

    if (!locali || !ospiti) {
        std::cout << "Squadre non trovate. Operazione annullata.\n";
        return;
    }

    std::cout << "Inserisci punti squadra locale: ";
    std::cin >> puntiLocali;
    std::cout << "Inserisci punti squadra ospite: ";
    std::cin >> puntiOspiti;

    // Crea partita e setta risultato
    Partita nuovaPartita(idPartita, dataPartita, *locali, *ospiti);
    nuovaPartita.setRisultato(puntiLocali, puntiOspiti);

    // Aggiungi la partita alla stagione
    stagione.addPartita(nuovaPartita);

    std::cout << "Partita aggiunta con successo.\n";
}


// METODO AUSILIARIO

int Gestionale::getMaxSquadraId() const {
    std::ifstream file("database/squadre.csv");
    if (!file.is_open()) return 0;

    std::string line;
    bool primaRiga = true;
    int maxId = 0;
    while (std::getline(file, line)) {
        if (primaRiga) { primaRiga = false; continue; }
        if (line.empty()) continue;

        std::vector<std::string> tokens = splitCSVLine(line);
        if (tokens.size() >= 4) {
            int id = std::stoi(tokens[0]);
            if (id > maxId) maxId = id;
        }
    }
    file.close();
    return maxId;
}


