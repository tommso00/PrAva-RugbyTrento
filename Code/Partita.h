#ifndef PARTITA_H
#define PARTITA_H

#include "Squadra.h"
#include <string>
#include <iostream>




// Non usare "using namespace std;" nei file header
class Partita {
private:
    int id, data;
    Squadra locali;
    Squadra ospiti;
    
//Statistiche - Getter e Setter
	int cartellinoRossoLoc;
	int cartellinoRossoOsp;
	int cartellinoGialloLoc;
	int cartellinoGialloOsp;
	double possessoLoc;
	double possessoOsp;
	int ptLocali, ptOspiti;
    
    
    	
	

public:
    Partita(int id, int data, const Squadra& locali, const Squadra& ospiti);

    // Il distruttore di default è sufficiente: nessun puntatore o risorsa gestita manualmente
    ~Partita() = default;

	// GETTER aggiunti
    int getId() const;
    int getData() const;
    
    const Squadra& getLocali() const;
    const Squadra& getOspiti() const;
    
	int getPuntiLocali() const;
    int getPuntiOspiti() const;
	void setPuntiLocali(int value);
	void setPuntiOspiti(int value);
    
	int getCartellinoRossoLoc() const;
	void setCartellinoRossoLoc(int value);

	int getCartellinoRossoOsp() const;
	void setCartellinoRossoOsp(int value);

	int getCartellinoGialloLoc() const;
	void setCartellinoGialloLoc(int value);

	int getCartellinoGialloOsp() const;
	void setCartellinoGialloOsp(int value);

	double getPossessoLoc() const;
	void setPossessoLoc(double value);

	double getPossessoOsp() const;
	void setPossessoOsp(double value);

    int getPunteggioPartita() const; 
    void setRisultato(int ptLocali, int ptOspiti);
	

	
	
	




    // Serve lo scope std:: per ostream, non "using namespace std;"
    friend std::ostream& operator<<(std::ostream& os, const Partita& p);
};

#endif

