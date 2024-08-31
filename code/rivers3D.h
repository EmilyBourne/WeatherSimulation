#ifndef PRJ_RIVERS_3D_H
#define PRJ_RIVERS_3D_H
#include "rivers.h"
#include <vector>

class rivers3D: virtual public rivers {
	public:
	rivers3D (gros_chaine_mont* M, vector<vector<int>> list, bool verbeuse=false, ostream& flot=cout);
	rivers3D (gros_chaine_mont* M, int n = rand()%15+1, bool verbeuse=false, ostream& flot=cout);
	rivers3D (vector<mult_riv*>const& list);
	
	mult_riv* copie() const;
	
	virtual ~rivers3D();
	
	virtual void dessine (std::ostream& flot=std::cout) const;
	
	private:
};

#endif //PRJ_RIVERS_3D_H
