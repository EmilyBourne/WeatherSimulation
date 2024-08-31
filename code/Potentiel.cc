#include "Potentiel.h"

using namespace std;
//---------------La classe Potentiel----------------------
//constructeur
Potentiel::Potentiel()
 : potentiel(0.0,0.0), laplacien(0.0,0.0)
 {}
 /* Potentiel::Potentiel(Vecteur2D p)
 * : potentiel(p), laplacien(0.0,0.0)
 * {}
 */
Potentiel::Potentiel(Vecteur2D p, Vecteur2D l)
	: potentiel(p), laplacien(l)
	{}
//set
	Vecteur2D& Potentiel::pot(){ return potentiel; }
	Vecteur2D& Potentiel::lapl(){ return laplacien; }
//get
	Vecteur2D Potentiel::pot() const{ return potentiel; }
	Vecteur2D Potentiel::lapl() const{ return laplacien; }
