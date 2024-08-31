#include <iostream>
#include "nuages.h"
using namespace std;

int main () {
	montagne m(15.0,15.0,15.0,5.0,5.0);
	chaine_mont M({&m});
	ChampPotentiels C;
	C.initialise(M);
	C.resolution(0.1,M);
	nuages n(C);
	for (int i(0); i<9; ++i) {
		n.evolue_nuage(0.031);
	}
	n.affiche();
	return 0;
}
