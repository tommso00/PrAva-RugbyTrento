#include "Persona.h"
#include <iostream>

// Costruttore
Persona::Persona(const std::string& nome_, const std::string& cognome_, int eta_)
    : nome(nome_), cognome(cognome_), eta(eta_) {}

// Distruttore virtuale, vuoto ma necessario per polymorphism corretto
Persona::~Persona() {}

// Getter
std::string Persona::getNome() const {
    return nome;
}

std::string Persona::getCognome() const {
    return cognome;
}

int Persona::getEta() const {
    return eta;
}

// Metodo virtuale per stampa informazioni
void Persona::stampaInfo() const {
    std::cout << "Nome: " << nome << ", Cognome: " << cognome << ", Età: " << eta;
}

