#ifndef PRJ_CHAINES_H
#define PRJ_CHAINES_H

#include <iostream>
#include "gros_chaines.h"
#include "montagne.h"
#include <vector>
#include <string>

class chaine_mont: virtual public gros_chaine_mont {
	public:
		virtual void dessine (std::ostream& flot=std::cout) const;
		virtual double alti(double coord1, double coord2) const;
		virtual gros_chaine_mont* copie() const;
		chaine_mont (std::vector<gros_chaine_mont*> list);
		chaine_mont (std::vector<std::vector<double>> list, bool verbeuse=false, std::ostream& flot=std::cerr);
		chaine_mont (std::string fichier, double zscale);
		virtual ~chaine_mont();
	protected:
		std::vector<gros_chaine_mont*>& mes_montagnes();
		chaine_mont();
		std::vector<gros_chaine_mont*> mon_range;
	private:
	
};

#endif // PRJ_CHAINES_H
