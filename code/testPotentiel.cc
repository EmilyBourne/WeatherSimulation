#include "Potentiel.h"
#include <iostream>

using namespace std;

int main(){
	Vecteur2D v1(3.0,4.2);
	Vecteur2D v2;
	Vecteur2D v3(8.8,9.9);
	
	Potentiel P(v1,v2);
	
	cout<<"Potentiel : "<<P.pot()<<endl;
	cout<<"Laplacien : "<<P.lapl()<<endl;
	
	P.lapl()=v3;
	cout<<"Nouveau Laplacien : "<<P.lapl()<<endl;
	
	Potentiel N;
	cout<<"Potentiel : "<<N.pot()<<endl;
	cout<<"Laplacien : "<<N.lapl()<<endl;
}
