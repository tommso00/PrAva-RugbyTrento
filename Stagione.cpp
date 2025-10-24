#include "Stagione.h"
using namespace std;

Stagione::Stagione(int anno) : anno(anno) {}

Stagione::~Stagione() {
    cout << "Distruttore Stagione " << anno << " chiamato" << endl;
	// distrutte automaticamente grazie a unique_ptr :)

}

Squadra* Stagione::getClassificaFinale() {
    if (squadre.empty()) return nullptr;
    Squadra* a = squadre[0].get();
    for (const auto& s : squadre){
        if (s->getPunteggio() > a->getPunteggio()){
  	        a = s.get();
		}
	}
	return a;
}

const vector<Partita>& Stagione::getCalendario() const{
    return partite;
}

void Stagione::addSquadra(unique_ptr<Squadra> s) {
    squadre.push_back(move(s));
}

void Stagione::addPartita(const Partita& p) {
    partite.push_back(p);
}

ostream& operator<<(ostream& os, const Stagione& s) {
    os << "Stagione: " << s.anno << endl;
    os << "Squadre partecipanti:" << endl;
    for (const auto& squadra : s.squadre)
        os << " - " << squadra->getNome() << endl;
    os << "Partite:" << endl;
    for (const auto& p : s.partite)
        os << " - " << p << endl;
    return os;
}


