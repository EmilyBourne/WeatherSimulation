#include "gros_chaines.h"
using namespace std;

void gros_chaine_mont::Riv(double x, double y, double z) {
	bool b(false);
	for (size_t i(0); i<riv.size() and b==false; ++i) {
		if (x==riv[i][0] and y==riv[i][1]) {
			riv[i][2]=riv[i][2]+z;
			b=true;
		}			
	}
	if (b==false) {
		vector<double> a ({x, y, z});
		riv.push_back (a);
	}
}

double gros_chaine_mont::alt(double coordx, double coordy) const {
	double altitude (alti(coordx, coordy));
	for (size_t i(0); i<riv.size(); ++i) {
		if (coordx<riv[i][0]+riv[i][3] and coordx>riv[i][0]-riv[i][3] and coordy<riv[i][1]+riv[i][3] and coordy>riv[i][1]-riv[i][3]) {
			altitude=altitude+riv[i][2];
			return altitude;
		}
	}
	return altitude;
}
