#include "ChampPotentiels.h"

using namespace std;

int main(){
	chaine_mont M({{15.0,15.0,15.0,5.0,5.0}});
	ChampPotentiels C;
	C.initialise(M);
	
	
	C.afficheToutPot();
	
	return 0;
}

