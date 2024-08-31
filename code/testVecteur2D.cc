#include "Vecteur2D.h"
using namespace std;

int main () {
	Vecteur2D vect1(1, 2);
	Vecteur2D vect2(2.6, 3.5);
	Vecteur2D vect3(vect1);  // copie de V1
	Vecteur2D vect4;         // le vecteur nul

	cout << "Vecteur 1 : " << vect1 << endl;
	cout << "Vecteur 2 : " << vect2 << endl;
	cout << "Vecteur 4 : " << vect4 << endl;

	cout << "Le vecteur 1 est ";
	if (vect1 == vect2) {
		cout << "égal au";
	} else {
		cout << "différent du";
	}
	cout << " vecteur 2," << endl << "et est ";
	if (vect1 != vect3) {
		cout << "différent du";
	} else {
		cout << "égal au";
	}
	cout << " vecteur 3." << endl;
	
	vect3=vect4;
	
	cout<< vect3;
	
	
	return 0;
}
