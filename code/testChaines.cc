#include "chaines.h"
using namespace std;

int main () {
	chaine_mont C({{2,22,12,12,3}, {20,2,15,8,4}});
	montagne m (15, 15, 18, 5, 10);
	chaine_mont M ({&C,&m});
	
	
	for(double a(0.0); a<30.0; a=a+1.0){
		for(double b(0.0); b<30.0; b=b+1.0){
			cout<< a<<" "<< b<<" "<< M.alt(a,b)<<endl;
		}
		cout<< endl;
	}
	
	return 0;
}
