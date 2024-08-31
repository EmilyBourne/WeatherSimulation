#include "Systeme.h"
#include "constantes.h"
#include "proprietes_syst.h"
#include "rivers.h"

using namespace std;

void Systeme::initialise(double pas, double errmax, int itermax, bool verbeuse){
	initialise_c(pas,errmax,itermax, verbeuse);
	N = new nuages(*C);
	
	N->init_source_humi(*R,*M);

	Monde.push_back(N);
	T = new terrain(*M, *N);
	T->terrain::initialise(Proprietes::nz*0.6);
	Monde.push_back(T);
}

void Systeme::initialise_c(double pas, double errmax, int itermax, bool verbeuse){
	C->initialise(*M);
	C->resolution(pas, *M,errmax, itermax, verbeuse);
}

void Systeme::evolue(double pas_temps){
	N->evolue(pas_temps);
	T->evolue(pas_temps);
}

Systeme::Systeme(bool vide)
{
	if (vide==false) {
		M=new chaine_mont({{15.0,15.0,15.0,5.0,5.0}});
		C=new ChampPotentiels();
		N=nullptr;
		Monde={M, C};
	}
}

Systeme::Systeme(chaine_mont* mont, ChampPotentiels* champ)
: M(new chaine_mont({mont->copie()})), C(new ChampPotentiels(*champ)), T(nullptr), R(), Monde({M, C})
{}

Systeme::Systeme(chaine_mont* mont, ChampPotentiels* champ, mult_riv* river)
: M(new chaine_mont({mont->copie()})), C(new ChampPotentiels(*champ)), T(nullptr), R(river), Monde({river, M, C})
{}

Systeme::Systeme(chaine_mont* mont, ChampPotentiels* champ, nuages* cloud, terrain* ground, mult_riv* r)
: M(new chaine_mont({mont->copie()})), C(new ChampPotentiels(*champ)), N(cloud), T(ground), R(r), Monde({ground, r, cloud})
{}

vector<dessinable*>& Systeme::monde(){
	return Monde;
}

ChampPotentiels*& Systeme::c(){
	return C;
}

nuages*& Systeme::n(){
	return N;
}

terrain*& Systeme::t(){
	return T;
}

chaine_mont* Systeme::m(){
	return M;
}

mult_riv*& Systeme::r(){
	return R;
}

Systeme::~Systeme()
{
	for(size_t i(0); i<Monde.size(); i++){
		delete Monde[i];
	}
}

void Systeme::dessine (std::ostream& flot) const{
	for(size_t i(0); i < Monde.size(); i++){
		Monde[i]->dessine(flot);
	}
}

ostream& operator<< (ostream& a, Systeme const& Syst) {
	Syst.dessine(a);
	return a;
}

bool Systeme::orage_switch(bool onoff){
	return (N->orage_switch(onoff));
}

bool Systeme::orage_switch(){
	return (N->orage_switch());
}
