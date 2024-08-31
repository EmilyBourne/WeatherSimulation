#include <iostream>
#include <cmath>
#include "montagne.h"
#include "proprietes_syst.h"

using namespace std;

//---------------La classe Montagne----------------------
	
double montagne::alti(double coordx, double coordy) const {
	double altitude(0);
	altitude = -(pow((coordx-centrex),2.0)/(2.0*pow(etalx,2.0)));
	altitude = altitude -(pow((coordy-centrey),2.0)/(2.0*pow(etaly,2.0)));
	altitude = hauteur*exp(altitude);
	
	if (altitude < 0.5){ altitude = 0; }
	
	return altitude;
}

	gros_chaine_mont* montagne::copie() const{
		return new montagne(*this);
	}

//constructeur
	montagne::montagne(double CX, double CY, double h, double EX, double EY)
	: centrex(CX), centrey(CY), hauteur(h), etalx(EX), etaly(EY)
	{}

//destructeur
	montagne::~montagne(){}
	
//get (peut être qu'on en aura pas besoin)
	double montagne::Cx() const { return centrex; }
	double montagne::Cy() const { return centrey; }
	double montagne::H() const { return hauteur; }
	double montagne::Ex() const { return etalx; }
	double montagne::Ey() const { return etaly; }
//set (peut être qu'on en aura pas besoin)
	double& montagne::Cx() { return centrex; }
	double& montagne::Cy() { return centrey; }
	double& montagne::H() { return hauteur; }
	double& montagne::Ex() { return etalx; }
	double& montagne::Ey() { return etaly; }

//fonction dessine de la classe dessinable
void montagne::dessine (std::ostream& flot) const {
	for(double a(0.0); a<Proprietes::nx; a=a+1.0){
		for(double b(0.0); b<Proprietes::ny; b=b+1.0){
			flot<< a<<" "<< b<<" "<< alt(a,b)<<endl;
		}
		flot<< endl;
	}
}
