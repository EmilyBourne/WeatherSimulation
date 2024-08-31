#include "ChampPotentiels.h"
#include "gros_chaines.h"
#include "proprietes_syst.h"
#include <cmath> // pour x^y

using namespace std;


//---------------La classe ChampPotentiels----------------------

//constructeur
ChampPotentiels::ChampPotentiels()
: C(Proprietes::nx, vector<vector<Potentiel>>(Proprietes::ny,vector<Potentiel>(Proprietes::nz)))
{ }

//initialisation du ChampPotentiels
void ChampPotentiels::initialise(chaine_mont & M){
	double /*xi(0.0),*/ yj(0.0), zk(0.0);
	
	for(int i(0); i<Proprietes::nx; i++){
		/*xi = i*lambda;*/
		for(int j(0); j<Proprietes::ny; j++){
			yj = (j-(Proprietes::ny-1)/2.0)*Proprietes::lambda;
			for(int k(0); k<Proprietes::nz; k++){
				zk = k* Proprietes::lambda;
				if(M.alti(i,j)<=k){
					Vecteur2D p(-(Proprietes::v_infinie/2.0)*zk, (Proprietes::v_infinie/2.0)*yj);
					C [i] [j] [k].pot() = p;
				}
				else if(M.alti(i,j)>k){
					Vecteur2D p(0.0,0.0);
					C [i] [j] [k].pot() = p;
				}
				Vecteur2D p(0.0,0.0);
				C [i] [j] [k].lapl() = p;
			}
		}
	}
}

//laplacien
void ChampPotentiels::resolution(double epsilon, chaine_mont & M, double errmax, int itermax, bool verbeuse){
	calculeLaplacien(M);
	int iter(0);
	double err(10000);
	do{
		iter++;
		if(verbeuse) {cout<<iter<<"  "<<err<<endl;}
		iteration(epsilon, M);
		err = erreur();
			
	}while(err > pow(Proprietes::lambda,4)*errmax and iter <= itermax);
	
}

void ChampPotentiels::calculeLaplacien(chaine_mont & M){
	
	for(int i(1); i<Proprietes::nx-1; i++){
		for(int j(1); j<Proprietes::ny-1; j++){
			for(int k(1); k<Proprietes::nz-1; k++){
				calculeLaplacien(M, i, j, k);
			}
		}
	}
}

void ChampPotentiels::calculeLaplacien(chaine_mont & M, int i, int j, int k){
	if(M.alti(i,j)<=k){
		C[i][j][k].lapl()  = C[i-1][j][k].pot() 
							+ C[i][j-1][k].pot() 
							+ C [i][j][k-1].pot() 
							- C [i][j][k].pot()*6.0
							+ C [i+1][j][k].pot()
							+ C [i][j+1][k].pot() 
							+ C [i][j][k+1].pot() ;
	}
}

//vitesse
vector<double> ChampPotentiels::vitesse(int i, int j, int k) const{
	vector<double> v;
		if(i==0 or j==0 or k==0 or i==Proprietes::nx-1 or j==Proprietes::ny-1 or k==Proprietes::nz-1){
			v.push_back(0.0);
								 
			v.push_back(0.0);
								 
			v.push_back(0.0);
		}
		else{
			v.push_back((1.0/(2.0*Proprietes::lambda))*( C[i][j+1][k].pot().y() 
								 -  C[i][j-1][k].pot().y()
								 -  C[i][j][k+1].pot().x()
								 +  C[i][j][k-1].pot().x()));
								 
			v.push_back((1.0/(2.0*Proprietes::lambda))*(-C[i+1][j][k].pot().y()
								 + 	C[i-1][j][k].pot().y()));
								 
			v.push_back((1.0/(2.0*Proprietes::lambda))*( C[i+1][j][k].pot().x()
								 -  C[i-1][j][k].pot().x()));
		}
	
	return v;
}

//erreur
double ChampPotentiels::erreur(){
	double err(0.0);
	for(int i(0); i<Proprietes::nx; i++){
		for(int j(0); j<Proprietes::ny; j++){
			for(int k(0); k<Proprietes::nz; k++){
				err = err + pow(C[i][j][k].lapl().norm(),2);
			}
		}
	}
	
	return err;
}

//iteration
void ChampPotentiels::iteration(double epsilon, chaine_mont & M){
	
	for(int i(1); i<Proprietes::nx-1; i++){
		for(int j(1); j<Proprietes::ny-1; j++){
			for(int k(1); k<Proprietes::nz-1; k++){
				calculeLaplacien(M,i,j,k);
				C[i][j][k].pot() = C[i][j][k].pot() + C[i][j][k].lapl()*epsilon;
			}
		}
	}
	
}

//get
collection ChampPotentiels::collec() const{ return C; }

//affiche
void ChampPotentiels::afficheToutPot(ostream & flot) const{
	
	for(int i(0); i<Proprietes::nx; i++){
		for(int j(0); j<Proprietes::ny; j++){
			for(int k(0); k<Proprietes::nz; k++){
				flot<<i<<" "<<j<<" "<<k<<" "<<C[i][j][k].pot()<<endl;
			}
		}
	}
}

void ChampPotentiels::afficheToutLapl(ostream & flot) const{
	for(int i(0); i<Proprietes::nx; i++){
		for(int j(0); j<Proprietes::ny; j++){
			for(int k(0); k<Proprietes::nz; k++){
				flot<<i<<" "<<j<<" "<<k<<" "<<C[i][j][k].lapl()<<endl;
			}
		}
	}
}

void ChampPotentiels::dessine (std::ostream& flot) const{
	afficheToutPot(flot);
}
