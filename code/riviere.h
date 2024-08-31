#ifndef PRJ_RIVIERE_H
#define PRJ_RIVIERE_H

#include <vector>
#include "Vecteur2D.h"
#include "gros_chaines.h"
#include "mult_riv.h"

struct mov {
	int i;
	int j;
	bool lac;
};

class riviere: public mult_riv {
	public:
		virtual bool position (int x, int y, int z) const;
		virtual bool lac_ici (int x, int y, int z) const;
		riviere (gros_chaine_mont* m);
		riviere (gros_chaine_mont* m, int debutx, int debuty);
		virtual mult_riv* copie() const;
		virtual void dessine (std::ostream& flot=std::cout) const;
		virtual ~riviere();
		virtual void affiche (std::ostream& flot=std::cout) const;
	private:
		//1 si riviere, 2 si lac, 0 si rien
		vector<vector<vector<int>>> eau;
		Vecteur2D Debut;
		void creer ();
		void creer (int x, int y);
		Vecteur2D debut ();
		double lac (int& x, int& y, int& z, int t);
	protected:
		riviere ();
		gros_chaine_mont* M;
		vector<mov> route;
};

#endif // PRJ_RIVIERE_H
