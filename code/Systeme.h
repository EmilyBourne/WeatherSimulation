#ifndef PRJ_SYSTEME_H
#define PRJ_SYSTEME_H
#include "dessinable.h"
#include "ChampPotentiels.h"
#include "nuages.h"
#include "chaines.h"
#include <vector>
#include "constantes.h"
#include "proprietes_syst.h"
#include "mult_riv.h"
#include "terrain.h"


class Systeme : public dessinable {
	public:
	virtual void dessine (std::ostream& flot=std::cout)const;
	virtual void initialise(double pas=0.1, double errmax=1e-4, int itermax=3000, bool verbeuse=false);
	void evolue(double pas_temps);
	bool orage_switch(bool onoff);
	bool orage_switch();
	
	Systeme(bool vide = false);
	virtual ~Systeme();
	Systeme(const Systeme& S) = delete;
	Systeme& operator=(const Systeme& S) = delete;
	
	private:
	chaine_mont* M;
	ChampPotentiels* C;
	nuages* N;
	terrain* T;
	mult_riv* R;
	
	vector<dessinable*> Monde;
	
	protected:
	Systeme(chaine_mont* mont, ChampPotentiels* champ);
	Systeme(chaine_mont* mont, ChampPotentiels* champ, mult_riv* river);
	Systeme(chaine_mont* mont, ChampPotentiels* champ, nuages* cloud, terrain* ground, mult_riv* r);
	vector<dessinable*>& monde();
	nuages*& n();
	ChampPotentiels*& c();
	chaine_mont* m();
	terrain*& t();
	mult_riv*& r();
	void initialise_c(double pas=0.1, double errmax=1e-4, int itermax=3000, bool verbeuse=false);
	
};

using namespace std;

ostream& operator<< (ostream& a, Systeme const& Syst);

#endif // PRJ_SYSTEME_H
