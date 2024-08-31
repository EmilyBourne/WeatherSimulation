#include <iostream>
#include "riviere.h"
#include <cmath>
#include "proprietes_syst.h"
using namespace std;

//constructeurs
riviere::riviere (gros_chaine_mont* m)
: eau(vector<vector<vector<int>>> (Proprietes::nx, vector<vector<int>> (Proprietes::ny, vector<int> (Proprietes::nz, 0)))),M(m) {
	creer ();
}

riviere::riviere (gros_chaine_mont* m, int debutx, int debuty)
: eau(vector<vector<vector<int>>> (Proprietes::nx, vector<vector<int>> (Proprietes::ny, vector<int> (Proprietes::nz, 0)))), Debut(debutx, debuty), M(m){
	creer (Debut.x(), Debut.y());
}

riviere::riviere () {}

//déstructeur
riviere::~riviere() {}

//créer la rivière
void riviere::creer () {
	Debut=debut();	
	creer (Debut.x(), Debut.y());
}

void riviere::creer (int x, int y) {
	int z(trunc(M->alt(x,y)));
	double l(Proprietes::nz);
	double n;
	bool prev_lac(false);
	do {
		
		int a(x);
		int b(y);
		if (x!=0) {
			n=M->alt(x-1, y);
			if (n<l) {
				a=x;
				b=y;
				l=n;
				a=a-1;
			}
		}
		if (y!=0) {
			n=M->alt(x, y-1);
			if (n<l) {
				a=x;
				b=y;
				l=n;
				b=b-1;
			}
		}
		if (x!=Proprietes::nx-1) {
			n=M->alt(x+1, y);
			if (n<l) {
				a=x;
				b=y;
				l=n;
				++a;
			}
		}
		if (y!=Proprietes::ny-1) {
			n=M->alt(x, y+1);
			if (n<l) {
				a=x;
				b=y;
				l=n;
				++b;
			}
		}
		if (x==0 or y==0 or x==Proprietes::nx-1 or y==Proprietes::ny-1){
			l=-1;
		}
		else if (x==a and y==b) {
			l=lac (a, b, z,1);
			prev_lac=true;
		}
		x=a;
		y=b;
		z=trunc(M->alt(x,y));
		eau[x][y][z]=1;
		if (prev_lac!=true) {
			M->Riv(x, y, 0.5);
		}
		route.push_back({x, y, false});
		prev_lac=false;
	} while (l>0);
	while (x>0 and x<Proprietes::nx-1 and y>0 and y<Proprietes::ny-1) {
		int a;
		int b;
		if(route.size()>=2) {
			a=x-route[route.size()-2].i;
			b=y-route[route.size()-2].j;
		}
		else {
			a=1;
			b=0;
		}
		if (M->alt(x+a,y+b)<=M->alt(route[route.size()-1].i, route[route.size()-1].j)) {
			x=x+a;
			y=y+b;
			route.push_back({x,y, false});
			M->Riv(x, y, 0.5);
		}
		else {
			x=-1;
		}			
	}
}

//Choisir le point de départ si ceci n'est pas donné
Vecteur2D riviere::debut () {
	int Nx(Proprietes::nx);
	int Ny(Proprietes::ny);
	Vecteur2D a (rand()%Nx, rand()%Ny);
	return a;
}

//dire si il y a un rivière sur un point ou pas
bool riviere::position (int x, int y, int z) const {
	bool rhone(false);
	if(eau[x][y][z]!=0){
		rhone = true;
	}
	return rhone;
}

bool riviere::lac_ici (int x, int y, int z) const {
	bool leman(false);
	if(eau[x][y][z]==2){
		leman = true;
	}
	return leman;
}

//dessine
void riviere::dessine (std::ostream& flot) const {
	for(int i(0); i<Proprietes::nx; ++i) {
		for(int j(0); j<Proprietes::ny; ++j) {
			for (int k(0); k<Proprietes::nz; ++k) {
				flot << i << ' ' << j << ' ' << k << ' ' << eau[i][j][k] << endl;
			}
		}
		flot<< endl;
	}
}

//copie
mult_riv* riviere::copie() const{
	return new riviere(*this);
}

//remplir les trous pour créer un lac	
double riviere::lac(int& x, int& y, int& z, int t) {
	double l(Proprietes::nz);
	int n(0);
	int a(x);
	int b(y);
	for (int i(0); i<t and x+t<Proprietes::nx; ++i) {
		for (int j(0); j<t and y+j<Proprietes::ny; ++j) {
			if (i==0 and x!=0) {
				n=M->alt(x-1, y+j);
				if (n<l) {
					a=x-1;
					b=y+j;
					l=n;
				}
			}
			else if (j==0 and y!=0) {
				n=M->alt(x+i, y-1);
				if (n<l) {
					a=x+i;
					b=y-1;
					l=n;
				}
			}
			else if (i==t-1 and x!=Proprietes::nx-1) {
				n=M->alt(x+i+1, y+j);
				if (n<l) {
					a=x+i+1;
					b=y+j;
					l=n;
				}
			}
			else if (j==t-1 and y!=Proprietes::ny-1) {
				n=M->alt(x+i, y+j+1);
				if (n<l) {
					a=x+i;
					b=y+j+1;
					l=n;
				}
			}
			eau[x+i][y+j][z]=2;
			M->Riv(x+i, y+j, 1);
			route.push_back({x+i, y+j, true});
		}
	}
	if (x+t>=Proprietes::nx-1 or x==0 or y+t>=Proprietes::ny-1 or y==0) {
		return 2.0;
	}
	if (l>z) {
		x=x-1;
		y=y-1;
		++z;
		double p(lac(x,y,z, t+2));
		if (p==2.0) {
			if (t==1) {
				return 0.0;
			}
			else return 2.0;
		}
	}
	else {
		x=a;
		y=b;
		z=trunc(M->alt(x,y));
	}		
	if(t==1) {
		return M->alt(x,y);
	}
	else {
		return 1.0;
	}
}

void riviere::affiche (std::ostream& flot) const {
	for (size_t i(0); i<route.size(); ++i) {
		cout << "i:" << route[i].i << " j:" << route[i].j << " lac:" << route[i].lac << endl;
	}
	cout << endl;
}
