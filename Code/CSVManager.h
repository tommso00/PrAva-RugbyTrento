#ifndef CSV_MANAGER_H
#define CSV_MANAGER_H

#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <memory>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <limits>

/**
 * @file CSVManager.h
 * @brief Gestore completo per operazioni CSV sicure (C++11).
 * 
 * RAII per file, template generici per load/save, struct POD per dati rugby.
 * Namespace organizzato, eccezioni gestite, zero dipendenze esterne.
 */

namespace CSVManager {
    
    // ==================== RAII FILE GUARD ====================
    /**
     * @class FileGuard
     * @brief RAII per gestione automatica file CSV (input/output).
     * 
     * Garantisce apertura/chiusura automatica con controllo eccezioni.
     */
    class FileGuard {
        std::ifstream infile;
        std::ofstream outfile;
    public:
        /**
         * @brief Costruttore con apertura file.
         * @param path Percorso file CSV.
         * @param write Modalità scrittura (true) o lettura (false).
         * @throws std::runtime_error se file non apribile.
         */
        explicit FileGuard(const std::string& path, bool write = false) {
            if (write) {
                outfile.open(path);
                if (!outfile.is_open()) {
                    throw std::runtime_error("Impossibile aprire " + path + " in scrittura");
                }
            } else {
                infile.open(path);
                if (!infile.is_open()) {
                    throw std::runtime_error("Impossibile aprire " + path + " in lettura");
                }
            }
        }
        
        std::ifstream& getInput() { return infile; }
        std::ofstream& getOutput() { return outfile; }
        bool inputOpen() const { return infile.is_open(); }
        bool outputOpen() const { return outfile.is_open(); }
        
        ~FileGuard() = default;
    };
    
    // ==================== TEMPLATE GENERICI ====================
    /**
     * @brief Carica righe CSV con parser personalizzato (C++11 lambda).
     * @tparam T Tipo dati da costruire.
     * @tparam LoadFunc Funzione parser (std::string -> T).
     * @param filepath Percorso file CSV.
     * @param loader Funzione di parsing riga.
     * @return Vettore di oggetti T caricati.
     */
	template<typename T, typename LoadFunc>
	std::vector<T> caricaRighe(const std::string& filepath, LoadFunc loader, bool skipHeader = true) {
	    std::vector<T> risultati;
	    FileGuard file(filepath);
	    
	    if (!file.inputOpen()) {
	        return risultati;
	    }
	    
	    std::string line;
	    bool primaRiga = true;
	    
	    while (std::getline(file.getInput(), line)) {
	        if (primaRiga && skipHeader) { 
	            primaRiga = false; 
	            continue; 
	        }
	        primaRiga = false;  // Reset per righe successive
	        
	        if (line.empty()) continue;
	        
	        try {
	            risultati.push_back(loader(line));
	        } catch (const std::exception& e) {
	            printf("[WARN] Riga CSV ignorata: %s\n", e.what());
	        }
	    }
	    return risultati;
	}

    /**
     * @brief Salva righe CSV con formatter personalizzato.
     * @tparam T Tipo dati da serializzare.
     * @tparam FormatFunc Funzione formatter (T -> std::string).
     * @param filepath Percorso file CSV.
     * @param header Riga intestazione CSV.
     * @param dati Vettore dati da salvare.
     * @param formatter Funzione di formattazione.
     */
    template<typename T, typename FormatFunc>
    void salvaRighe(const std::string& filepath, 
                    const std::string& header,
                    const std::vector<T>& dati,
                    FormatFunc formatter) {
        FileGuard file(filepath, true);
        auto& out = file.getOutput();
        
        out << header << "\n";
        std::for_each(dati.begin(), dati.end(), 
                     [&](const T& item) { out << formatter(item) << "\n"; });
    }
    
    /**
     * @brief Split riga CSV su virgola (utility C++11).
     * @param line Riga CSV grezza.
     * @return Vettore token splittati.
     */
    std::vector<std::string> splitCSVLine(const std::string& line) {
        std::vector<std::string> tokens;
        std::stringstream ss(line);
        std::string cell;
        while (std::getline(ss, cell, ',')) {
            tokens.push_back(cell);
        }
        return tokens;
    }
    
    // ==================== STRUCT DATI RUGBY ====================
    /**
     * @struct SquadraData
     * @brief POD per deserializzazione CSV squadre.
     */
    struct SquadraData {
        int id, anno;
        std::string nome, indirizzo;
        int possessoPalla;
        double territorio;
        int placcaggiTotali, metriGuadagnatiTotali, meteTotali, falliTotali;
        int mischieVinte, mischiePerse, toucheVinte, touchePerse;
        int punteggio;
        public:
	        
	        static SquadraData fromCSV(const std::vector<std::string>& tokens) {
	            if (tokens.size() < 15) {
	                throw std::runtime_error("CSV squadra incompleto");
	            }
	            return SquadraData{
	                std::stoi(tokens[0]), std::stoi(tokens[1]),
	                tokens[2], tokens[3],
	                std::stoi(tokens[4]), std::stod(tokens[5]),
	                std::stoi(tokens[6]), std::stoi(tokens[7]), 
	                std::stoi(tokens[8]), std::stoi(tokens[9]),
	                std::stoi(tokens[10]), std::stoi(tokens[11]), 
	                std::stoi(tokens[12]), std::stoi(tokens[13]),
	                std::stoi(tokens[14])
	            };
	        }
	        
	        std::string toCSV() const {
	            std::ostringstream oss;
	            oss << id << "," << anno << "," << nome << "," << indirizzo << ","
	                << possessoPalla << "," << territorio << ","
	                << placcaggiTotali << "," << metriGuadagnatiTotali << "," 
	                << meteTotali << "," << falliTotali << ","
	                << mischieVinte << "," << mischiePerse << "," 
	                << toucheVinte << "," << touchePerse << "," << punteggio;
	            return oss.str();
	        }
    };
    
    /**
     * @struct GiocatoreData
     * @brief POD per deserializzazione CSV giocatori.
     */
    struct GiocatoreData {
        int id, squadraId, eta;
        std::string nome, cognome, ruolo;
        int placcaggi, metriCorsi, mete, calciPiazzati;
        int falliCommessi, offload, minutiGiocati, partiteGiocate;
        
        static GiocatoreData fromCSV(const std::vector<std::string>& tokens) {
            if (tokens.size() < 14) {
                throw std::runtime_error("CSV giocatore incompleto");
            }
            return GiocatoreData{
                std::stoi(tokens[0]), std::stoi(tokens[1]), std::stoi(tokens[4]),
                tokens[2], tokens[3], tokens[5],
                std::stoi(tokens[6]), std::stoi(tokens[7]), std::stoi(tokens[8]), 
                std::stoi(tokens[9]),
                std::stoi(tokens[10]), std::stoi(tokens[11]), 
                std::stoi(tokens[12]), std::stoi(tokens[13])
            };
        }
        
        std::string toCSV() const {
            std::ostringstream oss;
            oss << id << "," << squadraId << "," << nome << "," << cognome 
                << "," << eta << "," << ruolo << ","
                << placcaggi << "," << metriCorsi << "," << mete << "," 
                << calciPiazzati << ","
                << falliCommessi << "," << offload << "," << minutiGiocati 
                << "," << partiteGiocate;
            return oss.str();
        }
    };
    
    /**
     * @enum RuoloStaff
     * @brief Enum ruoli staff (C++11).
     */
    enum class RuoloStaff {
        ALLENATORE, AIUTANTE_ALLENATORE, DS, SEGRETERIA, ALLENATORE_MINI
    };
    
    /**
     * @struct StaffData
     * @brief POD per deserializzazione CSV staff.
     */
    struct StaffData {
        int id, squadraId, eta;
        std::string nome, cognome;
        RuoloStaff ruolo;
        
        static StaffData fromCSV(const std::vector<std::string>& tokens) {
            if (tokens.size() < 6) {
                throw std::runtime_error("CSV staff incompleto");
            }
            return StaffData{
                std::stoi(tokens[0]), std::stoi(tokens[1]), std::stoi(tokens[4]),
                tokens[2], tokens[3],
                stringToRuolo(tokens[5])
            };
        }
        
        std::string toCSV() const {
            std::ostringstream oss;
            oss << id << "," << squadraId << "," << nome << "," << cognome 
                << "," << eta << "," << ruoloToString(ruolo);
            return oss.str();
        }
        
    private:
        static RuoloStaff stringToRuolo(const std::string& s) {
            if (s == "ALLENATORE") return RuoloStaff::ALLENATORE;
            if (s == "AIUTANTE_ALLENATORE") return RuoloStaff::AIUTANTE_ALLENATORE;
            if (s == "DS") return RuoloStaff::DS;
            if (s == "SEGRETERIA") return RuoloStaff::SEGRETERIA;
            if (s == "ALLENATORE_MINI") return RuoloStaff::ALLENATORE_MINI;
            return RuoloStaff::ALLENATORE;
        }
        
        static std::string ruoloToString(RuoloStaff r) {
            switch(r) {
                case RuoloStaff::ALLENATORE: return "ALLENATORE";
                case RuoloStaff::AIUTANTE_ALLENATORE: return "AIUTANTE_ALLENATORE";
                case RuoloStaff::DS: return "DS";
                case RuoloStaff::SEGRETERIA: return "SEGRETERIA";
                case RuoloStaff::ALLENATORE_MINI: return "ALLENATORE_MINI";
                default: return "ALLENATORE";
            }
        }
    };
    
    /**
     * @struct PartitaData
     * @brief POD per deserializzazione CSV partite.
     */
    struct PartitaData {
        int id, anno, data, idLocali, idOspiti;
        int ptLocali, ptOspiti, meteLocali, meteOspiti;
        int cartellinoRossoLoc, cartellinoRossoOsp;
        int cartellinoGialloLoc, cartellinoGialloOsp;
        double possessoLoc, possessoOsp;
        
        static PartitaData fromCSV(const std::vector<std::string>& tokens) {
            if (tokens.size() < 15) {
                throw std::runtime_error("CSV partita incompleto");
            }
            return PartitaData{
                std::stoi(tokens[0]), std::stoi(tokens[1]), std::stoi(tokens[2]), 
                std::stoi(tokens[3]), std::stoi(tokens[4]),
                std::stoi(tokens[5]), std::stoi(tokens[6]), std::stoi(tokens[7]), 
                std::stoi(tokens[8]),
                std::stoi(tokens[9]), std::stoi(tokens[10]), 
                std::stoi(tokens[11]), std::stoi(tokens[12]),
                std::stod(tokens[13]), std::stod(tokens[14])
            };
        }
        
        std::string toCSV() const {
            std::ostringstream oss;
            oss << id << "," << anno << "," << data << "," << idLocali << "," 
                << idOspiti << ","
                << ptLocali << "," << ptOspiti << "," << meteLocali << "," 
                << meteOspiti << ","
                << cartellinoRossoLoc << "," << cartellinoRossoOsp << ","
                << cartellinoGialloLoc << "," << cartellinoGialloOsp << ","
                << possessoLoc << "," << possessoOsp;
            return oss.str();
        }
    };
}

#endif

