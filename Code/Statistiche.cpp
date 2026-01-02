#include "Statistiche.h"
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iostream>
#include <iomanip>

/**
 * @brief Ruoli standard rugby (costante statica).
 */
const std::vector<std::string> Statistiche::RUOLI_STANDARD = {
    "Pilone", "Tallonatore", "SecondaLinea", 
    "TerzaLineaCentro", "TerzaLineaAla",
    "Mediano", "Apertura", 
    "CentroThreeQuarter", "AlaThreeQuarter", "Estremo"
};

// ==================== STATISTICHE X GIOCATORI ====================

/**
 * @brief Trova giocatore con più placcaggi usando std::max_element.
 */
// Lezione 7: std::max_element con lambda comparator
const Giocatore* Statistiche::getMigliorPlaccatore(const Squadra& squadra) {
    const auto& giocatori = squadra.getGiocatori();
    if (giocatori.empty()) return nullptr;
    
    auto confrontaPlaccaggi = [](const Giocatore& a, const Giocatore& b) {
        return a.getPlaccaggi() < b.getPlaccaggi();
    };
    
    auto it = std::max_element(giocatori.begin(), giocatori.end(), confrontaPlaccaggi);
    return &(*it);
}

/**
 * @brief Meta Man della squadra (più mete).
 */
// Lezione 7: std::max_element inline lambda
const Giocatore* Statistiche::getMetaMan(const Squadra& squadra) {
    const auto& giocatori = squadra.getGiocatori();
    if (giocatori.empty()) return nullptr;
    
    auto it = std::max_element(giocatori.begin(), giocatori.end(),
        [](const Giocatore& a, const Giocatore& b) {
            return a.getMete() < b.getMete();
        });
    
    return &(*it);
}

/**
 * @brief Giocatore con più metri percorsi con palla.
 */
const Giocatore* Statistiche::getMigliorCorridore(const Squadra& squadra) {
    const auto& giocatori = squadra.getGiocatori();
    if (giocatori.empty()) return nullptr;
    
    auto it = std::max_element(giocatori.begin(), giocatori.end(),
        [](const Giocatore& a, const Giocatore& b) {
            return a.getMetriCorsi() < b.getMetriCorsi();
        });
    
    return &(*it);
}

/**
 * @brief Conta giocatori per ruolo (std::count_if + lambda capture).
 */
int Statistiche::contaGiocatoriPerRuolo(const Squadra& squadra, const std::string& ruolo) {
    const auto& giocatori = squadra.getGiocatori();
    
    auto haStoRuolo = [&ruolo](const Giocatore& g) {
        return g.getRuolo() == ruolo;
    };
    
    return std::count_if(giocatori.begin(), giocatori.end(), haStoRuolo);
}

/**
 * @brief Filtra giocatori con mete = soglia (std::copy_if).
 */
std::vector<Giocatore> Statistiche::giocatoriConMeteSopra(const Squadra& squadra, int soglia) {
    const auto& giocatori = squadra.getGiocatori();
    std::vector<Giocatore> risultato;
    risultato.reserve(giocatori.size());
    
    auto superaSoglia = [soglia](const Giocatore& g) {
        return g.getMete() >= soglia;
    };
    
    std::copy_if(giocatori.begin(), giocatori.end(), 
                 std::back_inserter(risultato),
                 superaSoglia);
    
    return risultato;
}

/**
 * @brief Filtra giocatori con placcaggi = soglia (std::copy_if).
 */
std::vector<Giocatore> Statistiche::giocatoriConPlaccaggiSopra(const Squadra& squadra, int soglia) {
    const auto& giocatori = squadra.getGiocatori();
    std::vector<Giocatore> risultato;
    risultato.reserve(giocatori.size());
    
    std::copy_if(giocatori.begin(), giocatori.end(), 
                 std::back_inserter(risultato),
                 [soglia](const Giocatore& g) {
                     return g.getPlaccaggi() >= soglia;
                 });
    
    return risultato;
}

/**
 * @brief Media aritmetica mete per giocatore (std::accumulate).
 */
double Statistiche::mediaMetePerGiocatore(const Squadra& squadra) {
    const auto& giocatori = squadra.getGiocatori();
    if (giocatori.empty()) return 0.0;
    
    int totale = std::accumulate(giocatori.begin(), giocatori.end(), 0,
        [](int acc, const Giocatore& g) {
            return acc + g.getMete();
        });
    
    return static_cast<double>(totale) / giocatori.size();
}

/**
 * @brief Media aritmetica placcaggi per giocatore (std::accumulate).
 */
double Statistiche::mediaPlaccaggiPerGiocatore(const Squadra& squadra) {
    const auto& giocatori = squadra.getGiocatori();
    if (giocatori.empty()) return 0.0;
    
    int totale = std::accumulate(giocatori.begin(), giocatori.end(), 0,
        [](int acc, const Giocatore& g) {
            return acc + g.getPlaccaggi();
        });
    
    return static_cast<double>(totale) / giocatori.size();
}

/**
 * @brief Distribuzione giocatori per ruolo standard.
 */
std::map<std::string, int> Statistiche::distribuzioneRuoli(const Squadra& squadra) {
    std::map<std::string, int> distribuzione;
    
    for (const auto& ruolo : RUOLI_STANDARD) {
        distribuzione[ruolo] = contaGiocatoriPerRuolo(squadra, ruolo);
    }
    
    return distribuzione;
}

/**
 * @brief Stampa report statistico completo squadra.
 */
void Statistiche::stampaReportSquadra(const Squadra& squadra) {
    std::cout << "\n+----------------------------------------------------+\n";
    std::cout << "¦          REPORT STATISTICO SQUADRA                 ¦\n";
    std::cout << "+----------------------------------------------------+\n";
    
    std::cout << "\n " << squadra.getNome() << " \n";
    
    // TOP PERFORMERS
    std::cout << "\n TOP PERFORMERS:\n";
    
    const Giocatore* migliorPlaccatore = getMigliorPlaccatore(squadra);
    if (migliorPlaccatore) {
        std::cout << "   # Miglior Placcatore: " 
                  << migliorPlaccatore->getNome() << " " 
                  << migliorPlaccatore->getCognome()
                  << " (" << migliorPlaccatore->getPlaccaggi() << " placcaggi)\n";
    }
    
    const Giocatore* MetaMan = getMetaMan(squadra);
    if (MetaMan) {
        std::cout << "  # Meta Man: " 
                  << MetaMan->getNome() << " " 
                  << MetaMan->getCognome()
                  << " (" << MetaMan->getMete() << " mete)\n";
    }
    
    const Giocatore* migliorCorridore = getMigliorCorridore(squadra);
    if (migliorCorridore) {
        std::cout << "  # Miglior Ball Carrier: " 
                  << migliorCorridore->getNome() << " " 
                  << migliorCorridore->getCognome()
                  << " (" << migliorCorridore->getMetriCorsi() << " metri)\n";
    }
    
    // MEDIE
    std::cout << "\n MEDIE DI SQUADRA:\n";
    std::cout << "  # Media mete per giocatore: " 
              << std::fixed << std::setprecision(2) 
              << mediaMetePerGiocatore(squadra) << "\n";
    std::cout << "  # Media placcaggi per giocatore: " 
              << std::fixed << std::setprecision(2) 
              << mediaPlaccaggiPerGiocatore(squadra) << "\n";
    
    // DISTRIBUZIONE RUOLI
    std::cout << "\n DISTRIBUZIONE RUOLI:\n";
    auto distribuzione = distribuzioneRuoli(squadra);
    for (const auto& pair : distribuzione) {
        if (pair.second > 0) {
            std::cout << "  # " << std::setw(20) << std::left 
                      << pair.first << ": " << pair.second << "\n";
        }
    }
    
    // GIOCATORI PRODUTTIVI
    std::cout << "\n GIOCATORI PRODUTTIVI:\n";
    auto topScorer = giocatoriConMeteSopra(squadra, 5);
    std::cout << "  # Con 5+ mete: " << topScorer.size() << "\n";
    for (const auto& g : topScorer) {
        std::cout << "      @ " << g.getNome() << " " << g.getCognome() 
                  << " (" << g.getMete() << " mete)\n";
    }
    
    auto difensori = giocatoriConPlaccaggiSopra(squadra, 30);
    std::cout << "  # Con 30+ placcaggi: " << difensori.size() << "\n";
    for (const auto& g : difensori) {
        std::cout << "      @ " << g.getNome() << " " << g.getCognome() 
                  << " (" << g.getPlaccaggi() << " placcaggi)\n";
    }
    
    std::cout << "\n----------------------------------------------------\n";
}

// ==================== STATISTICHE STAGIONE ====================

/**
 * @brief Classifica completa (std::sort + std::transform).
 */
std::vector<Squadra*> Statistiche::classificaCompleta(const Stagione& stagione) {
    const auto& squadre = stagione.getSquadre();
    std::vector<Squadra*> classifica;
    classifica.reserve(squadre.size());
    
    std::transform(squadre.begin(), squadre.end(), 
                   std::back_inserter(classifica),
                   [](const std::unique_ptr<Squadra>& sq) { return sq.get(); });
    
    std::sort(classifica.begin(), classifica.end(),
        [](Squadra* a, Squadra* b) {
            if (a->getPunteggio() != b->getPunteggio()) {
                return a->getPunteggio() > b->getPunteggio();
            }
            return a->getMeteTotali() > b->getMeteTotali();
        });
    
    return classifica;
}

/**
 * @brief Top N squadre (std::partial_sort ottimizzato).
 */
std::vector<Squadra*> Statistiche::topNSquadre(const Stagione& stagione, size_t n) {
    const auto& squadre = stagione.getSquadre();
    std::vector<Squadra*> risultato;
    risultato.reserve(squadre.size());
    
    std::transform(squadre.begin(), squadre.end(), 
                   std::back_inserter(risultato),
                   [](const std::unique_ptr<Squadra>& sq) { return sq.get(); });
    
    if (n < risultato.size()) {
        std::partial_sort(risultato.begin(), 
                          risultato.begin() + n, 
                          risultato.end(),
                          [](Squadra* a, Squadra* b) {
                              return a->getPunteggio() > b->getPunteggio();
                          });
        risultato.resize(n);
    } else {
        std::sort(risultato.begin(), risultato.end(),
                  [](Squadra* a, Squadra* b) {
                      return a->getPunteggio() > b->getPunteggio();
                  });
    }
    
    return risultato;
}

/**
 * @brief Squadra mediana classifica (std::nth_element O(n)).
 */
Squadra* Statistiche::squadraMediana(const Stagione& stagione) {
    const auto& squadre = stagione.getSquadre();
    if (squadre.empty()) return nullptr;
    
    std::vector<Squadra*> temp;
    temp.reserve(squadre.size());
    
    std::transform(squadre.begin(), squadre.end(), 
                   std::back_inserter(temp),
                   [](const std::unique_ptr<Squadra>& sq) { return sq.get(); });
    
    size_t mid = temp.size() / 2;
    std::nth_element(temp.begin(), 
                     temp.begin() + mid, 
                     temp.end(),
                     [](Squadra* a, Squadra* b) {
                         return a->getPunteggio() < b->getPunteggio();
                     });
    
    return temp[mid];
}

/**
 * @brief Confronta due squadre su 5 metriche.
 */
std::map<std::string, int> Statistiche::confrontaSquadre(const Squadra& sq1, const Squadra& sq2) {
    std::map<std::string, int> confronto;
    
    confronto["punti"] = sq1.getPunteggio() - sq2.getPunteggio();
    confronto["mete"] = sq1.getMeteTotali() - sq2.getMeteTotali();
    confronto["placcaggi"] = sq1.getPlaccaggiTotali() - sq2.getPlaccaggiTotali();
    confronto["metri"] = sq1.getMetriGuadagnatiTotali() - sq2.getMetriGuadagnatiTotali();
    confronto["possesso"] = sq1.getPossessoPalla() - sq2.getPossessoPalla();
    
    return confronto;
}

/**
 * @brief Squadra leader per metrica specifica.
 */
Squadra* Statistiche::squadraMigliorePerMetrica(const Stagione& stagione, const std::string& metrica) {
    const auto& squadre = stagione.getSquadre();
    if (squadre.empty()) return nullptr;
    
    auto it = squadre.begin();
    
    if (metrica == "mete") {
        it = std::max_element(squadre.begin(), squadre.end(),
            [](const std::unique_ptr<Squadra>& a, const std::unique_ptr<Squadra>& b) {
                return a->getMeteTotali() < b->getMeteTotali();
            });
    } else if (metrica == "placcaggi") {
        it = std::max_element(squadre.begin(), squadre.end(),
            [](const std::unique_ptr<Squadra>& a, const std::unique_ptr<Squadra>& b) {
                return a->getPlaccaggiTotali() < b->getPlaccaggiTotali();
            });
    } else {
        it = std::max_element(squadre.begin(), squadre.end(),
            [](const std::unique_ptr<Squadra>& a, const std::unique_ptr<Squadra>& b) {
                return a->getPunteggio() < b->getPunteggio();
            });
    }
    
    return it->get();
}

/**
 * @brief Media metrica squadre (pointer-to-member + std::accumulate).
 */
double Statistiche::mediaMetrica(const Stagione& stagione, int (Squadra::*getter)() const) {
    const auto& squadre = stagione.getSquadre();
    if (squadre.empty()) return 0.0;
    
    int somma = std::accumulate(squadre.begin(), squadre.end(), 0,
        [getter](int acc, const std::unique_ptr<Squadra>& sq) {
            return acc + (sq.get()->*getter)();
        });
    
    return static_cast<double>(somma) / squadre.size();
}

/**
 * @brief Deviazione standard metrica (pointer-to-member).
 */
double Statistiche::deviazioneStandard(const Stagione& stagione, int (Squadra::*getter)() const) {
    const auto& squadre = stagione.getSquadre();
    if (squadre.size() < 2) return 0.0;
    
    double media = mediaMetrica(stagione, getter);
    
    double sommaScartiQuadrati = std::accumulate(squadre.begin(), squadre.end(), 0.0,
        [getter, media](double acc, const std::unique_ptr<Squadra>& sq) {
            double valore = (sq.get()->*getter)();
            double scarto = valore - media;
            return acc + (scarto * scarto);
        });
    
    return std::sqrt(sommaScartiQuadrati / squadre.size());
}

/**
 * @brief Minimo valore metrica (std::min_element).
 */
int Statistiche::minimoMetrica(const Stagione& stagione, int (Squadra::*getter)() const) {
    const auto& squadre = stagione.getSquadre();
    if (squadre.empty()) return 0;
    
    auto it = std::min_element(squadre.begin(), squadre.end(),
        [getter](const std::unique_ptr<Squadra>& a, const std::unique_ptr<Squadra>& b) {
            return (a.get()->*getter)() < (b.get()->*getter)();
        });
    
    return (it->get()->*getter)();
}

/**
 * @brief Massimo valore metrica (std::max_element).
 */
int Statistiche::massimoMetrica(const Stagione& stagione, int (Squadra::*getter)() const) {
    const auto& squadre = stagione.getSquadre();
    if (squadre.empty()) return 0;
    
    auto it = std::max_element(squadre.begin(), squadre.end(),
        [getter](const std::unique_ptr<Squadra>& a, const std::unique_ptr<Squadra>& b) {
            return (a.get()->*getter)() < (b.get()->*getter)();
        });
    
    return (it->get()->*getter)();
}

/**
 * @brief Squadre con attacco/difesa sopra media.
 */
std::vector<Squadra*> Statistiche::squadreBilanciate(const Stagione& stagione) {
    double mediaMete = mediaMetrica(stagione, &Squadra::getMeteTotali);
    double mediaPlaccaggi = mediaMetrica(stagione, &Squadra::getPlaccaggiTotali);
    
    const auto& squadre = stagione.getSquadre();
    std::vector<Squadra*> risultato;
    
    for (const auto& sq : squadre) {
        if (sq->getMeteTotali() >= mediaMete && sq->getPlaccaggiTotali() >= mediaPlaccaggi) {
            risultato.push_back(sq.get());
        }
    }
    
    return risultato;
}

/**
 * @brief Classifica efficienza punti/mete (std::sort pair).
 */
std::vector<std::pair<Squadra*, double>> Statistiche::classificaEfficienza(const Stagione& stagione) {
    const auto& squadre = stagione.getSquadre();
    std::vector<std::pair<Squadra*, double>> efficienza;
    
    for (const auto& sq : squadre) {
        double eff = (sq->getMeteTotali() > 0) 
            ? static_cast<double>(sq->getPunteggio()) / sq->getMeteTotali()
            : 0.0;
        efficienza.push_back(std::make_pair(sq.get(), eff));
    }
    
    std::sort(efficienza.begin(), efficienza.end(),
        [](const std::pair<Squadra*, double>& a, const std::pair<Squadra*, double>& b) {
            return a.second > b.second;
        });
    
    return efficienza;
}

/**
 * @brief Stampa report statistico completo stagione.
 */
void Statistiche::stampaReportStagione(const Stagione& stagione) {
    std::cout << "\n+----------------------------------------------------------+\n";
    std::cout << "¦          REPORT STATISTICO STAGIONE " << stagione.getAnno() << "              ¦\n";
    std::cout << "+----------------------------------------------------------+\n";
    
    // CLASSIFICA
    std::cout << "\n CLASSIFICA GENERALE:\n";
    auto classifica = classificaCompleta(stagione);
    for (size_t i = 0; i < classifica.size(); ++i) {
        std::cout << "  " << std::setw(2) << (i+1) << ". " 
                  << std::setw(25) << std::left << classifica[i]->getNome()
                  << " - " << std::setw(3) << classifica[i]->getPunteggio() << " pt"
                  << " (" << classifica[i]->getMeteTotali() << " mete)\n";
    }
    
    // TOP 3
    std::cout << "\n PODIO:\n";
    auto top3 = topNSquadre(stagione, 3);
    for (size_t i = 0; i < top3.size() && i < 3; ++i) {
        std::string medaglia = (i == 0) ? "1." : (i == 1) ? "2." : "3.";
        std::cout << "  " << medaglia << " " << top3[i]->getNome() 
                  << " (" << top3[i]->getPunteggio() << " pt)\n";
    }
    
    // STATISTICHE AGGREGATE
    std::cout << "\n STATISTICHE GENERALI:\n";
    std::cout << "  # Media punti: " << std::fixed << std::setprecision(1) 
              << mediaMetrica(stagione, &Squadra::getPunteggio) << "\n";
    std::cout << "  # Deviazione std punti: " << std::fixed << std::setprecision(2)
              << deviazioneStandard(stagione, &Squadra::getPunteggio) << "\n";
    std::cout << "  # Range punti: " << minimoMetrica(stagione, &Squadra::getPunteggio)
              << " - " << massimoMetrica(stagione, &Squadra::getPunteggio) << "\n";
    
    // MIGLIORI PER CATEGORIA
    std::cout << "\n MIGLIORI PER CATEGORIA:\n";
    auto miglioriMete = squadraMigliorePerMetrica(stagione, "mete");
    if (miglioriMete) {
        std::cout << "   Attacco: " << miglioriMete->getNome() 
                  << " (" << miglioriMete->getMeteTotali() << " mete)\n";
    }
    
    auto miglioriPlaccaggi = squadraMigliorePerMetrica(stagione, "placcaggi");
    if (miglioriPlaccaggi) {
        std::cout << "    Difesa: " << miglioriPlaccaggi->getNome() 
                  << " (" << miglioriPlaccaggi->getPlaccaggiTotali() << " placcaggi)\n";
    }
    
    // SQUADRE BILANCIATE
    std::cout << "\n  SQUADRE BILANCIATE (attacco E difesa sopra media):\n";
    auto bilanciate = squadreBilanciate(stagione);
    for (const auto& sq : bilanciate) {
        std::cout << "  # " << sq->getNome() << "\n";
    }
    
    // EFFICIENZA
    std::cout << "\n TOP 5 EFFICIENZA (punti/mete):\n";
    auto efficienze = classificaEfficienza(stagione);
    for (size_t i = 0; i < efficienze.size() && i < 5; ++i) {
        std::cout << "  " << (i+1) << ". " << efficienze[i].first->getNome()
                  << " - " << std::fixed << std::setprecision(2) 
                  << efficienze[i].second << " pt/meta\n";
    }

}

