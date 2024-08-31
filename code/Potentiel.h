#ifndef PRJ_POTENTIEL_H
#define PRJ_POTENTIEL_H
#include "Vecteur2D.h"

//---------------La classe Potentiel----------------------

class Potentiel {
	public:
	//constructeur
	Potentiel();
	/*Potentiel(Vecteur2D p);*/
	Potentiel(Vecteur2D p, Vecteur2D l);
	//set
	Vecteur2D& pot();
	Vecteur2D& lapl();
	//get
	Vecteur2D pot() const;
	Vecteur2D lapl() const;
	
	private:
	Vecteur2D potentiel;
	Vecteur2D laplacien;
};

#endif //PRJ_POTENTIEL_H
