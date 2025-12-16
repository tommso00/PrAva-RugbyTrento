#include "Gestionale.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <memory>
#include <algorithm>
#include <numeric>

using namespace std;

// ==================== RAII FILE GUARD ====================
namespace CSVHelper {
    // RAII Wrapper per gestione automatica file
    class FileGuard {
        std::ifstream infile;
        std::ofstream outfile;
    public:
        explicit FileGuard(const std::string& path, bool write = false) {
            if (write) {
                outfile.open(path);
                if (!outfile.is_open()) {
                    throw std::runtime_error("Impossibile aprire " + path + " in scrittura");
                }
            } else {
                infile.open(path);
            }
        }
        
        std::ifstream& getInput() { return infile; }
        std::ofstream& getOutput() { return outfile; }
        bool inputOpen() const { return infile.is_open(); }
        
        ~FileGuard() = default; // Chiusura automatica
    };
    
    // TEMPLATE: Carica righe CSV con lambda parser
    template<typename T, typename LoadFunc>
    std::vector<T> caricaRighe(const std::string& filepath, LoadFunc loader) {
        std::vector<T> risultati;
        FileGuard file(filepath);
        
        if (!file.inputOpen()) return risultati;
        
        std::string line;
        bool primaRiga = true;
        while (std::getline(file.getInput(), line)) {
            if (primaRiga) { primaRiga = false; continue; }
            if (line.empty()) continue;
            
            try {
                risultati.push_back(loader(line));
            } catch (const std::exception& e) {
                printf("[WARN] Riga CSV ignorata: %s\n", e.what());
            }
        }
        return risultati;
    }
    
    // TEMPLATE: Salva righe CSV con lambda formatter
    template<typename T, typename FormatFunc>
    void salvaRighe(const std::string& filepath, 
                    const std::string& header,
                    const std::vector<T>& dati,
                    FormatFunc formatter) {
        FileGuard file(filepath, true);
        auto& out = file.getOutput();
        
        out << header << "\n";
        std::for_each(dati.begin(), dati.end(), [&](const T& item) {
            out << formatter(item) << "\n";
        });
    }
}

// ==================== STRUCT PER DATI CSV ====================
namespace {
    // Struct Squadra (invece di tuple)
    struct SquadraData {
        int id, anno;
        std::string nome, indirizzo;
        int possessoPalla;
        double territorio;
        int placcaggiTotali, metriGuadagnatiTotali, meteTotali, falliTotali;
        int mischieVinte, mischiePerse, toucheVinte, touchePerse;
        int punteggio;
        
        static SquadraData fromCSV(const std::vector<std::string>& tokens) {
            if (tokens.size() < 15) throw std::runtime_error("CSV squadra incompleto");
            
            return SquadraData{
                std::stoi(tokens[0]), std::stoi(tokens[1]),
                tokens[2], tokens[3],
                std::stoi(tokens[4]), std::stod(tokens[5]),
                std::stoi(tokens[6]), std::stoi(tokens[7]), std::stoi(tokens[8]), std::stoi(tokens[9]),
                std::stoi(tokens[10]), std::stoi(tokens[11]), std::stoi(tokens[12]), std::stoi(tokens[13]),
                std::stoi(tokens[14])
            };
        }
        
        std::string toCSV() const {
            std::ostringstream oss;
            oss << id << "," << anno << "," << nome << "," << indirizzo << ","
                << possessoPalla << "," << territorio << ","
                << placcaggiTotali << "," << metriGuadagnatiTotali << "," << meteTotali << "," << falliTotali << ","
                << mischieVinte << "," << mischiePerse << "," << toucheVinte << "," << touchePerse << ","
                << punteggio;
            return oss.str();
        }
    };
    
    // Struct Giocatore
    struct GiocatoreData {
        int id, squadraId, eta;
        std::string nome, cognome, ruolo;
        int placcaggi, metriCorsi, mete, calciPiazzati;
        int falliCommessi, offload, minutiGiocati, partiteGiocate;
        
        static GiocatoreData fromCSV(const std::vector<std::string>& tokens) {
            if (tokens.size() < 14) throw std::runtime_error("CSV giocatore incompleto");
            return GiocatoreData{
                std::stoi(tokens[0]), std::stoi(tokens[1]), std::stoi(tokens[4]),
                tokens[2], tokens[3], tokens[5],
                std::stoi(tokens[6]), std::stoi(tokens[7]), std::stoi(tokens[8]), std::stoi(tokens[9]),
                std::stoi(tokens[10]), std::stoi(tokens[11]), std::stoi(tokens[12]), std::stoi(tokens[13])
            };
        }
        
        std::string toCSV() const {
            std::ostringstream oss;
            oss << id << "," << squadraId << "," << nome << "," << cognome << "," << eta << "," << ruolo << ","
                << placcaggi << "," << metriCorsi << "," << mete << "," << calciPiazzati << ","
                << falliCommessi << "," << offload << "," << minutiGiocati << "," << partiteGiocate;
            return oss.str();
        }
    };
    
    // Struct Partita
    struct PartitaData {
        int id, anno, data, idLocali, idOspiti;
        int ptLocali, ptOspiti, meteLocali, meteOspiti;
        int cartellinoRossoLoc, cartellinoRossoOsp;
        int cartellinoGialloLoc, cartellinoGialloOsp;
        double possessoLoc, possessoOsp;
        
        static PartitaData fromCSV(const std::vector<std::string>& tokens) {
            if (tokens.size() < 15) throw std::runtime_error("CSV partita incompleto");
            return PartitaData{
                std::stoi(tokens[0]), std::stoi(tokens[1]), std::stoi(tokens[2]), 
                std::stoi(tokens[3]), std::stoi(tokens[4]),
                std::stoi(tokens[5]), std::stoi(tokens[6]), std::stoi(tokens[7]), std::stoi(tokens[8]),
                std::stoi(tokens[9]), std::stoi(tokens[10]), std::stoi(tokens[11]), std::stoi(tokens[12]),
                std::stod(tokens[13]), std::stod(tokens[14])
            };
        }
        
        std::string toCSV() const {
            std::ostringstream oss;
            oss << id << "," << anno << "," << data << "," << idLocali << "," << idOspiti << ","
                << ptLocali << "," << ptOspiti << "," << meteLocali << "," << meteOspiti << ","
                << cartellinoRossoLoc << "," << cartellinoRossoOsp << ","
                << cartellinoGialloLoc << "," << cartellinoGialloOsp << ","
                << possessoLoc << "," << possessoOsp;
            return oss.str();
        }
    };
    
    // ==================== THREAD WRAPPERS ====================
    void threadSalvaStagioni(Gestionale* gestore, const Stagione* stagione) {
        try {
            gestore->salvaStagioni(*stagione);
        } catch (const std::exception& e) {
            printf("[ERRORE] salvaStagioni: %s\n", e.what());
        }
    }
    
    void threadSalvaSquadre(Gestionale* gestore, const Stagione* stagione) {
        try {
            gestore->salvaSquadre(*stagione);
        } catch (const std::exception& e) {
            printf("[ERRORE] salvaSquadre: %s\n", e.what());
        }
    }
    
    void threadSalvaPartite(Gestionale* gestore, const Stagione* stagione) {
        try {
            gestore->salvaPartite(*stagione);
        } catch (const std::exception& e) {
            printf("[ERRORE] salvaPartite: %s\n", e.what());
        }
    }
}

// ==================== CREA STAGIONE ====================
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

// ==================== RECUPERA STAGIONE ====================
int Gestionale::recuperaStagione(const std::string& filename, int numeroRiga) {
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
            intestazioneSaltata = true;
            continue;
        }
        contoRighe++;
        if (contoRighe == numeroRiga) {
            std::cout << "Riga " << numeroRiga << ": " << riga << std::endl;
            return std::stoi(riga);
        }
    }

    std::cout << "Riga " << numeroRiga << " non trovata nel file." << std::endl;
    return 0;
}

// ==================== MODIFICA STAGIONE ====================
void Gestionale::modificaStagione(Stagione& stagione) {
    int lastSquadraId = getMaxSquadraId();  
    for (const auto& s : stagione.getSquadre()) {
        if (s->getId() > lastSquadraId) lastSquadraId = s->getId();
    }

    int azione, azgioc, controllo = 0, c = 0;
    string nome, cognome, ruolo;
    int eta;
    
    while(controllo == 0) {
        cout << endl << "Seleziona azione:" << endl;
        cout << "1) Aggiungi squadra" << endl 
             << "2) Aggiungi partita" << endl 
             << "3) Stampa Stagione" << endl 
             << "4) Vedi Classifica" << endl 
             << "5) Medie Punteggio" << endl;
        cin >> azione;
        
        switch (azione) {
            case 1: {
                while(c == 0) {
                    auto squadraPtr = aggiungiSquadra();
                    squadraPtr->setId(++lastSquadraId);
                    
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
                auto classifica = stagione.classificaSquadre();
                std::cout << "\n?? CLASSIFICA (STL sort + lambda):\n";
                for(size_t i = 0; i < classifica.size(); ++i) {
                    std::cout << (i+1) << ". " << classifica[i]->getNome() 
                              << " (" << classifica[i]->getPunteggio() << " pt)\n";
                }
                
                std::cout << "\n?? Media punteggio: " << stagione.mediaPunteggioSquadre() << "\n";
                std::cout << "?? Media mete: " << stagione.mediaMeteTotaliSquadre() << "\n";
                
                auto top3 = stagione.topSquadre(3);
                std::cout << "\n?? TOP 3 (partial_sort):\n";
                for(size_t i = 0; i < top3.size(); ++i) {
                    std::cout << (i+1) << ". " << top3[i]->getNome() << "\n";
                }
                break;
            }
            case 5: {
                std::cout << "\n?? TEMPLATE METAPROGRAMMING:\n";
                std::cout << "Media punteggio (template): " << stagione.mediaPunteggioTemplate() << "\n";
                std::cout << "Somma mete totali (template): " << stagione.sommaMeteTemplate() << "\n";
                
                auto media_mete = stagione.calcolaMedia(stagione.getSquadre(), &Squadra::getMeteTotali);
                auto media_placcaggi = stagione.calcolaMedia(stagione.getSquadre(), &Squadra::getPlaccaggiTotali);
                
                std::cout << "Media mete (pointer-to-member): " << media_mete << "\n";
                std::cout << "Media placcaggi (pointer-to-member): " << media_placcaggi << "\n";
                break;
            }
            default:
                cout << "Azione non valida." << endl;
                break;
        }
        cout << "Vuoi modificare ancora? 0=si / 1=no" << endl;
        cin >> controllo;
    }
	
	/*for (const auto& sq : stagione.getSquadre()) {
	    std::cout << sq->getNome()
	              << " meteTotali=" << sq->getMeteTotali() << "\n";
	}*/

    salvaParallel(stagione);
}

// ==================== AGGIUNGI SQUADRA ====================
std::unique_ptr<Squadra> Gestionale::aggiungiSquadra() {
    int newId = getMaxSquadraId() + 1;
    string nome, indirizzo;
    cout << "Nome squadra: ";
    cin >> nome;
    cout << "Indirizzo squadra: ";
    cin >> indirizzo;

    return std::unique_ptr<Squadra>(new Squadra(newId, nome, indirizzo));
}

// ==================== RICERCA STAGIONE ====================
Stagione* Gestionale::trovaStagione(int anno) {
    auto it = std::find_if(stagioni.begin(), stagioni.end(),
        [anno](const std::unique_ptr<Stagione>& s) {
            return s->getAnno() == anno;
        });
    
    return (it != stagioni.end()) ? it->get() : nullptr;
}

// ==================== SELEZIONA STAGIONE ====================
void Gestionale::selezionaStagione() {
    fetchStagioni(pathStagioni);
    
    int stag;
    std::cout << std::endl << "Seleziona numero stagione da caricare:" << std::endl;
    std::cin >> stag;

    std::cout << "Selezionata: " << stag << std::endl;

    int anno = recuperaStagione(pathStagioni, stag);
    if(anno == 0) return;
    
    auto stagionePtr = std::unique_ptr<Stagione>(new Stagione(anno));
    Stagione* stagioneSelezionata = stagionePtr.get();
    
    fetchSquadre(*stagionePtr);
    //std::cout << "DEBUG: Caricate " << stagionePtr->getSquadre().size() << " squadre\n";
    
    for (auto& squadraPtr : stagionePtr->getSquadre()) {
        fetchGiocatori(*squadraPtr);
    }
    
    fetchPartite(*stagionePtr);
    //std::cout << "DEBUG: fetchPartite completato\n";
    
    /*std::cout << "DEBUG SQUADRE DOPO CARICAMENTO:\n";
    for (const auto& sq : stagionePtr->getSquadre()) {
        std::cout << "  " << sq->getNome() << " pts=" << sq->getPunteggio() << "\n";
    }*/
    
    stagioni.push_back(std::move(stagionePtr));
    modificaStagione(*stagioneSelezionata);
}

// ==================== SPLIT CSV LINE ====================
vector<string> Gestionale::splitCSVLine(const string& line) const {
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
    int numeroRiga = 1;
    std::cout << endl << "=== Elenco Stagioni ===" << endl;
    bool prima = true;
    
    while (std::getline(file, riga)) {
        if (prima) { 
            prima = false; 
            continue; 
        }
        std::cout << numeroRiga << ". " << riga << std::endl;
        ++numeroRiga;
    }
    file.close();
}

// ==================== SALVA STAGIONI (OTTIMIZZATO) ====================
void Gestionale::salvaStagioni(const Stagione& nuovaStagione) {
    using namespace CSVHelper;
    
    auto parseAnno = [](const std::string& line) -> int {
        return std::stoi(line);
    };
    
    auto anni = caricaRighe<int>(pathStagioni, parseAnno);
    
    int annoNuova = nuovaStagione.getAnno();
    if (std::find(anni.begin(), anni.end(), annoNuova) == anni.end()) {
        anni.push_back(annoNuova);
    }
    
    auto formatAnno = [](int anno) -> std::string {
        return std::to_string(anno);
    };
    
    salvaRighe(pathStagioni, "anno", anni, formatAnno);
}

// ==================== FETCH SQUADRE ====================
void Gestionale::fetchSquadre(Stagione& stagione) {
    std::ifstream file(pathSquadre);
    if (!file.is_open()) {
        std::cerr << "Impossibile aprire il file squadre.csv" << std::endl;
        return;
    }

    std::string line;
    bool primaRiga = true;
    int stagioneAnno = stagione.getAnno();

    while (std::getline(file, line)) {
        if (primaRiga) { 
            primaRiga = false; 
            continue; 
        }
        if (line.empty()) continue;

        std::vector<std::string> tokens = splitCSVLine(line);
        if (tokens.size() >= 15) {
            int anno = std::stoi(tokens[1]);
            
            if (anno == stagioneAnno) {
                auto squadraPtr = std::unique_ptr<Squadra>(new Squadra(
                    std::stoi(tokens[0]), tokens[2], tokens[3]
                ));
                
                squadraPtr->setPossessoPalla(std::stoi(tokens[4]));
                squadraPtr->setTerritorio(std::stod(tokens[5]));
                squadraPtr->setPlaccaggiTotali(std::stoi(tokens[6]));
                squadraPtr->setMetriGuadagnatiTotali(std::stoi(tokens[7]));
                //squadraPtr->setMeteTotali(std::stoi(tokens[8]));
                squadraPtr->setFalliTotali(std::stoi(tokens[9]));
                squadraPtr->setMischieVinte(std::stoi(tokens[10]));
                squadraPtr->setMischiePerse(std::stoi(tokens[11]));
                squadraPtr->setToucheVinte(std::stoi(tokens[12]));
                squadraPtr->setTouchePerse(std::stoi(tokens[13]));
                squadraPtr->setPunteggio(std::stoi(tokens[14]));
                
                stagione.addSquadra(std::move(squadraPtr));
            }
        }
    }
    
    for (auto& squadraPtr : stagione.getSquadre()) {
        squadraPtr->setPunteggio(0);  // ? RESET PUNTEGGIO
        //squadraPtr->setMeteTotali(0); // ? RESET METE (se necessario)
    }
    file.close();
}

// ==================== SALVA SQUADRE (OTTIMIZZATO) ====================
void Gestionale::salvaSquadre(const Stagione& stagione) {
    using namespace CSVHelper;
    
    std::vector<SquadraData> squadreData;
    int annoStagione = stagione.getAnno();
    
    // ? Popola SOLO con dati della stagione corrente
    for (const auto& sq : stagione.getSquadre()) {
        SquadraData sd{
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
    
    salvaRighe(pathSquadre, 
        "squadra_id,stagione_anno,nome,indirizzo,possesso_palla,territorio,"
        "placcaggi_totali,metri_guadagnati_totali,mete_totali,falli_totali,"
        "mischie_vinte,mischie_perse,touche_vinte,touche_perse,punteggio_classifica",
        squadreData, [](const SquadraData& sd) { return sd.toCSV(); });
}


// ==================== FETCH GIOCATORI ====================
void Gestionale::fetchGiocatori(Squadra& squadra) {
    std::ifstream file(pathGiocatori);
    if (!file.is_open()) {
        std::cerr << "Impossibile aprire il file giocatori.csv" << std::endl;
        return;
    }

    std::string line;
    bool primaRiga = true;
    int squadraId = squadra.getId();

    while (std::getline(file, line)) {
        if (primaRiga) { 
            primaRiga = false; 
            continue; 
        }
        if (line.empty()) continue;

        std::vector<std::string> tokens = splitCSVLine(line);

        if (tokens.size() >= 14) {
            int idSquadra = std::stoi(tokens[1]);

            if (idSquadra == squadraId) {
                Giocatore g(tokens[2], tokens[3], std::stoi(tokens[4]), tokens[5], std::stoi(tokens[0]));
                
                g.setPlaccaggi(std::stoi(tokens[6]));
                g.setMetriCorsi(std::stoi(tokens[7]));
                g.setMete(std::stoi(tokens[8]));
                g.setCalciPiazzati(std::stoi(tokens[9]));
                g.setFalliCommessi(std::stoi(tokens[10]));
                g.setOffload(std::stoi(tokens[11]));
                g.setMinutiGiocati(std::stoi(tokens[12]));
                g.setPartiteGiocate(std::stoi(tokens[13]));
                
                squadra.addGiocatore(g);
            }
        }
    }
    file.close();
}

// ==================== SALVA GIOCATORI (OTTIMIZZATO) ====================
void Gestionale::salvaGiocatori(const Squadra& squadra) {
    using namespace CSVHelper;
    
    // 1) Carico TUTTI i giocatori già presenti nel file
    auto parseGiocatore = [this](const std::string& line) {
        return GiocatoreData::fromCSV(splitCSVLine(line));
    };
    
    std::vector<GiocatoreData> giocatoriData =
        caricaRighe<GiocatoreData>(pathGiocatori, parseGiocatore);
    
    int squadraId = squadra.getId();
    
    // 2) Rimuovo i giocatori appartenenti a questa squadra
    giocatoriData.erase(
        std::remove_if(giocatoriData.begin(), giocatoriData.end(),
            [squadraId](const GiocatoreData& gd) {
                return gd.squadraId == squadraId;
            }),
        giocatoriData.end()
    );
    
    // 3) Aggiungo i giocatori ATTUALI della squadra
    for (const auto& g : squadra.getGiocatori()) {
        GiocatoreData gd{
            g.getId(), squadraId, g.getEta(),
            g.getNome(), g.getCognome(), g.getRuolo(),
            g.getPlaccaggi(), g.getMetriCorsi(), g.getMete(), g.getCalciPiazzati(),
            g.getFalliCommessi(), g.getOffload(), g.getMinutiGiocati(), g.getPartiteGiocate()
        };
        giocatoriData.push_back(gd);
    }
    
    // 4) Riscrivo l'intero file con TUTTI i giocatori (vecchi + aggiornati)
    salvaRighe(pathGiocatori,
        "giocatore_id,squadra_id,nome,cognome,eta,ruolo,"
        "placcaggi,metri_corsi,mete,calci_piazzati,"
        "falli_commessi,offload,minuti_giocati,partite_giocate",
        giocatoriData,
        [](const GiocatoreData& gd) { return gd.toCSV(); }
    );
}



// ==================== FETCH PARTITE ====================
void Gestionale::fetchPartite(Stagione& stagione) {
    std::ifstream file(pathPartite);
    if (!file.is_open()) {
        std::cerr << "Impossibile aprire partite.csv" << std::endl;
        return;
    }

    std::string line;
    bool primaRiga = true;
    int stagioneAnno = stagione.getAnno();
    const auto& squadre = stagione.getSquadre();

    while (getline(file, line)) {
        if (primaRiga) { primaRiga = false; continue; }
        if (line.empty()) continue;

        auto tokens = splitCSVLine(line);
        if (tokens.size() >= 15) {
            int anno = std::stoi(tokens[1]);

            if (anno == stagioneAnno) {
                int idLocali = std::stoi(tokens[3]);
                int idOspiti = std::stoi(tokens[4]);
                
                Squadra* locali = nullptr;
                Squadra* ospiti = nullptr;
                
                for (const auto& sqPtr : squadre) {
                    if (sqPtr->getId() == idLocali) locali = sqPtr.get();
                    if (sqPtr->getId() == idOspiti) ospiti = sqPtr.get();
                }
                
                if (locali && ospiti) {
                    Partita p(std::stoi(tokens[0]), std::stoi(tokens[2]), *locali, *ospiti);
                    
                    int ptLocali = std::stoi(tokens[5]);
                    int ptOspiti = std::stoi(tokens[6]);
                    int meteLocali = std::stoi(tokens[7]);
                    int meteOspiti = std::stoi(tokens[8]);
                    
                    p.setMeteLocali(meteLocali);   // ? NUOVO
					p.setMeteOspiti(meteOspiti);   // ? NUOVO
                    
                    p.setRisultato(ptLocali, ptOspiti);
                    p.setCartellinoRossoLoc(std::stoi(tokens[9]));
                    p.setCartellinoRossoOsp(std::stoi(tokens[10]));
                    p.setCartellinoGialloLoc(std::stoi(tokens[11]));
                    p.setCartellinoGialloOsp(std::stoi(tokens[12]));
                    p.setPossessoLoc(std::stod(tokens[13]));
                    p.setPossessoOsp(std::stod(tokens[14]));
                    
                    // Calcolo punti classifica
                    int puntiLoc = 0, puntiOsp = 0;
                    
                    if (ptLocali > ptOspiti) {
                        puntiLoc += 4;
                    } else if (ptLocali < ptOspiti) {
                        puntiOsp += 4;
                    } else {
                        puntiLoc += 2;
                        puntiOsp += 2;
                    }
                    
                    int diff = std::abs(ptLocali - ptOspiti);
                    if (ptLocali > ptOspiti && diff <= 7) {
                        puntiOsp += 1;
                    } else if (ptOspiti > ptLocali && diff <= 7) {
                        puntiLoc += 1;
                    }
                    
                    if (meteLocali >= 4) puntiLoc += 1;
                    if (meteOspiti >= 4) puntiOsp += 1;
                    
                    locali->aggiungiPuntiClassifica(puntiLoc);
                    ospiti->aggiungiPuntiClassifica(puntiOsp);
                    locali->aggiungiMete(meteLocali);
                    ospiti->aggiungiMete(meteOspiti);
                    
                    stagione.addPartita(p);
                }
            }
        }
    }
    file.close();

}

// ==================== SALVA PARTITE (OTTIMIZZATO) ====================
void Gestionale::salvaPartite(const Stagione& stagione) {
    using namespace CSVHelper;
    
    std::vector<PartitaData> partiteData;
    int annoStagione = stagione.getAnno();
    
    // ? Popola SOLO con partite della stagione corrente
    for (const auto& p : stagione.getCalendario()) {
        PartitaData pd{
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
    
    salvaRighe(pathPartite,
        "partita_id,stagione_anno,data,id_locali,id_ospiti,pt_locali,pt_ospiti,"
        "mete_locali,mete_ospiti,"
        "cartellino_rosso_loc,cartellino_rosso_osp,"
        "cartellino_giallo_loc,cartellino_giallo_osp,"
        "possesso_loc,possesso_osp",
        partiteData, [](const PartitaData& pd) { return pd.toCSV(); });
}


// ==================== AGGIUNGI PARTITA ====================
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

// ==================== GET MAX SQUADRA ID (OTTIMIZZATO) ====================
int Gestionale::getMaxSquadraId() const {
    using namespace CSVHelper;
    
    auto parseId = [this](const std::string& line) -> int {
        auto tokens = splitCSVLine(line);
        return tokens.empty() ? 0 : std::stoi(tokens[0]);
    };
    
    auto ids = caricaRighe<int>(pathSquadre, parseId);
    
    if (ids.empty()) return 0;
    return *std::max_element(ids.begin(), ids.end());
}

// ==================== SALVATAGGIO PARALLELO ====================
void Gestionale::salvaParallel(const Stagione& stagione) {
    printf("=== Avvio salvataggio parallelo ===\n");
    
    // Thread paralleli per dati pesanti
    std::thread t1(threadSalvaStagioni, this, &stagione);
    std::thread t2(threadSalvaSquadre, this, &stagione);
    std::thread t3(threadSalvaPartite, this, &stagione);
    
    t1.join(); t2.join(); t3.join();
    
    // Salvataggio sequenziale per giocatori (dipende dalle squadre)
    printf("Salvataggio giocatori...\n");
    try{
    for (const auto& squadraPtr : stagione.getSquadre()) {
	    std::cout << "Squadra " << squadraPtr->getNome()
	              << " giocatori: " << squadraPtr->getGiocatori().size() << "\n";
	    salvaGiocatori(*squadraPtr);
		}
	}catch(const std::exception& e){
		std::cerr << "[ERRORE] salvaGiocatori: " << e.what() << "\n";
	}
    
    printf("=== Salvataggio COMPLETO! ===\n");
}


