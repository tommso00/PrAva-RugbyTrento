#include "Persona.h"
#include <iostream>

/**
 * @brief Costruttore principale Persona.
 */
Persona::Persona(const std::string& nome_, const std::string& cognome_, int eta_)
    : nome(nome_), cognome(cognome_), eta(eta_) {}

/**
 * @brief Distruttore virtuale per polimorfismo.
 */
Persona::~Persona() {}

/**
 * @brief Restituisce il nome della persona.
 */
std::string Persona::getNome() const {
    return nome;
}

/**
 * @brief Restituisce il cognome della persona.
 */
std::string Persona::getCognome() const {
    return cognome;
}

/**
 * @brief Restituisce l'età della persona.
 */
int Persona::getEta() const {
    return eta;
}

/**
 * @brief Stampa informazioni base Persona.
 */
void Persona::stampaInfo() const {
    std::cout << "Nome: " << nome << ", Cognome: " << cognome << ", Età: " << eta;
}

