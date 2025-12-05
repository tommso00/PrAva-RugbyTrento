#include <iostream>
#include <stdexcept>
#include "Gestionale.h"

using namespace std;

int getScelta(int min, int max);

int main(int argc, char** argv) {
    Gestionale gest;
    int scelta = 0;

    do {
        cout << "Selezionare azione:" << endl
             << " 1) Carica stagione" << endl
             << " 2) Crea stagione" << endl
             << " 3) Esci" << endl;

        scelta = getScelta(1, 3);

        switch (scelta) {
            case 1:
                cout << "Selezionare stagione da caricare:" << endl;
                gest.selezionaStagione();
                break;

            case 2:
                gest.creaStagione();
                break;

            case 3:
                cout << "Arrivederci!" << endl;
                break;
        }

    } while (scelta != 3);

    return 0;
}

int getScelta(int min, int max) {
    int scelta;
    
    while (true) {
        try {
            cout << "Inserisci scelta: ";
            
            if (!(cin >> scelta)) {
                throw invalid_argument("Errore: inserire un numero intero valido.");
            }
            
            cin.ignore(10000, '\n');  // pulisce buffer
            
            if (scelta < min || scelta > max) {
                throw invalid_argument("ERR scelta non valida: inserire tra " + 
                                     to_string(min) + " e " + to_string(max));
            }
            
            return scelta;
            
        } catch (const invalid_argument& e) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << e.what() << endl;
            // continua il ciclo invece di ricorsione
        }
    }
}

