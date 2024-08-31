#ifndef PRJ_TERRAIN_H
#define PRJ_TERRAIN_H
#include "chaines.h"
#include <iostream>
#include "nuages.h"

struct carre_sol{
	double plantes;
	int type;
};

class terrain : public dessinable{
	public:
		terrain (chaine_mont& mont, nuages& sky);
		void initialise(double alt_roche);
		
		double veg (int x, int y, chaine_mont& M, double Z);
		
		terrain(const terrain& S) = delete;
		terrain& operator=(const terrain& S) = delete;
		
		void evolue(double pas);
		
		virtual void dessine(std::ostream& flot=std::cout) const;
	private:
		//0=fertile, 1=aride, 2=rocailleux
		double tirage_gauss(double moy, double ec_type);
		double tirage();
		
		void initialise_type(double alt_roche);
		void initialise_veg();
	
	protected:
		std::vector<std::vector<carre_sol>> sol;
		chaine_mont& M;
		nuages& N;
		
		
};

#endif //PRJ_TERRAIN_H
