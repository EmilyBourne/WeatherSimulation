#include <iostream>
#include <sstream>
#include "Vecteur2D.h"
#include <cmath>
using namespace std;

//get
double Vecteur2D::x() const {
	return X;
}
double Vecteur2D::y() const {
	return Y;
}
//set
Vecteur2D::Vecteur2D () 
: X(0.0), Y(0.0)
{}
Vecteur2D::Vecteur2D (double x, double y) 
: X(x), Y(y)
{}
double& Vecteur2D::x(){ return X; }
double& Vecteur2D::y(){ return Y; }

//affiche
ostream& operator<< (ostream& a, Vecteur2D const& v) {
	a << v.x() << ' ' << v.y();
	return a;
}
void Vecteur2D::affiche () const {
	cout << X << ' ' << Y;
}
//compare
bool Vecteur2D::operator== (Vecteur2D z) const {
	if (X==z.X) {
		if (Y==z.Y) {
			return true;
		}
	}
	return false;
}
bool Vecteur2D::operator!= (Vecteur2D z) const {
	if (X==z.X) {
		if (Y==z.Y) {
			return false;
		}
	}
	return true;
}
//copie
/*void Vecteur2D::operator= (Vecteur2D const& vec) {
	X=vec.x();
	Y=vec.y();

}
*/
/* Le consctructeur de copie pose problème Il est de trop. (le par défaut fonctionne bien)
   Vecteur2D::Vecteur2D (Vecteur2D const& vec) {
	X=vec.x();
	Y=vec.y();
}
*/
//maths
Vecteur2D Vecteur2D::operator+ (Vecteur2D const& vec) const {
	Vecteur2D terc;
	terc.X=X+vec.X;
	terc.Y=Y+vec.Y;
	return terc;
}
Vecteur2D Vecteur2D::operator- (Vecteur2D const& vec) const {
	Vecteur2D terc;
	terc.X=X-vec.X;
	terc.Y=Y-vec.Y;
	return terc;
}
Vecteur2D Vecteur2D::operator* (double const& k) const {
	Vecteur2D vect;
	vect.X=k*X;
	vect.Y=k*Y;
	return vect;
}
//opposé
Vecteur2D Vecteur2D::operator- () const {
	Vecteur2D vect;
	vect.X=-X;
	vect.Y=-Y;
	return vect;
}
double Vecteur2D::prod_scal (Vecteur2D const& vec) const {
	return vec.X*X+vec.Y*Y;
}
double Vecteur2D::carre () const {
	return pow(X, 2)+pow(Y,2);
}
double Vecteur2D::norm () const {
	return pow(carre(), 0.5);
}
