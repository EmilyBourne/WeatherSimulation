#ifndef PRJ_SYSTEME3D_H
#define PRJ_SYSTEME3D_H
#include "Systeme.h"
#include "proprietes_syst.h"
#include <string>
#include <vector>


class Systeme3D : public Systeme {
	public:
	virtual void dessine (std::ostream& flot=std::cout)const;
	virtual void initialise(double pas=0.1, double errmax=1e-4, int itermax=3000, bool verbeuse=false);
	
	Systeme3D();
	Systeme3D(bool vide);
	Systeme3D(std::string fichier, double zscale);
	Systeme3D(chaine_mont* mont, ChampPotentiels* champ, mult_riv* river);
	Systeme3D(chaine_mont* mont, ChampPotentiels* champ, nuages* cloud, terrain* ground, mult_riv* r);
	virtual ~Systeme3D();
	Systeme3D(const Systeme3D& S) = delete;
	Systeme3D& operator=(const Systeme3D& S) = delete;
	
	//codes parametre	: (121) nuage3D::affiche_press 	, (122) nuage3D::affiche_temp
	//codes changement	: (121)/ (1)true (0) false		, (122)/ (1) true (0) false
	virtual void parametre (unsigned int code_param, unsigned int changement);
	
	private:
	dessinable* copie (dessinable* a);
};

using namespace std;

ostream& operator<< (ostream& a, Systeme3D const& Syst);

#endif // PRJ_SYSTEME3D_H
