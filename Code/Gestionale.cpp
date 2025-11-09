#include "Gestionale.h"
#include <iostream>
using namespace std;

void Gestionale::avvia(){
	int scelta;
	
	do{
	
		cout << "\n=== MENU GESTIONALE ===\n";
		cout << "1) Crea nuova stagione\n";
		cout << "2) Aggiungi squadra a stagione\n";
		cout << "3) Aggiungi partita a stagione\n";
		cout << "4) Aggiungi giocatore a squadra\n";
		cout << "0) Esci\n";
		cin>> scelta;
	
		switch(scelta){
			case 1: creaStagione(); break;
			case 2: addSquadraToStagione(); break;
			case 3: addPartitaToStagione(); break;
			case 4: addGiocatoreToStagione();break;
		}
	}while( scelta!=0);
}

void Gestionale::creaStagione(){
	int anno;
	cout << "Inserisci anno stagione: ";
	cin >> anno;
	stagioni.push_back(unique_ptr<Stagione>(new Stagione(anno)));
}

Stagione* Gestionale::selezionaStagione(){
	if(stagioni.empty()){
		cout << "Nessuna stagione presente.\n";
		return nullptr;
	}
	
	cout << "selezionaStagione: \n";
	for(size_t i =0; i<stagioni.size(); i++)
		cout << i << ") " << *stagioni[i] << "\n";
	int i; 
    cin >> i;
    if(i < 0 || i >= (int)stagioni.size()) return nullptr;
    return stagioni[i].get();
	
}


void Gestionale::addSquadraToStagione(){
    Stagione* st = selezionaStagione();
    if(!st) return;

    string nome, indirizzo;
    int id;

    cout << "Nome squadra: ";
    cin >> nome;
    cout << "Indirizzo squadra: ";
    cin >> indirizzo;
    cout << "ID squadra: ";
    cin >> id;

    // C: creazione su heap e move
    st->addSquadra(std::unique_ptr<Squadra>(new Squadra(nome, indirizzo, id)));

    cout << "? Squadra aggiunta con successo.\n";
}


void Gestionale::addPartitaToStagione(){
    Stagione* st = selezionaStagione();
    if(!st) return;

    const auto& squadre = st->getSquadre();
    if(squadre.size() < 2){
        cout << "Servono almeno due squadre per creare una partita.\n";
        return;
    }
    
    cout << "Seleziona squadra locale:\n";
    for(size_t i=0;i<squadre.size();i++)
        cout << i << ") " << *squadre[i] << "\n";
    int iLocali; cin >> iLocali;
    
    cout << "Seleziona squadra ospite:\n";
    for(size_t i=0;i<squadre.size();i++)
        cout << i << ") " << *squadre[i] << "\n";
    int iOspiti; cin >> iOspiti;
    
    int idPartita, data;
    cout << "ID partita: ";
    cin >> idPartita;
    cout << "Data partita (AAAAMMGG): ";
    cin >> data;

    Partita p(idPartita, data, *squadre[iLocali], *squadre[iOspiti]);
    st->addPartita(p);

    cout << "Partita aggiunta.\n";
}

void Gestionale::addGiocatoreToStagione(){
    Stagione* st = selezionaStagione();
    if(!st) return;

    const auto& squadre = st->getSquadre();
    if(squadre.empty()){
        cout << "Nessuna squadra disponibile.\n";
        return;
    }

    cout << "Seleziona squadra:\n";
    for(size_t i=0;i<squadre.size();i++)
        cout << i << ") " << *squadre[i] << "\n";
    int index; cin >> index;

    string nome, cognome, ruolo;
    int eta, id;

    cout << "Nome giocatore: ";
    cin >> nome;
    cout << "Cognome giocatore: ";
    cin >> cognome;
    cout << "Età: ";
    cin >> eta;
    cout << "Ruolo: ";
    cin >> ruolo;
    cout << "ID: ";
    cin >> id;

    Giocatore g(nome, cognome, eta, ruolo, id);
    squadre[index]->addGiocatore(g);

    cout << "Giocatore aggiunto.\n";
}



