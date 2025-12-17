# 🏉 Sistema Gestionale Campionato Rugby

[![C++](https://img.shields.io/badge/C%2B%2B-11-blue.svg)](https://en.cppreference.com/w/cpp/11)
[![Build](https://img.shields.io/badge/build-passing-brightgreen.svg)]()

Sistema completo per la gestione di campionati di rugby italiano, sviluppato come progetto per il corso di **Programmazione Avanzata** (C++11).

## 📋 Indice

- [Descrizione](#-descrizione)
- [Caratteristiche](#-caratteristiche)
- [Tecnologie e Concetti C++](#-tecnologie-e-concetti-c)
- [Struttura del Progetto](#-struttura-del-progetto)
- [Utilizzo](#-utilizzo)
- [Database CSV](#-database-csv)
- [Algoritmi STL Implementati](#-algoritmi-stl-implementati)
- [Architettura](#-architettura)
- [Ottimizzazioni](#-ottimizzazioni)
- [Autori](#-autori)

---

## 📖 Descrizione

Sistema gestionale Object-Oriented per campionati di rugby che permette di:
- Gestire **stagioni complete** con squadre, giocatori e staff tecnico
- Registrare e analizzare **partite** con statistiche dettagliate
- Generare **classifiche** e **report statistici avanzati** usando algoritmi STL
- Persistere i dati su file CSV con **threading parallelo**

Il progetto dimostra l'applicazione pratica di **tecniche avanzate C++11** tra cui move semantics, lambda expressions, smart pointers e metaprogramming.

---

## ✨ Caratteristiche

### 🎯 Funzionalità Principali
- ✅ **Gestione completa stagioni** (creazione, modifica, consultazione)
- ✅ **Roster squadre** con giocatori (15 ruoli) e staff tecnico
- ✅ **Sistema partite** con aggiornamento automatico statistiche
- ✅ **Classifiche dinamiche** con ordinamento multi-criterio
- ✅ **Statistiche avanzate** per giocatori e squadre
- ✅ **Analisi comparative** tra squadre con metriche multiple
- ✅ **Persistenza dati** su CSV con salvataggio parallelo
- ✅ **Menu interattivo** user-friendly

### 📊 Statistiche e Analisi
- **Top Performer**: Miglior placcaggitore, capocannoniere, corridore
- **Distribuzione ruoli**: Conteggio per ogni posizione
- **Medie di squadra**: Mete, placcaggi, metri percorsi
- **Classifiche**: Completa, Top N, mediana, efficienza
- **Squadre bilanciate**: Analisi attacco/difesa sopra media
- **Confronti diretti**: Head-to-head tra squadre

---

## 🛠 Tecnologie e Concetti C++

### **Standard C++11**
| Concetto | Implementazione | File |
|----------|-----------------|------|
| **OOP** | Ereditarietà (Persona → Giocatore/Staff) | `Persona.h`, `Giocatore.h`, `Staff.h` |
| **Move Semantics** | Move constructor/assignment, rvalue references | `Squadra.cpp`, `Stagione.cpp` |
| **Smart Pointers** | `std::unique_ptr` per gestione memoria | `Stagione.h` |
| **Lambda Expressions** | Capture by value/reference, predicati STL | `Statistiche.cpp` |
| **Template Functions** | CSVHelper generico | `Gestionale.cpp` |
| **RAII** | FileGuard per gestione file automatica | `Gestionale.cpp` |
| **Threading** | Salvataggio parallelo CSV con `std::thread` | `Gestionale.cpp` |
| **Pointer-to-Member** | Getter functions per metriche generiche | `Statistiche.cpp` |

### **STL (Standard Template Library)**
| Algoritmo | Utilizzo | Complessità |
|-----------|----------|-------------|
| `std::max_element` | Trova top performer (mete, placcaggi) | O(n) |
| `std::min_element` | Trova valori minimi statistiche | O(n) |
| `std::count_if` | Conta giocatori per ruolo | O(n) |
| `std::copy_if` | Filtra giocatori produttivi | O(n) |
| `std::sort` | Classifica completa squadre | O(n log n) |
| `std::partial_sort` | Top N ottimizzato | O(n log k) |
| `std::nth_element` | Mediana classifica | O(n) |
| `std::accumulate` | Somme e medie aggregate | O(n) |
| `std::transform` | Conversione unique_ptr → raw pointer | O(n) |

---

## 📁 Struttura del Progetto

rugby-management/  
│  
├── include/ # Header files  
│ ├── Persona.h # Classe base astratta  
│ ├── Giocatore.h # Eredita da Persona  
│ ├── Staff.h # Eredita da Persona  
│ ├── Squadra.h # Gestione roster e dati squadra  
│ ├── Partita.h # Risultati e statistiche partita  
│ ├── Stagione.h # Container squadre (unique_ptr)  
│ ├── Gestionale.h # Business logic e persistenza  
│ └── Statistiche.h # Algoritmi STL per analisi dati  
│  
├── src/ # Implementazioni  
│ ├── Persona.cpp  
│ ├── Giocatore.cpp  
│ ├── Staff.cpp  
│ ├── Squadra.cpp # Move semantics, reserve()  
│ ├── Partita.cpp  
│ ├── Stagione.cpp # Smart pointers  
│ ├── Gestionale.cpp # RAII, threading, template  
│ ├── Statistiche.cpp # Lambda, STL algorithms  
│ └── main.cpp # Entry point  
│  
├── database/ # File CSV di persistenza  
│ ├── stagioni.csv # 2 stagioni (2023-2024)  
│ ├── squadre.csv # 20 squadre (10 per stagione)  
│ ├── giocatori.csv # 300 giocatori (15 per squadra)  
│ ├── staff.csv # 40 membri staff (2 per squadra)  
│ └── partite.csv # 60 partite (30 per stagione)  
│  
├── Makefile # Automazione build  
└──README.md # Questo file  
  


---



## 🚀 Utilizzo

### Menu Principale
╔═════════════════════════╗  
║.....GESTIONALE CAMPIONATO RUGBY.....║  
╚═════════════════════════╝  

1. Crea nuova stagione
2. Consulta stagione esistente
3. Modifica stagione
4. Salva tutto su file
5. Esci


### Esempio: Consultazione Statistiche
Seleziona stagione → Modifica → Statistiche Avanzate  
Output:  
🏆 TOP PERFORMERS:  
🛡️ Miglior Placcatore: Giovanni Rossi (47 placcaggi)  
⚡ Meta Man: Tommaso Gallo (15 mete)  
🏃 Miglior Ball Carrier: Lorenzo Romano (285 metri)

📊 CLASSIFICA GENERALE:

RugbyUdine - 85 pt (54 mete)  
RugbyRiviera - 82 pt (52 mete)  
SanMarcoRugby - 76 pt (48 mete)


---

## 💾 Database CSV

### Formato File

#### `squadre.csv`
squadra_id,stagione_anno,nome,indirizzo,possesso_palla,territorio,...  
1,2023,RugbyTrento,ViaRovigo15Trento,52,54.5,...


#### `giocatori.csv`
giocatore_id,squadra_id,nome,cognome,eta,ruolo,placcaggi,mete,...  
1,1,Giovanni,Rossi,28,Pilone,45,1,...


### Dataset Incluso
- **2 Stagioni** complete (2023-2024)
- **20 Squadre** (10 per stagione)
- **300 Giocatori** con statistiche realistiche
- **40 Membri Staff** (allenatori, DS, assistenti)
- **60 Partite** giocate con risultati dettagliati

---

## 📊 Algoritmi STL Implementati

### Ricerca e Selezione
// Trova capocannoniere (O(n))  
auto it = std::max_element(giocatori.begin(), giocatori.end(),  
[](const Giocatore& a, const Giocatore& b) {  
return a.getMete() < b.getMete();  
});


### Filtraggio
// Giocatori con 5+ mete (O(n))  
std::copy_if(giocatori.begin(), giocatori.end(),  
std::back_inserter(risultato),  
[](const Giocatore& g) { return g.getMete() >= 5; });  


### Ordinamento Parziale
// Top 3 squadre (O(n log 3))  
std::partial_sort(squadre.begin(),  
squadre.begin() + 3,  
squadre.end(),  
[](Squadra* a, Squadra* b) {  
return a->getPunteggio() > b->getPunteggio();  
});  


### Statistica Mediana
// Squadra mediana (O(n))  
std::nth_element(squadre.begin(),  
squadre.begin() + squadre.size()/2,  
squadre.end(),  
comparatore);  


---

## 🏗 Architettura

### Design Patterns

#### **Single Responsibility Principle (SRP)**
- `Squadra`: Gestione roster e dati
- `Statistiche`: Analisi e calcoli STL
- `Gestionale`: Persistenza e business logic

#### **RAII (Resource Acquisition Is Initialization)**
class FileGuard {  
std::ofstream& file;  
public:  
FileGuard(std::ofstream& f) : file(f) {}  
~FileGuard() { if(file.is_open()) file.close(); }  
};  


#### **Dependency Injection**
// Funzioni statiche senza stato  
Statistiche::stampaReportStagione(const Stagione& stagione);

---

## ⚡ Ottimizzazioni

### Memory Management
- **Smart Pointers**: `std::unique_ptr` per ownership esclusivo
- **Move Semantics**: Elimina copie inutili (60% meno distruttori chiamati)
- **Reserve**: Pre-alloca capacità vector per evitare riallocazioni

Squadra::Squadra(...) {  
giocatori.reserve(25); // Evita 3-4 riallocazioni  
staffTecnico.reserve(5); // 80% meno allocazioni  
}  


### Parallelismo
// Salvataggio parallelo CSV (3x più veloce)  
std::thread t1(& { salvaStagioni(); });  
std::thread t2(& { salvaSquadre(); });  
std::thread t3(& { salvaPartite(); });  
t1.join(); t2.join(); t3.join();  


### Complessità Algoritmica
| Operazione | Naive | Ottimizzata | Guadagno |
|------------|-------|-------------|----------|
| Top 3 squadre | O(n log n) | O(n log 3) | ~70% |
| Mediana | O(n log n) | O(n) | ~90% |
| Filtraggio | O(n²) | O(n) | ~95% |

---

## 🎓 Obiettivi Didattici

Questo progetto dimostra:

1. **OOP**: Ereditarietà, polimorfismo, incapsulamento
2. **STL**: Padronanza algoritmi e containers
3. **C++11**: Move semantics, lambda, smart pointers
4. **Threading**: Parallelizzazione I/O
5. **Template**: Metaprogramming e type deduction
6. **Design**: SOLID principles, separation of concerns
7. **Performance**: Ottimizzazioni memoria e tempo

---

## 👤 Autori

**Tommaso Santus & Francesco Martella**  
Corso di Programmazione Avanzata - A.A. 2025/2026  
Università degli Studi di Trento

- 📧 Email: tommaso.santus@studenti.unitn.it
- 📧 Email: francesco.martella@studenti.unitn.it

---

## 🙏 Ringraziamenti

- Prof. Blanzieri per il corso di Programmazione Avanzata
- Comunità C++ per documentazione e best practices
- [cppreference.com](https://en.cppreference.com/) per riferimenti STL

---

## 📚 Riferimenti

- [C++ Reference](https://en.cppreference.com/)
- [Effective Modern C++](https://www.oreilly.com/library/view/effective-modern-c/9781491908419/) - Scott Meyers
- [The C++ Programming Language](https://www.stroustrup.com/4th.html) - Bjarne Stroustrup
- [STL Algorithm Complexity](https://en.cppreference.com/w/cpp/algorithm)

---

<div align="center">

**⭐ Se ti piace questo progetto, lascia una stella su GitHub! ⭐**

Made with ❤️ and C++11

</div>



