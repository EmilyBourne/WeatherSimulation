#ifndef PRJ_RIVIERE_3D_H
#define PRJ_RIVIERE_3D_H
#include "riviere.h"

class riviere3D: public riviere {
	public:
		riviere3D (gros_chaine_mont* m);
		riviere3D (gros_chaine_mont* m, int debutx, int debuty);
		
		virtual ~riviere3D ();
		
		virtual mult_riv* copie() const;
		
		virtual void dessine (std::ostream& flot=std::cout) const;
	private:
};

#endif //PRJ_RIVIERE_3D_H
