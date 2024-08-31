#include "terrain.h"
#include <iostream>

using namespace std;

int main(){
	montagne m(15.0,15.0,15.0,5.0,5.0);
	chaine_mont M({&m});
	ChampPotentiels C;
	C.initialise(M);
	C.resolution(0.3,M);
	nuages n(C);
	
	terrain T(M, n);
	T.initialise(12);
	
	T.dessine();
	
	return 0;
}
