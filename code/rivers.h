#ifndef PRJ_RIVERS_H
#define PRJ_RIVERS_H

#include <iostream>
#include "mult_riv.h"
#include "riviere.h"
#include <vector>

class rivers: virtual public mult_riv {
	public:
		virtual void dessine (std::ostream& flot=std::cout) const;
		virtual bool position (int x, int y, int z) const;
		virtual bool lac_ici (int x, int y, int z) const;
		virtual mult_riv* copie() const;
		rivers (vector<mult_riv*>const& list);
		rivers (gros_chaine_mont* M, vector<vector<int>> list, bool verbeuse = false, ostream& flot = cout);
		rivers (gros_chaine_mont* M, int n = rand()%15+1, bool verbeuse = false, ostream& flot = cout);
		virtual ~rivers();
		virtual void affiche (std::ostream& flot=std::cout) const;
	protected:
		rivers ();
		vector<mult_riv*> mon_range;
	private:
};

#endif // PRJ_RIVERS_H
