#include "cubed_air.h"
#include "constantes.h"
#include <cmath>
#include "proprietes_syst.h"
using namespace std;

//get
bool CubedAir::nuage () const { return cloud; }
std::vector<double> CubedAir::vitesse () const { return vit; }
double CubedAir::Tau() const {return tau; }

bool CubedAir::pleut() const {
	bool goutte(false);
	if(Pluie==true){
		goutte=true;
	}
	else{goutte = false;}
	return goutte;
}

int CubedAir::source_humi() const{return humi;}
int& CubedAir::source_humi(){return humi;}

//tau
void CubedAir::Tau(double p) {
	p=(p/100)+1;
	tau=tau*p;
}

int CubedAir::temp() const {return trunc(T); }
int CubedAir::press() const {return trunc(P/1000); }

//constructeur vide pour augmenter la vitesse quand on initialise un tableau de Cubes d'air
CubedAir::CubedAir () {}

//deuxième constructeur
CubedAir::CubedAir(std::vector<double> Vit, double Z, double const& h_infinie, double const& cte, double const& Tau)
: tau(Tau), vit(Vit), v2(pow(vit[0], 2) + pow(vit[1], 2) + pow(vit[2], 2)), z(Z), cloud(false), Pluie(false), humi(false)
{
	calculate(h_infinie, cte);
	pluie(0.1);
}

//fonction qui décide s'il y a un nuage ou pas
void CubedAir::calculate (double const& h_infinie, double const& cte) {
	set_values (h_infinie, cte);
	if (P_eau>P_rose) {
		cloud=true;
	}
	else {
		cloud=false;
	}
}

//calculer si il pleut ou pas
void CubedAir::pluie(double dt){
	if(cloud==true){
		if(P_eau>(P_rose+40)){
			Pluie = true;
			Tau((-2.5)*dt);
		}
		else{
			Pluie = false;
		}
	}
	else{
		Pluie = false;
	}
}

//calcule des valeurs necessaire pour décider s'il y a un nuage ou pas
void CubedAir::set_values(double const& h_infinie, double const& cte) {
	h=cte-Physique::g*z-v2/2.0;
	T=2*Physique::M_air_sec*h/(7*Physique::R);
	P=Proprietes::P_infinie*pow(Proprietes::T_infinie,(-7.0/2.0))*pow(T, 7.0/2.0);
	P_eau=tau*P/((Physique::M_eau/Physique::M_air_sec)+tau);
	P_rose=Proprietes::P_infinie*exp(13.96-(5208.0/T));
}

//fonction qui affiche des valeurs calculé
void CubedAir::affiche(std::ostream& flot) const {
	flot << ' ' << v2 << ' ' << h << ' ' << T << ' ' << P << ' ' << P_eau << ' ' << P_rose << ' ' << cloud << ' ' << Pluie << std::endl;
}

//fonction dessine du class dessinable
void CubedAir::dessine (std::ostream& flot) const {
	affiche(flot);
}
