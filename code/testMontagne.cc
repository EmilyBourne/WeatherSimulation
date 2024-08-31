#include "montagne.h"
#include <iostream>

using namespace std;

int main(){
	montagne M(15.0,15.0,18.0,5.0,10.0);
	
	//test methodes de lecture
	cout<<"#centre x : "<< M.Cx() <<"  centre y : "<< M.Cy()<<endl;
	cout<<"#hauteur : "<<M.H()<<endl;
	cout<<"#etal x : "<< M.Ex() <<"  etal y : "<< M.Ey()<<endl;
	cout<<"#altitude en (4.0 ; 9.0) : "<< M.alt(4.0,9.0)<<endl<<endl;
	//test methode altitude
	for(double a(0.0); a<30.0; a=a+1.0){
		for(double b(0.0); b<30.0; b=b+1.0){
			cout<< a<<" "<< b<<" "<< M.alt(a,b)<<endl;
		}
		cout<< endl;
	}

return 0;
}
