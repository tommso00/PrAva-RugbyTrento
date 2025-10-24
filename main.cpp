#include <iostream>
#include <memory>
#include "Stagione.h"
#include "Squadra.h"
#include "Giocatore.h"
#include "Staff.h"
#include "Partita.h"
using namespace std;


int main(int argc, char** argv) {
	
	
	//main di prova
	
	
	Stagione stagione2025(2025);

    // Creiamo le squadre
    unique_ptr<Squadra> s1(new Squadra("Trento Rugby", "Trento", 1));
	unique_ptr<Squadra> s2(new Squadra("Rovereto RFC", "Rovereto", 2));

    // Aggiungiamo alla stagione (ownership trasferita)
    stagione2025.addSquadra(move(s1));
    stagione2025.addSquadra(move(s2));
    // Creiamo partita snapshot
    Partita p1(1, 20250518, *stagione2025.getClassificaFinale(), *stagione2025.getClassificaFinale());
    stagione2025.addPartita(p1);

    cout << stagione2025;
	
	
	return 0;
}

