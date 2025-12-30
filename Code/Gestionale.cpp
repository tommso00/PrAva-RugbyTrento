#include "Gestionale.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <memory>
#include <algorithm>
#include <numeric>
#include <thread>
#include "Statistiche.h"
#include "CSVManager.h"

using namespace std;

/**
 * @brief Crea nuova stagione interattivamente.
 * 
 * Verifica unicità anno e avvia modalità modifica.
 */
void Gestionale::creaStagione() {
    int anno;
    cout << "Inserisci anno stagione: ";
    cin >> anno;

    if (trovaStagione(anno) != nullptr) {
        cout << "Stagione " << anno << " già esistente.\n";
        return;
    }

    cout << "Stagione " << anno << " creata correttamente!\n";
    
    auto stagionePtr = std::unique_ptr<Stagione>(new Stagione(anno));
    Stagione* stagioneRaw = stagionePtr.get();
    
    stagioni.push_back(std::move(stagionePtr));
    modificaStagione(*stagioneRaw);
}

int Gestionale::recuperaStagione(const std::string& filename, int numeroRiga) {
    CSVManager::FileGuard file(filename);
    if (!file.inputOpen()) {
        std::cerr << "Errore apertura file: " << filename << std::endl;
        return 0;
    }

    std::string riga;
    int numeroRigaTrovata = 1;  // ? Inizia da 1 come fetchStagioni()
    bool intestazioneSaltata = false;

    while (std::getline(file.getInput(), riga)) {
        if (!intestazioneSaltata) {
            intestazioneSaltata = true;
            continue;
        }
        
        if (numeroRigaTrovata == numeroRiga) {  // ? Controllo diretto
            std::string annoPulito = trim(riga);
            try {
                int anno = std::stoi(annoPulito);
                std::cout << "Riga " << numeroRiga << ": " << riga 
                          << " ? Anno caricato: " << anno << std::endl;
                return anno;
            } catch (const std::exception& e) {
                std::cerr << "[WARN] Errore parsing riga " << numeroRiga 
                          << ": " << e.what() << std::endl;
                return 0;
            }
        }
        numeroRigaTrovata++;  // ? Incrementa DOPO controllo
    }
    
    std::cout << "Riga " << numeroRiga << " non trovata nel file." << std::endl;
    return 0;
}



/**
 * @brief Modalità interattiva modifica/estensione stagione.
 * @param stagione Stagione da modificare.
 * 
 * Menu completo: squadre, partite, statistiche STL.
 */
void Gestionale::modificaStagione(Stagione& stagione) {
    int lastSquadraId = getMaxSquadraId();  
    for (const auto& s : stagione.getSquadre()) {
        if (s->getId() > lastSquadraId) lastSquadraId = s->getId();
    }

    int azione, azgioc, azstaff, controllo = 0, c = 0;
    string nome, cognome, ruolo;
    int eta;
    
    while(controllo == 0) {
        cout << endl << "Seleziona azione:" << endl;
        cout << "1) Aggiungi squadra" << endl 
             << "2) Aggiungi partita" << endl 
             << "3) Stampa Stagione" << endl 
             << "4) Statistiche Avanzate (STL)" << endl
			 << "5) ESCI"<<endl;
        cin >> azione;
        
        switch (azione) {
            case 1: {
                while(c == 0) {
                    auto squadraPtr = aggiungiSquadra();
                    squadraPtr->setId(++lastSquadraId);
                    
                    cout << "Vuoi Aggiungere Staff? 0=si / 1=no" << endl;
                    cin >> azstaff;
                    
                    while(azstaff == 0) {
                        cout << "\n=== AGGIUNGI MEMBRO STAFF ===\n";
                        cout << "Nome: "; cin >> nome;
                        cout << "Cognome: "; cin >> cognome;
                        cout << "Eta: "; cin >> eta;
                                            cout << "Ruolo (0=ALLENATORE, 1=AIUTANTE, 2=DS, 3=SEGRETERIA, 4=ALLENATORE_MINI): ";
                    int ruoloInt;
                    cin >> ruoloInt;
                    
                    RuoloStaff ruoloStaff = static_cast<RuoloStaff>(ruoloInt);
                    Staff s1(nome, cognome, eta, ruoloStaff);
                    squadraPtr->addStaff(std::move(s1));
                    
                    cout << "Vuoi Aggiungere altro Staff? 0=si / 1=no" << endl;
                    cin >> azstaff;
                }
                
                cout << "Vuoi Aggiungere Giocatori? 0=si / 1=no" << endl;
                cin >> azgioc;
                int lastGiocatoreId = 0;
                
                if (!squadraPtr->getGiocatori().empty()) {
                    for (const auto& g : squadraPtr->getGiocatori()) {
                        if (g.getId() > lastGiocatoreId) lastGiocatoreId = g.getId();
                    }
                }
                
                while(azgioc == 0) {
                    cout << "Nome: "; cin >> nome;
                    cout << "Cognome: "; cin >> cognome;
                    cout << "Eta: "; cin >> eta;
                    cout << "Ruolo: "; cin >> ruolo;
                    
                    Giocatore g1(nome, cognome, eta, ruolo, ++lastGiocatoreId);
                    squadraPtr->addGiocatore(g1);
                    
                    cout << "Vuoi Aggiungere Giocatori? 0=si / 1=no" << endl;
                    cin >> azgioc;
                }	            
                
                stagione.addSquadra(std::move(squadraPtr));
                cout << "Vuoi aggiungere un'altra squadra? 0=si / 1=no" << endl;
                cin >> c;	
            	}
            break;
        	}
            case 2:
                aggiungiPartita(stagione);
                break;
                
            case 3:
                cout << stagione;
                break;
                
            
            case 4: {
                int sceltaStats;
                std::cout << "\n+----------------------------------------------------+\n";
                std::cout << "¦       STATISTICHE AVANZATE (Algoritmi STL)        ¦\n";
                std::cout << "+----------------------------------------------------+\n";
                std::cout << "\n1) Statistiche per Squadra (giocatori)\n";
                std::cout << "2) Report Completo Stagione\n";
                std::cout << "Scelta: ";
                std::cin >> sceltaStats;
                
                if (sceltaStats == 1) {
                    for (const auto& sq : stagione.getSquadre()) {
                        Statistiche::stampaReportSquadra(*sq);
                    }
                } else if (sceltaStats == 2) {
                    Statistiche::stampaReportStagione(stagione);
                } else {
                    std::cout << "Scelta non valida.\n";
                }
                break;
            }
            
            case 5:
            	cout<<endl<<"Uscito!"<<endl;
            	break;
            
            default:
                cout << "Azione non valida." << endl;
                break;
        }
        cout << "Vuoi modificare ancora? 0=si / 1=no" << endl;
        cin >> controllo;
    }

    salvaParallel(stagione);
}

/**
 * @brief Crea nuova squadra con ID sequenziale.
 * @return unique_ptr<Squadra> pronta per l'uso.
 */
std::unique_ptr<Squadra> Gestionale::aggiungiSquadra() {
	int newId = getMaxSquadraId() + 1;
	string nome, indirizzo;
	cout << "Nome squadra: ";
	cin >> nome;
	cout << "Indirizzo squadra: ";
	cin >> indirizzo;
	
	return std::unique_ptr<Squadra>(new Squadra(newId, nome, indirizzo));
}

/**
 * @brief Cerca stagione per anno usando STL find_if + lambda.
 * @param anno Anno da cercare.
 * @return Puntatore a Stagione o nullptr.
 */
Stagione* Gestionale::trovaStagione(int anno) {
    auto confrontaAnno = [anno](const std::unique_ptr<Stagione>& s) {
        return s->getAnno() == anno;
    };
    
    auto it = std::find_if(stagioni.begin(), stagioni.end(), confrontaAnno);
    return (it != stagioni.end()) ? it->get() : nullptr;
}

void Gestionale::selezionaStagione() {
    fetchStagioni(pathStagioni);
    
    int stag;
    std::cout << std::endl << "Seleziona numero stagione da caricare:" << std::endl;
    std::cin >> stag;

    int anno = recuperaStagione(pathStagioni, stag);
    if(anno == 0) return;
    
    // PASSO 1: Crea stagione VUOTA
    auto stagionePtr = std::unique_ptr<Stagione>(new Stagione(anno));
    
    // PASSO 2: Carica SQUADRE
    fetchSquadre(*stagionePtr);
    
    // PASSO 3: Carica GIOCATORI/STAFF
    for (auto& squadraPtr : stagionePtr->getSquadre()) {
        fetchGiocatori(*squadraPtr);
        fetchStaff(*squadraPtr);
    }
    
    // PASSO 4: Carica PARTITE
    fetchPartite(*stagionePtr);
    
    // ? FIX: Salva pointer PRIMA del move
    Stagione* rawPtr = stagionePtr.get();
    stagioni.push_back(std::move(stagionePtr));
    modificaStagione(*rawPtr);  // Usa rawPtr valido!
}


/**
 * @brief Split riga CSV su virgola.
 * @param line Riga CSV grezza.
 * @return Vettore token splittati.
 */
vector<string> Gestionale::splitCSVLine(const string& line) const {
    return CSVManager::splitCSVLine(line);
}

/**
 * @brief Visualizza elenco stagioni da CSV.
 * @param filename File stagioni.csv.
 */
void Gestionale::fetchStagioni(const std::string& filename) {
    CSVManager::FileGuard file(filename);
    
    if (!file.inputOpen()) {
        std::cout << "[ERRORE] Impossibile aprire " << filename << std::endl;
        return;
    }
    
    std::string riga;
    int numeroRiga = 1;
    std::cout << std::endl << "=== Elenco Stagioni ===" << std::endl;
    bool primaRiga = true;
    
    while (std::getline(file.getInput(), riga)) {
        if (primaRiga) { 
            primaRiga = false; 
            continue; 
        }
        std::cout << numeroRiga << ". " << riga << std::endl;
        ++numeroRiga;
    }
    // File chiude automaticamente grazie a RAII!
}


/**
 * @brief Salva stagioni uniche (merge con esistenti).
 * @param nuovaStagione Stagione da salvare.
 */
void Gestionale::salvaStagioni(const Stagione& nuovaStagione) {
    // Parser per estrarre anno da riga CSV (solo numero)
    auto parseAnno = [](const std::string& line) -> int {
        return std::stoi(line);
    };
    
    // Carica anni esistenti dal CSV
    auto anni = CSVManager::caricaRighe<int>(pathStagioni, parseAnno);
    
    // Aggiungi anno se non esiste (merge)
    int annoNuova = nuovaStagione.getAnno();
    if (std::find(anni.begin(), anni.end(), annoNuova) == anni.end()) {
        anni.push_back(annoNuova);
    }
    
    // Formatter per scrivere anno come stringa
    auto formatAnno = [](int anno) -> std::string {
        return std::to_string(anno);
    };
    
    // Salva con header "anno"
    CSVManager::salvaRighe(pathStagioni, "anno", anni, formatAnno);
}


void Gestionale::fetchSquadre(Stagione& stagione) {
    int stagioneAnno = stagione.getAnno();
    auto parseSquadra = [&stagione, stagioneAnno, this](const std::string& line) -> int {
        auto tokens = CSVManager::splitCSVLine(line);
        if (tokens.size() < 15) return 0;
        
        try {
            std::string annoStr = trim(tokens[1]);
            int anno = std::stoi(annoStr);
            if (anno != stagioneAnno) return 0;
            
            int id = std::stoi(trim(tokens[0]));
            auto squadraPtr = std::unique_ptr<Squadra>(new Squadra(id, tokens[2], tokens[3]));
            
            squadraPtr->setPossessoPalla(std::stoi(trim(tokens[4])));
            squadraPtr->setTerritorio(std::stod(trim(tokens[5])));
            squadraPtr->setPlaccaggiTotali(std::stoi(trim(tokens[6])));
            squadraPtr->setMetriGuadagnatiTotali(std::stoi(trim(tokens[7])));
            squadraPtr->setMeteTotali(0);
            squadraPtr->setFalliTotali(std::stoi(trim(tokens[9])));
            squadraPtr->setMischieVinte(std::stoi(trim(tokens[10])));
            squadraPtr->setMischiePerse(std::stoi(trim(tokens[11])));
            squadraPtr->setToucheVinte(std::stoi(trim(tokens[12])));
            squadraPtr->setTouchePerse(std::stoi(trim(tokens[13])));
            squadraPtr->setPunteggio(std::stoi(trim(tokens[14])));
            
            stagione.addSquadra(std::move(squadraPtr));
            return 1;
        } catch (const std::exception& e) {
            std::cerr << "[WARN] Riga CSV ignorata (squadre): " << line.substr(0, 50) 
                      << "... ? " << e.what() << std::endl;
            return 0;
        }
    };
    
    try {
        CSVManager::caricaRighe<int>(pathSquadre, parseSquadra, false);
        // Reset punteggi dopo caricamento
        for (auto& squadraPtr : stagione.getSquadre()) {
            squadraPtr->setPunteggio(0);
        }
        std::cout << "Caricate " << stagione.getSquadre().size() << " squadre per 2024." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[ERRORE] fetchSquadre: " << e.what() << std::endl;
    }
}


/**
 * @brief Salva squadre della stagione (merge con esistenti).
 * @param stagione Stagione contenente squadre da salvare.
 */
void Gestionale::salvaSquadre(const Stagione& stagione) {
    auto parseSquadra = [](const std::string& line) {
        return CSVManager::SquadraData::fromCSV(CSVManager::splitCSVLine(line));
    };

    std::vector<CSVManager::SquadraData> squadreData =
        CSVManager::caricaRighe<CSVManager::SquadraData>(pathSquadre, parseSquadra);

    int annoStagione = stagione.getAnno();

    squadreData.erase(
        std::remove_if(squadreData.begin(), squadreData.end(),
            [annoStagione](const CSVManager::SquadraData& sd) {
                return sd.anno == annoStagione;
            }),
        squadreData.end()
    );

    for (const auto& sq : stagione.getSquadre()) {
        CSVManager::SquadraData sd{
            sq->getId(), annoStagione,
            sq->getNome(), sq->getIndirizzo(),
            sq->getPossessoPalla(), sq->getTerritorio(),
            sq->getPlaccaggiTotali(), sq->getMetriGuadagnatiTotali(), 
            sq->getMeteTotali(), sq->getFalliTotali(),
            sq->getMischieVinte(), sq->getMischiePerse(), 
            sq->getToucheVinte(), sq->getTouchePerse(),
            sq->getPunteggio()
        };
        squadreData.push_back(sd);
    }

    CSVManager::salvaRighe(pathSquadre, 
        "squadra_id,stagione_anno,nome,indirizzo,possesso_palla,territorio,"
        "placcaggi_totali,metri_guadagnati_totali,mete_totali,falli_totali,"
        "mischie_vinte,mischie_perse,touche_vinte,touche_perse,punteggio_classifica",
        squadreData, [](const CSVManager::SquadraData& sd) { return sd.toCSV(); });
}


/**
 * @brief Carica giocatori della squadra da CSV.
 * @param squadra Squadra da popolare.
 */
void Gestionale::fetchGiocatori(Squadra& squadra) {
    auto parseGiocatore = [this, &squadra](const std::string& line) -> int {
        auto tokens = CSVManager::splitCSVLine(line);
        if (tokens.size() < 14) return 0;
        
        try {
            int idSquadra = std::stoi(trim(tokens[1]));
            if (idSquadra != squadra.getId()) return 0;
            
            Giocatore g(trim(tokens[2]), trim(tokens[3]), 
                       std::stoi(trim(tokens[4])), trim(tokens[5]), 
                       std::stoi(trim(tokens[0])));
            g.setPlaccaggi(std::stoi(trim(tokens[6])));
            g.setMetriCorsi(std::stoi(trim(tokens[7])));
            g.setMete(std::stoi(trim(tokens[8])));
            g.setCalciPiazzati(std::stoi(trim(tokens[9])));
            g.setFalliCommessi(std::stoi(trim(tokens[10])));
            g.setOffload(std::stoi(trim(tokens[11])));
            g.setMinutiGiocati(std::stoi(trim(tokens[12])));
            g.setPartiteGiocate(std::stoi(trim(tokens[13])));
            
            squadra.addGiocatore(g);
            return 1;
        } catch (const std::exception& e) {
            // Silenzioso: ignora righe malformate
            return 0;
        }
    };
    
    try {
        CSVManager::caricaRighe<int>(pathGiocatori, parseGiocatore);
    } catch (const std::exception& e) {
        std::cerr << "[WARN] fetchGiocatori(" << squadra.getId() << "): " << e.what() << std::endl;
    }
}



/**
 * @brief Salva giocatori della squadra (merge con esistenti).
 * @param squadra Squadra contenente giocatori da salvare.
 */
void Gestionale::salvaGiocatori(const Squadra& squadra) {
    auto parseGiocatore = [](const std::string& line) {
        return CSVManager::GiocatoreData::fromCSV(CSVManager::splitCSVLine(line));
    };
    
    std::vector<CSVManager::GiocatoreData> giocatoriData =
        CSVManager::caricaRighe<CSVManager::GiocatoreData>(pathGiocatori, parseGiocatore);
    
    int squadraId = squadra.getId();
    
    giocatoriData.erase(
        std::remove_if(giocatoriData.begin(), giocatoriData.end(),
            [squadraId](const CSVManager::GiocatoreData& gd) {
                return gd.squadraId == squadraId;
            }),
        giocatoriData.end()
    );
    
    for (const auto& g : squadra.getGiocatori()) {
        CSVManager::GiocatoreData gd{
            g.getId(), squadraId, g.getEta(),
            g.getNome(), g.getCognome(), g.getRuolo(),
            g.getPlaccaggi(), g.getMetriCorsi(), g.getMete(), g.getCalciPiazzati(),
            g.getFalliCommessi(), g.getOffload(), g.getMinutiGiocati(), g.getPartiteGiocate()
        };
        giocatoriData.push_back(gd);
    }
    
    CSVManager::salvaRighe(pathGiocatori,
        "giocatore_id,squadra_id,nome,cognome,eta,ruolo,placcaggi,metri_corsi,mete,calci_piazzati,"
        "falli_commessi,offload,minuti_giocati,partite_giocate",
        giocatoriData,
        [](const CSVManager::GiocatoreData& gd) { return gd.toCSV(); }
    );
}


/**
 * @brief Carica staff della squadra da CSV.
 * @param squadra Squadra da popolare.
 */
void Gestionale::fetchStaff(Squadra& squadra) {
    auto parseStaff = [this, &squadra](const std::string& line) -> int {
        auto tokens = CSVManager::splitCSVLine(line);
        if (tokens.size() < 6) return 0;
        
        try {
            int idSquadra = std::stoi(trim(tokens[1]));
            if (idSquadra != squadra.getId()) return 0;
            
            RuoloStaff ruolo = Staff::stringToRuolo(trim(tokens[5]));
            Staff s(std::stoi(trim(tokens[0])), trim(tokens[2]), trim(tokens[3]), 
                   std::stoi(trim(tokens[4])), ruolo);
            squadra.addStaff(std::move(s));
            return 1;
        } catch (const std::exception& e) {
            // Silenzioso
            return 0;
        }
    };
    
    try {
        CSVManager::caricaRighe<int>(pathStaff, parseStaff);
    } catch (const std::exception& e) {
        std::cerr << "[WARN] fetchStaff(" << squadra.getId() << "): " << e.what() << std::endl;
    }
}




/**
 * @brief Salva staff della squadra (merge con esistenti).
 * @param squadra Squadra contenente staff da salvare.
 */
void Gestionale::salvaStaff(const Squadra& squadra) {
    auto parseStaff = [](const std::string& line) {
        return CSVManager::StaffData::fromCSV(CSVManager::splitCSVLine(line));
    };
    
    std::vector<CSVManager::StaffData> staffData =
        CSVManager::caricaRighe<CSVManager::StaffData>(pathStaff, parseStaff);
    
    int squadraId = squadra.getId();
    
    staffData.erase(
        std::remove_if(staffData.begin(), staffData.end(),
            [squadraId](const CSVManager::StaffData& sd) {
                return sd.squadraId == squadraId;
            }),
        staffData.end()
    );
    
    int nextId = 1;
    if (!staffData.empty()) {
        nextId = std::max_element(staffData.begin(), staffData.end(),
            [](const CSVManager::StaffData& a, const CSVManager::StaffData& b) { 
                return a.id < b.id; 
            })->id + 1;
    }
    
    for (const auto& s : squadra.getStaff()) {
        int idStaff = s.getId();
        if (idStaff == 0) {
            idStaff = nextId++;
            // Nota: const_cast necessario per modificare ID (design da migliorare)
            const_cast<Staff&>(s).setId(idStaff);
        }

        CSVManager::StaffData sd{
            idStaff, squadraId, s.getEta(),
            s.getNome(), s.getCognome(),
            static_cast<CSVManager::RuoloStaff>(s.getRuolo())
        };
        staffData.push_back(sd);
    }
    
    CSVManager::salvaRighe(pathStaff,
        "staff_id,squadra_id,nome,cognome,eta,ruolo",
        staffData,
        [](const CSVManager::StaffData& sd) { return sd.toCSV(); }
    );
}


/**
 * @brief Carica partite della stagione da CSV con calcolo punti automatici.
 * @param stagione Stagione da popolare.
 */
void Gestionale::fetchPartite(Stagione& stagione) {
    int stagioneAnno = stagione.getAnno();
    const auto& squadre = stagione.getSquadre();
    
    auto parsePartita = [this, &stagione, &squadre, stagioneAnno](const std::string& line) -> int {
        auto tokens = CSVManager::splitCSVLine(line);
        if (tokens.size() < 15) return 0;
        
        try {
            int anno = std::stoi(trim(tokens[1]));
            if (anno != stagioneAnno) return 0;
            
            int idLocali = std::stoi(trim(tokens[3]));
            int idOspiti = std::stoi(trim(tokens[4]));
            
            Squadra* locali = nullptr;
            Squadra* ospiti = nullptr;
            
            for (const auto& sqPtr : squadre) {
                if (sqPtr->getId() == idLocali) locali = sqPtr.get();
                if (sqPtr->getId() == idOspiti) ospiti = sqPtr.get();
            }
            
            if (!locali || !ospiti) return 0;
            
            Partita p(std::stoi(trim(tokens[0])), std::stoi(trim(tokens[2])), *locali, *ospiti);
            int ptLocali = std::stoi(trim(tokens[5]));
            int ptOspiti = std::stoi(trim(tokens[6]));
            int meteLocali = std::stoi(trim(tokens[7]));
            int meteOspiti = std::stoi(trim(tokens[8]));
            
            p.setMeteLocali(meteLocali);
            p.setMeteOspiti(meteOspiti);
            p.setRisultato(ptLocali, ptOspiti);
            p.setCartellinoRossoLoc(std::stoi(trim(tokens[9])));
            p.setCartellinoRossoOsp(std::stoi(trim(tokens[10])));
            p.setCartellinoGialloLoc(std::stoi(trim(tokens[11])));
            p.setCartellinoGialloOsp(std::stoi(trim(tokens[12])));
            p.setPossessoLoc(std::stod(trim(tokens[13])));
            p.setPossessoOsp(std::stod(trim(tokens[14])));
            
            // Calcolo punti rugby COMPLETO
            int puntiLoc = 0, puntiOsp = 0;
            if (ptLocali > ptOspiti) puntiLoc += 4;
            else if (ptLocali < ptOspiti) puntiOsp += 4;
            else { puntiLoc += 2; puntiOsp += 2; }
            
            int diff = std::abs(ptLocali - ptOspiti);
            if (ptLocali > ptOspiti && diff <= 7) puntiOsp += 1;
            else if (ptOspiti > ptLocali && diff <= 7) puntiLoc += 1;
            
            if (meteLocali >= 4) puntiLoc += 1;
            if (meteOspiti >= 4) puntiOsp += 1;
            
            locali->aggiungiPuntiClassifica(puntiLoc);
            ospiti->aggiungiPuntiClassifica(puntiOsp);
            locali->aggiungiMete(meteLocali);
            ospiti->aggiungiMete(meteOspiti);
            
            stagione.addPartita(p);
            return 1;
        } catch (const std::exception& e) {
            // Silenzioso: ignora righe malformate
            return 0;
        }
    };
    
    try {
        CSVManager::caricaRighe<int>(pathPartite, parsePartita);
        std::cout << "Caricate " << stagione.getCalendario().size() << " partite per 2024." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[WARN] fetchPartite(2024): " << e.what() << std::endl;
    }
}




/**
 * @brief Salva partite della stagione (merge con esistenti).
 * @param stagione Stagione contenente partite da salvare.
 */
void Gestionale::salvaPartite(const Stagione& stagione) {
    auto parsePartita = [](const std::string& line) {
        return CSVManager::PartitaData::fromCSV(CSVManager::splitCSVLine(line));
    };

    std::vector<CSVManager::PartitaData> partiteData =
        CSVManager::caricaRighe<CSVManager::PartitaData>(pathPartite, parsePartita);

    int annoStagione = stagione.getAnno();

    partiteData.erase(
        std::remove_if(partiteData.begin(), partiteData.end(),
            [annoStagione](const CSVManager::PartitaData& pd) {
                return pd.anno == annoStagione;
            }),
        partiteData.end()
    );

    for (const auto& p : stagione.getCalendario()) {
        CSVManager::PartitaData pd{
            p.getId(), annoStagione, p.getData(),
            p.getLocali().getId(), p.getOspiti().getId(),
            p.getPuntiLocali(), p.getPuntiOspiti(),
            p.getMeteLocali(), p.getMeteOspiti(),
            p.getCartellinoRossoLoc(), p.getCartellinoRossoOsp(),
            p.getCartellinoGialloLoc(), p.getCartellinoGialloOsp(),
            p.getPossessoLoc(), p.getPossessoOsp()
        };
        partiteData.push_back(pd);
    }
    
    CSVManager::salvaRighe(pathPartite,
        "partita_id,stagione_anno,data,id_locali,id_ospiti,pt_locali,pt_ospiti,"
        "mete_locali,mete_ospiti,"
        "cartellino_rosso_loc,cartellino_rosso_osp,"
        "cartellino_giallo_loc,cartellino_giallo_osp,"
        "possesso_loc,possesso_osp",
        partiteData, [](const CSVManager::PartitaData& pd) { return pd.toCSV(); });
}


/**
 * @brief Aggiunge partita interattivamente con validazione squadre.
 * @param stagione Stagione da modificare.
 */
void Gestionale::aggiungiPartita(Stagione& stagione) {
    int idPartita = stagione.getCalendario().size() + 1;
    int dataPartita, idSquadraLocale, idSquadraOspite;
    int puntiLocali, puntiOspiti;

    std::cout << "Elenco squadre disponibili:\n";
    for (const auto& squadraPtr : stagione.getSquadre()) {
        std::cout << "ID: " << squadraPtr->getId() << " - " << squadraPtr->getNome() << std::endl;
    }

    std::cout << "Inserisci data della partita (formato AAAAMMGG): ";
    std::cin >> dataPartita;
    std::cout << "Inserisci ID squadra locale: ";
    std::cin >> idSquadraLocale;
    std::cout << "Inserisci ID squadra ospite: ";
    std::cin >> idSquadraOspite;

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

    Partita nuovaPartita(idPartita, dataPartita, *locali, *ospiti);
    nuovaPartita.setRisultato(puntiLocali, puntiOspiti);

    stagione.addPartita(nuovaPartita);
    std::cout << "Partita aggiunta con successo.\n";
}

/**
 * @brief Trova massimo ID squadra globale da CSV.
 * @return Massimo ID trovato o 0.
 */
int Gestionale::getMaxSquadraId() const {
    auto parseId = [this](const std::string& line) -> int {
        auto tokens = CSVManager::splitCSVLine(line);
        if (tokens.empty()) return 0;
        try {
            return std::stoi(trim(tokens[0]));
        } catch (...) { return 0; }
    };
    auto ids = CSVManager::caricaRighe<int>(pathSquadre, parseId);
    return ids.empty() ? 0 : *std::max_element(ids.begin(), ids.end());
}


/**
 * @brief Salvataggio COMPLETO parallelo con 5 thread.
 * 
 * t1: stagioni.csv
 * t2: squadre.csv
 * t3: partite.csv
 * t4: TUTTI giocatori (parallelo)
 * t5: TUTTI staff (parallelo)
 */
void Gestionale::salvaParallel(const Stagione& stagione) {
    printf("=== Avvio salvataggio PARALLELO (5 THREAD) ===\n");
    
    // THREAD 1-3: Indipendenti (stagioni/squadre/partite)
    std::thread t1([this, &stagione]() {
        try { salvaStagioni(stagione); }
        catch (const std::exception& e) { printf("[ERRORE] salvaStagioni: %s\n", e.what()); }
    });
    
    std::thread t2([this, &stagione]() {
        try { salvaSquadre(stagione); }
        catch (const std::exception& e) { printf("[ERRORE] salvaSquadre: %s\n", e.what()); }
    });
    
    std::thread t3([this, &stagione]() {
        try { salvaPartite(stagione); }
        catch (const std::exception& e) { printf("[ERRORE] salvaPartite: %s\n", e.what()); }
    });
    
    // THREAD 4: TUTTI GIOCATORI (parallelo)
    std::thread t4([this, &stagione]() {
        try {
            for (const auto& squadraPtr : stagione.getSquadre()) {
                salvaGiocatori(*squadraPtr);
            }
        } catch(const std::exception& e) {
            printf("[ERRORE] salvaGiocatori: %s\n", e.what());
        }
    });
    
    // THREAD 5: TUTTI STAFF (parallelo)
    std::thread t5([this, &stagione]() {
        try {
            for (const auto& squadraPtr : stagione.getSquadre()) {
                salvaStaff(*squadraPtr);
            }
        } catch(const std::exception& e) {
            printf("[ERRORE] salvaStaff: %s\n", e.what());
        }
    });
    
    // Join tutti i 5 thread
    t1.join(); t2.join(); t3.join(); t4.join(); t5.join();
    printf("=== Salvataggio COMPLETO (5 THREAD)! ===\n");
}


std::string Gestionale::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}
