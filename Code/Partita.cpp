#include "Partita.h"

/**
 * @brief Costruttore principale Partita.
 */
Partita::Partita(int id_, int data_, const Squadra& locali_, const Squadra& ospiti_) 
    : id(id_), data(data_), locali(locali_), ospiti(ospiti_), ptLocali(0), ptOspiti(0),cartellinoRossoLoc(0), cartellinoRossoOsp(0),
      cartellinoGialloLoc(0), cartellinoGialloOsp(0),
      possessoLoc(0.0), possessoOsp(0.0), meteLocali(0), meteOspiti(0)  {}

/**
 * @brief Formato stringa punteggio "X:Y".
 */
std::string Partita::getPunteggioPartita() const {
    return std::to_string(ptLocali) + ":" + std::to_string(ptOspiti);	
}

/**
 * @brief Imposta risultato partita.
 */
void Partita::setRisultato(int ptLocali_, int ptOspiti_) {
    ptLocali = ptLocali_;
    ptOspiti = ptOspiti_;
}

/**
 * @brief Punti squadra ospite.
 */
int Partita::getPuntiOspiti() const {
    return ptOspiti;
}

/**
 * @brief Punti squadra locale.
 */
int Partita::getPuntiLocali() const {
    return ptLocali;
}

/**
 * @brief Cartellini rossi locali.
 */
int Partita::getCartellinoRossoLoc() const {
    return cartellinoRossoLoc;
}

/**
 * @brief Imposta cartellini rossi locali.
 */
void Partita::setCartellinoRossoLoc(int value) {
    cartellinoRossoLoc = value;
}

/**
 * @brief Cartellini rossi ospiti.
 */
int Partita::getCartellinoRossoOsp() const {
    return cartellinoRossoOsp;
}

/**
 * @brief Imposta cartellini rossi ospiti.
 */
void Partita::setCartellinoRossoOsp(int value) {
    cartellinoRossoOsp = value;
}

/**
 * @brief Cartellini gialli locali.
 */
int Partita::getCartellinoGialloLoc() const {
    return cartellinoGialloLoc;
}

/**
 * @brief Imposta cartellini gialli locali.
 */
void Partita::setCartellinoGialloLoc(int value) {
    cartellinoGialloLoc = value;
}

/**
 * @brief Cartellini gialli ospiti.
 */
int Partita::getCartellinoGialloOsp() const {
    return cartellinoGialloOsp;
}

/**
 * @brief Imposta cartellini gialli ospiti.
 */
void Partita::setCartellinoGialloOsp(int value) {
    cartellinoGialloOsp = value;
}

/**
 * @brief Possesso palla locali (%).
 */
double Partita::getPossessoLoc() const {
    return possessoLoc;
}

/**
 * @brief Imposta possesso palla locali.
 */
void Partita::setPossessoLoc(double value) {
    possessoLoc = value;
}

/**
 * @brief Possesso palla ospiti (%).
 */
double Partita::getPossessoOsp() const {
    return possessoOsp;
}

/**
 * @brief Imposta possesso palla ospiti.
 */
void Partita::setPossessoOsp(double value) {
    possessoOsp = value;
}

/**
 * @brief Imposta punti locali.
 */
void Partita::setPuntiLocali(int value) {
    ptLocali = value;
}

/**
 * @brief Imposta punti ospiti.
 */
void Partita::setPuntiOspiti(int value) {
    ptOspiti = value;
}

/**
 * @brief Squadra ospite (costante).
 */
const Squadra& Partita::getOspiti() const {
    return ospiti;
}

/**
 * @brief Data partita.
 */
int Partita::getData() const {
    return data;
}

/**
 * @brief Squadra locale (costante).
 */
const Squadra& Partita::getLocali() const {
    return locali;
}

/**
 * @brief ID partita.
 */
int Partita::getId() const {
    return id;
}

/**
 * @brief Mete squadra locale.
 */
int Partita::getMeteLocali()const{
	return meteLocali;
}

/**
 * @brief Mete squadra ospite.
 */
int Partita::getMeteOspiti()const{
	return meteOspiti;
}

/**
 * @brief Imposta mete locali.
 */
void Partita::setMeteLocali(int val){
	meteLocali = val;
}

/**
 * @brief Imposta mete ospiti.
 */
void Partita::setMeteOspiti(int val){
	meteOspiti = val;
}

/**
 * @brief Overload operator<< per stampa Partita.
 */
std::ostream& operator<<(std::ostream& os, const Partita& p) {
 	os << "Partita ID: " << p.id << ", Data: " << p.data << "\n";
	os << "Squadre: " << p.locali.getNome() << " vs " << p.ospiti.getNome() << "\n";
	os << "Punteggio partita: " << p.ptLocali << ":" << p.ptOspiti;

/* 	os << "Partita ID: " << p.id << ", Data: " << p.data << "\n";
	os << "Locali: " << p.locali << " - Punti: " << p.ptLocali << "\n";
    os << "Ospiti: " << p.ospiti << " - Punti: " << p.ptOspiti;
*/  return os;
}

