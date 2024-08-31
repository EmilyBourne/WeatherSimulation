#ifndef PRJ_MONTAGNE_LUE_H
#define PRJ_MONTAGNE_LUE_H
#include "dessinable.h"
#include "gros_chaines.h"
#include <fstream>
#include <string>
#include <vector>
#include "Vecteur2D.h"
//---------------La classe montagne_lue----------------------

class montagne_lue: public gros_chaine_mont {
	public:
	//prototypes des méthodes:
	virtual double alti(double coord1, double coord2) const ; //donne l'altitude au point x=coord1 y=coord2
	virtual gros_chaine_mont* copie() const;
	//constructeur
	montagne_lue(std::string fichier, double zscale);
	montagne_lue();
	//destructeur
	virtual ~montagne_lue();
	
	//affichage
	virtual void dessine(std::ostream& flot=std::cout) const;
	
	private:
	void genere_montagne(double h_over_nz);
	void genere_mont_carre(unsigned int x, unsigned int y, int pas, double echelle, vector<vector<double>>& creation);
	void genere_mont_diamand(unsigned int x, unsigned int y, int pas, double echelle, vector<vector<double>>& creation);
	
	double tirage();
	bool puissance_2(int nombre);
	int next_puissance_2(int nombre);
	//attributs
	std::string nom;
	std::vector<std::vector<double>> mont;
	
};

#endif // PRJ_MONTAGNE_LUE_H
