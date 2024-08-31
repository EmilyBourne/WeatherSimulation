#include <iostream>
#include <cmath>
#include "montagne_lue.h"
#include "proprietes_syst.h"
#include <random>
#include <functional>
#include <string>

using namespace std;

//---------------La classe montagne_lue----------------------

	double montagne_lue::alti(double coordx, double coordy) const {
		double altitude(0.0);
		
		
		
		
			unsigned int x_entier(floor(coordx));
			unsigned int y_entier(floor(coordy));
			if(x_entier+1<mont.size()){
				if(y_entier+1<mont[coordx].size()){
					altitude = (mont[1+x_entier][1+y_entier]*sqrt(pow((x_entier+1 - coordx),2)+pow((y_entier+1 - coordy),2))
								+mont[x_entier][1+y_entier]*sqrt(pow((x_entier - coordx),2)+pow((y_entier+1 - coordy),2))
								+mont[1+x_entier][y_entier]*sqrt(pow((x_entier+1 - coordx),2)+pow((y_entier - coordy),2))
								+mont[x_entier][y_entier]*sqrt(pow((x_entier - coordx),2)+pow((y_entier - coordy),2))
								)/(sqrt(pow((x_entier+1 - coordx),2)+pow((y_entier+1 - coordy),2))+sqrt(pow((x_entier - coordx),2)+pow((y_entier+1 - coordy),2))+sqrt(pow((x_entier+1 - coordx),2)+pow((y_entier - coordy),2))+sqrt(pow((x_entier - coordx),2)+pow((y_entier - coordy),2)));
				}
			}
		if (altitude < 0.5){ altitude = 0.0; }
		
		return altitude;
	}

	gros_chaine_mont* montagne_lue::copie() const{
		return new montagne_lue(*this);
	}

void montagne_lue::genere_montagne(double h_over_nz){
	int dim(0);
		if(Proprietes::ny>=Proprietes::nx){
		dim = next_puissance_2(Proprietes::ny-1)+1;
	}
	else{
		dim = next_puissance_2(Proprietes::nx-1)+1;
	}
		
	vector<vector<double>> creation(dim,vector<double>(dim,0.0));
	int pas(dim-1);
	double echelle(Proprietes::nz*h_over_nz);
	creation[pas/2][pas/2] = Proprietes::nz*0.8;
	while(pas>1){
		int mipas(pas/2);
		//phase carré
			for (int y(mipas); y < dim-1 + mipas; y += pas){
				for (int x(mipas); x < dim-1 + mipas; x += pas){
						genere_mont_carre(x,y,pas,echelle, creation);
				
				}
			}	
		//phase diamand
			for (int y(mipas); y < dim-1 + mipas; y += pas){
				for (int x(mipas); x < dim-1 + mipas; x += pas){
	
						genere_mont_diamand(x+mipas,y,pas,echelle, creation);
						
						genere_mont_diamand(x,y+mipas,pas,echelle, creation);
						
				}
			}
		
		pas = pas/2;
		echelle = echelle/2.0;
	}
	
	//ajouter if pour les 2^n +1 mieux que ça!!!!
	if((mont.size()==creation.size()) and (mont[0].size()==creation[0].size())){
		mont=creation;
	}
	else{
		
		for (unsigned int i(0); i < mont.size(); i ++){
			for (unsigned int j(0); j < mont[i].size(); j ++){
				double x_corr(static_cast<double>(creation.size())/mont.size());
				double y_corr(static_cast<double>(creation[round(i*x_corr)].size())/mont[i].size());
			
				int i_creation(round(i*x_corr));
				int j_creation(round(j*y_corr));
			
				mont[i][j] = creation [i_creation][j_creation];
			
				if(i>=Proprietes::nx-2){mont[i][j]=0.0;}
				if(j>=Proprietes::ny-2){mont[i][j]=0.0;}
				if(i<=2){mont[i][j]=0.0;}
				if(j<=2){mont[i][j]=0.0;}
			}
		}

	}
}

void montagne_lue::genere_mont_carre(unsigned int x, unsigned int y, int pas, double echelle, vector<vector<double>>& creation){
	int hs(pas / 2);
	
	double a(creation[x - hs][y - hs]);
	double b(creation[x + hs][y - hs]);
	double c(creation[x - hs][y + hs]);
	double d(creation[x + hs][y + hs]);
 
	creation[x][y] += ((a + b + c + d) / 4.0) + tirage()*echelle;
	//conditions de bord
	if(creation[x][y]>=Proprietes::nz){creation[x][y]=Proprietes::nz*0.8;}
	if(x>=creation.size()-2){creation[x][y]=0.0;}
	if(y>=creation[x].size()-2){creation[x][y]=0.0;}
	if(x<=2){creation[x][y]=0.0;}
	if(y<=2){creation[x][y]=0.0;}

}

void montagne_lue::genere_mont_diamand(unsigned int x, unsigned int y, int pas, double echelle, vector<vector<double>>& creation){
	int hs(pas / 2);
 
	if(abs(x+hs)>=creation.size()){ x-=hs;}
	
	double a(creation[x - hs][y]);
	double b(creation[x + hs][y]); 	
	double c(creation[x][y - hs]);	
	double d(creation[x][y + hs]);
	
 	creation[x][y] += ((a + b + c + d) / 4.0) + tirage()*echelle;
 	//conditions de bord
	if(creation[x][y]>=Proprietes::nz){creation[x][y]=Proprietes::nz*0.8;}
	if(x>=creation.size()-2){creation[x][y]=0.0;}
	if(y>=creation[x].size()-2){creation[x][y]=0.0;}
	if(x<=2){creation[x][y]=0.0;}
	if(y<=2){creation[x][y]=0.0;}
}

double montagne_lue::tirage(){
	double min(-1.0); double max(1.0);
	uniform_real_distribution<double> distribution(min, max);
	random_device rd;
	double graine(rd());
	default_random_engine generateur(graine);
	auto alea(bind(distribution, generateur));
	
	return(alea());
}

bool montagne_lue::puissance_2(int nombre){
	bool p2(false);
		if(((nombre%2)==0)and(nombre != 2)){
			p2 = puissance_2(nombre/2);
		}
		else if(nombre==2){
			p2 = true;
		}
		else{
			p2 = false;
		}
	return p2;
}

int montagne_lue::next_puissance_2(int nombre){
	int next(0);
	if(puissance_2(nombre)){
		next = nombre;
	}
	else{
		next = pow(2.0, trunc((log(nombre))/(log(2.0)))+1);
		if(not puissance_2(next)){next = 0;}
	}
	return next;
}

//constructeur
	montagne_lue::montagne_lue(string fichier, double zscale)
	: nom(fichier), mont(Proprietes::nx, vector<double>(Proprietes::ny,0))
	{
		ifstream montagne(nom);
		if (!montagne.fail()) {
			int x(0);
			int y(0);
			double z(0.0);
			do{
				montagne >> x;
				montagne >> y;
				montagne >> z;
				if((x>2) and (abs(x)<mont.size()-2)){
					if((y>=2) and (abs(y)<mont[x].size()-2)){
						mont[x][y] = z*zscale;
					}
				}
			}while(!montagne.eof());
		}
		montagne.close();
	}

montagne_lue::montagne_lue()
	: nom("random.mont"), mont(Proprietes::nx, vector<double>(Proprietes::ny,0))
	{	
		genere_montagne(0.6);
		ofstream montagne(nom);
		for(int x(0); x<Proprietes::nx; x++){
			for(int y(0); y<Proprietes::ny; y++){
				montagne << x<<" "<<y<<" "<<alti(x,y)<<endl;
			}
		}
	}

//destructeur
	montagne_lue::~montagne_lue(){}
	
//fonction dessine de la classe dessinable
void montagne_lue::dessine (std::ostream& flot) const {
	for(double a(0.0); a<Proprietes::nx; a+=1.0){
		for(double b(0.0); b<Proprietes::ny; b+=1.0){
			flot<< a<<" "<< b<<" "<< alti(a,b)<<endl;
		}
		flot<< endl;
	}
}

