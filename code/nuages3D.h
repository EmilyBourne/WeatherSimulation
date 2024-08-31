#ifndef PRJ_NUAGES3D_H
#define PRJ_NUAGES3D_H

#include "nuages.h"



class nuages3D : public nuages
{
	public:
		//constructeur
		nuages3D (ChampPotentiels c) : nuages(c) {};
		nuages3D (ChampPotentiels c, gros_chaine_mont* m);
		//méthodes d'affichage
		virtual void dessine (std::ostream& flot=std::cout) const;
		virtual bool nuage_ici(unsigned int i,unsigned int j,unsigned int k) const;
		//set
		bool& Pression();
		bool& Temperature();
		//codes parametre	: (1) affiche_press 		, (2) affiche_temp
		//codes changement	: (1)/ (1)true (0) false	, (2)/ (1) true (0) false
		virtual void parametre (unsigned int code_param, unsigned int changement);
	private:
		bool affiche_pression;
		bool affiche_temperature;
		gros_chaine_mont* M;
		string inttostring (int i) const;
	
};

#endif 
