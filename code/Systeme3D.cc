#include "Systeme3D.h"
#include "constantes.h"
#include "nuages3D.h"
#include "proprietes_syst.h"
#include "montagne_lue.h"
#include "rivers3D.h"
#include "terrain3D.h"

using namespace std;

void Systeme3D::initialise(double pas, double errmax, int itermax, bool verbeuse){
	if (monde().size()==0) {
		monde().push_back(new rivers3D(m()));
	}
	initialise_c(pas,errmax, itermax, verbeuse);
	n() = new nuages3D(*c());
		
	n()->init_source_humi(*r(),*m());
	
	t() = new terrain3D(*m(), *n());
	t()->initialise(Proprietes::nz*0.6);
	monde().push_back(t());
	monde().push_back(n());
}

Systeme3D::Systeme3D()
: Systeme((new chaine_mont({{15.0,15.0,15.0,5.0,5.0},{10.0,10.0,10.0,3.0,3.0},{20.0,10.0,10.0,3.0,3.0}})),(new ChampPotentiels())) //les contagnes "clown"
{
	monde().pop_back();
	monde().pop_back();
}

Systeme3D::Systeme3D(string fichier, double zscale)
: Systeme((new chaine_mont(fichier, zscale)),(new ChampPotentiels()))
{
	monde().pop_back();
	monde().pop_back();
}

Systeme3D::Systeme3D(chaine_mont* mont, ChampPotentiels* champ, mult_riv* river)
: Systeme(mont, champ, river)
{
	monde().pop_back();
	monde().pop_back();
}

Systeme3D::Systeme3D(chaine_mont* mont, ChampPotentiels* champ, nuages* cloud, terrain* ground, mult_riv* r)
: Systeme(mont, champ, cloud, ground, r)
{}

Systeme3D::Systeme3D(bool vide)
: Systeme((new chaine_mont({new montagne_lue()})),(new ChampPotentiels()))
{
	monde().pop_back();
	monde().pop_back();
}

Systeme3D::~Systeme3D()
{}

void Systeme3D::dessine (std::ostream& flot) const{
	Systeme::dessine(flot);
}

ostream& operator<< (ostream& a, Systeme3D const& Syst) {
	Syst.dessine(a);
	return a;
}


void Systeme3D::parametre (unsigned int code_param, unsigned int changement){
		switch(code_param)
    {
         // change l'affichage de la pression
        case 121:
            n()->parametre(1,changement);
            break;
        // change l'affichage de la temperature       
        case 122:
             n()->parametre(2,changement);
             break;
    }
}
