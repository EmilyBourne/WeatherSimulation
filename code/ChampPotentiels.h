#ifndef PRJ_CHAMP_POTENTIEL_H
#define PRJ_CHAMP_POTENTIEL_H
#include "Potentiel.h"
#include "chaines.h"
#include <vector>
#include "dessinable.h"


typedef vector<vector<vector<Potentiel>>> collection;

//---------------La classe ChampPotentiels----------------------

class ChampPotentiels: public dessinable {
	public:
	//constructeur
	ChampPotentiels();
	//methodes
	void initialise(chaine_mont& M);
	void calculeLaplacien(chaine_mont & M);
	void calculeLaplacien(chaine_mont & M, int i, int j, int k);
	void afficheToutPot(std::ostream & flot=std::cout)const;
	void afficheToutLapl(std::ostream & flot=std::cout)const;
	double erreur();
	virtual void dessine (std::ostream& flot=std::cout) const;
	
	void resolution(double epsilon, chaine_mont & M, double errmax=1e-4, int itermax = 3000, bool verbeuse = false);
	vector<double> vitesse(int i, int j, int k) const;
	//get
	collection collec() const;
	
	private:
	void iteration(double epsilon,chaine_mont & M);
	collection C;
};

#endif //  PRJ_CHAMP_POTENTIEL_H
