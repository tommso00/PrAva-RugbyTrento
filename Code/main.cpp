#include <iostream>
#include <cstdlib>
#include <memory>
#include <stdexcept>
#include "Gestionale.h"

using namespace std;

int getScelta(int min, int max);

int main(int argc, char** argv) {
	
	Gestionale gest;
	int scelta=0;
	
	cout<< "Selezionare azione:"<<endl<<" 1) Carica stagione"<<endl<<" 2) Crea stagione"<<endl<<" 3) Esci"<<endl;
	
	do{
		scelta = getScelta(0,3);
		switch (scelta) {
		    case 1:
		        // Carica Stagione
		        cout<<"Selezionare stagione da caricare:"<<endl;
		        //gest.fetchStagioni();
		        //gest.selezionaStagioni();
		        //gest.modificaStagione();
		        break;
		    case 2:
		        // Crea Stagione
		        gest.creaStagione();
		        
		        break;
		    default:
		        // Ultimo caso: esci
		        system("cls"); 
		        cout<<"Arrivederci!"<<endl;
		        break;
		}
	}while(scelta!=3);
	



	
	
	
	
	/*

    Stagione stagione2025(2025);

    Giocatore g1("Mario", "Rossi", 28, "Mediano", 1);
    Giocatore g2("Luca", "Bianchi", 25, "Ala", 2);
    Giocatore g3("Gianni", "Verdi", 30, "Pilone", 3);

    unique_ptr<Squadra> s1(new Squadra("Trento Rugby", "Trento", 1));
    s1->addGiocatore(g1);
    s1->addGiocatore(g2);
    s1->setPunteggio(15);

    unique_ptr<Squadra> s2(new Squadra("Rovereto RFC", "Rovereto", 2));
    s2->addGiocatore(g3);
    s2->setPunteggio(20);

    // Salvo i puntatori raw prima di passare ownership
    const Squadra* ptrS1 = s1.get();
    const Squadra* ptrS2 = s2.get();

    stagione2025.addSquadra(move(s1));
    stagione2025.addSquadra(move(s2));

    // Creo partita tra due squadre diverse
    Partita p1(1, 20250518, *ptrS1, *ptrS2);
    p1.setRisultato(30, 25);
    stagione2025.addPartita(p1);

    // Mostro squadra vincente
    const Squadra* vincente = stagione2025.getClassificaFinale();
    if (vincente) {
        cout << "Squadra vincente della stagione: \n" << *vincente << endl;
    } else {
        cout << "Nessuna squadra in stagione." << endl;
    }

    // Stampo calendario partite
    cout << "\nCalendario partite:\n";
    for (const auto& p : stagione2025.getCalendario()) {
        cout << p << "\n\n";
    }

    // Riepilogo stagione
    cout << "\nRiepilogo stagione:\n" << stagione2025;
    */


    return 0;
}

int getScelta(int min, int max){
	int temp;
		try{
		cin>>temp;
		if(temp<min || temp>max){throw invalid_argument("ERR scelta non valida");}
	}catch(const invalid_argument& e){
		cout<< e.what()<<endl;
		temp = getScelta(min, max);
	}
	return temp;
}

