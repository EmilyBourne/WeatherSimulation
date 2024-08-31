#ifndef PRJ_VECTEUR_2D_H
#define PRJ_VECTEUR_2D_H
#include <iostream>


class Vecteur2D {
	public:
		//get
		double x() const;
		double y() const;
		//set
		Vecteur2D (double x, double y=0.0);
		Vecteur2D ();
		double& x();
		double& y();
		//affiche
		void affiche () const;
		//operators
		//compare
		bool operator== (Vecteur2D z) const;
		bool operator!= (Vecteur2D z) const;
		//void operator= (Vecteur2D const& vec);
		Vecteur2D operator+ (Vecteur2D const& vec) const;
		Vecteur2D operator- (Vecteur2D const& vec) const;
		Vecteur2D operator- () const;
		Vecteur2D operator* (double const& k) const;
		double prod_scal (Vecteur2D const& vec) const;
		double carre () const;
		double norm () const;
	private:
		double X;
		double Y;
};

using namespace std;

ostream& operator<< (ostream& a, Vecteur2D const& v);

#endif // PRJ_VECTEUR_2D_H
