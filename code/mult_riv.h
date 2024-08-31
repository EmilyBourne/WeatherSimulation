#ifndef PRJ_MULT_RIV_H
#define PRJ_MULT_RIV_H
#include "dessinable.h"

class mult_riv: public dessinable {
	public:
		virtual ~mult_riv(){};
		virtual mult_riv* copie() const =0;
		virtual bool position (int x, int y, int z) const = 0;
		virtual bool lac_ici (int x, int y, int z) const = 0;
		virtual void dessine (std::ostream& flot=std::cout) const = 0;
		virtual void affiche (std::ostream& flot=std::cout) const = 0;
};

#endif // PRJ_MULT_RIV_H
