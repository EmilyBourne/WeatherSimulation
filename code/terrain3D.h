#ifndef PRJ_TERRAIN_3D_H
#define PRJ_TERRAIN_3D_H
#include "chaines.h"
#include <iostream>
#include "terrain.h"
#include "INCLUSIONS"


class terrain3D : public terrain{
	public:
		terrain3D (chaine_mont& mont, nuages& sky);
		
		terrain3D(const terrain3D& S) = delete;
		terrain3D& operator=(const terrain3D& S) = delete;
		
		virtual void dessine(std::ostream& flot=std::cout) const;
	private:
		
		
		
};

#endif //PRJ_TERRAIN_3D_H
