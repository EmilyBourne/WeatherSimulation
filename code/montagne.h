#ifndef PRJ_MONTAGNE_H
#define PRJ_MONTAGNE_H
#include "dessinable.h"
#include "gros_chaines.h"
//---------------La classe Montagne----------------------

class montagne: public gros_chaine_mont {
	public:
	//prototypes des méthodes:
	virtual double alti(double coord1, double coord2) const ; //donne l'altitude au point x=coord1 y=coord2
	virtual gros_chaine_mont* copie() const;
	//constructeur
	montagne(double centreX, double centreY, double hauteur, double etalementX, double etalementY);
	//destructeur
	virtual ~montagne();
	
	//get (peut être qu'on en aura pas besoin)
	double Cx() const;	//donne la coordonée x au centre
	double Cy() const;	//donne la coordonée y au centre
	double H() const;	//donne la hauteur de la montagne
	double Ex() const;	//donne l'étalement en x de la montagne
	double Ey() const;	//donne l'étalement en y de la montagne
	//set (peut être qu'on en aura pas besoin)
	double& Cx();		//paramètre la coordonée x au centre
	double& Cy();		//paramètre la coordonée y au centre
	double& H();		//paramètre la hauteur de la montagne
	double& Ex();		//paramètre l'étalement en x de la montagne
	double& Ey();		//paramètre l'étalement en y de la montagne
	
	//affichage
	virtual void dessine(std::ostream& flot=std::cout) const;
	
	private:
	//attributs
	double centrex;
	double centrey;
	double hauteur;
	double etalx;
	double etaly;
};

#endif // PRJ_MONTAGNE_H
