#ifndef PRJ_GROS_CHAINES_H
#define PRJ_GROS_CHAINES_H

#include "dessinable.h"
#include <vector>

class gros_chaine_mont: public dessinable {
	public:
	virtual ~gros_chaine_mont(){};
	
	virtual gros_chaine_mont* copie() const =0;
	virtual void dessine (std::ostream& flot=std::cout) const =0;
	double alt(double coord1, double coord2) const;
	void Riv(double x, double y, double z);
	virtual double alti(double coord1, double coord2) const =0;
		
	private:
		std::vector<std::vector<double>> riv;
};

#endif //PRJ_GROS_CHAINES_H
