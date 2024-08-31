#include <iostream>
#include "chaines.h"
#include "rivers.h"

/*Pour tester créer un .dat puis utiliser les commandes suivantes sur gnulot:
 * file='testRiviere.dat'
 * splot file u 1:2:3:($4 > 0 ? $4 : 1/0) notitle w p
 */

int main () {
	chaine_mont M("random.mont", 1.0);
	riviere R (&M, 15, 15);
	
	R.affiche();
	//R.dessine();
	
	return 0;
}
