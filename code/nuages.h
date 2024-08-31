#ifndef PRJ_NUAGES_H
#define PRJ_NUAGES_H

#include <iostream>
#include "cubed_air.h"
#include <vector>
#include "ChampPotentiels.h"
#include "dessinable.h"
#include "rivers.h"
#include "gros_chaines.h"

//definition du ciel comme des cubes dans 3 dimensions
typedef std::vector<std::vector<std::vector<CubedAir>>> ciel;

class nuages : public dessinable {
	public:
		//constructeur
		nuages (ChampPotentiels c);
		//méthodes d'affichage
		void affiche (std::ostream& flot=cout) const;
		virtual void dessine (std::ostream& flot=std::cout) const;
		//évolution
		void evolue_nuage (double pas_de_temps);
		void evolue(double pas);
		void pluie (double dt);
		void calculate ();
		virtual bool nuage_ici(unsigned int i,unsigned int j,unsigned int k) const;
		bool pluie_ici(unsigned int i,unsigned int j, unsigned int k) const;
		bool pluie_au_sol(unsigned int i,unsigned int j) const;
		void init_source_humi(mult_riv& R,  gros_chaine_mont& M);
		
		void orage_go();
		void orage_stop();
		
		bool orage_switch(bool onoff);
		bool orage_switch();
		
	private:
		void initialise_sky(ChampPotentiels C);
		//fonctions
		std::vector<double> precedente (double pas_de_temps, int i, int j, int k) const;
	protected:
		//ciel inclu
		ciel sky;
		//climat: 0=normal, 1=orage
		int climat;
};

#endif // PRJ_NUAGES_H
