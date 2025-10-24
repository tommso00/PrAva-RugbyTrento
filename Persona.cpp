#include "Persona.h"
#include <iostream>
using namespace std;

Persona::Persona(const string& nome, const string& cognome, int eta) : nome(nome), eta(eta), cognome(cognome) {}

string Persona::getNome() const { return nome; }
int Persona::getEta() const { return eta; }
string Persona::getCognome() const { return cognome;}

void Persona::stampaInfo() const {
    cout << "Nome: " << nome << " Cognome: " << cognome <<", Eta: " << eta;
}

Persona::~Persona(){
	cout << "Distruttore Persona---> " << nome << endl; 
}


