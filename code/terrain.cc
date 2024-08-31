#include "terrain.h"
#include <cmath>
#include <random>
#include <functional>
#include "proprietes_syst.h"

using namespace std;

double terrain::tirage_gauss(double moy, double ec_type){
	normal_distribution<double> distribution(moy, ec_type);
	random_device rd;
	double graine(rd());
	default_random_engine generateur(graine);
	auto alea(bind(distribution, generateur));
	
	return(alea());
}

double terrain::tirage(){
	double min(0.0); double max(1.0);
	uniform_real_distribution<double> distribution(min, max);
	random_device rd;
	double graine(rd());
	default_random_engine generateur(graine);
	auto alea(bind(distribution, generateur));
	
	return(alea());
}

terrain::terrain (chaine_mont& mont, nuages& sky)
: sol(Proprietes::nx, vector<carre_sol>(Proprietes::ny)), M(mont), N(sky)
{}

void terrain::initialise_type(double alt_roche){
	double Z(alt_roche);
	for(unsigned int x(0); x<sol.size(); x++){
		for(unsigned int y(0); y<sol.size(); y++){
			double z(M.alt(x,y));
			double zonz(0.0);
			if(Z!=0){zonz=z/Z;}
			if(z>Z){
				sol[x][y].type = 2;
			}
			else{
				double u(tirage());
				if(u<(1.0-sqrt(2.0*zonz-pow(zonz,2.0)))){
					sol[x][y].type = 0;
				}
				else if(u<(2.0-sqrt(2.0*zonz-pow(zonz,2.0)) - sqrt(1-pow(zonz,2.0)))){
					sol[x][y].type = 2;
				}
				else{
					sol[x][y].type = 1;
				}
			}
			if((x==0)or(x==sol.size()-1)or(y==0)or(y==sol[x].size()-1)){
				sol[x][y].type = 0;
			}
		}
	}
}

void terrain::initialise_veg(){
	for(unsigned int x(0); x<sol.size(); x++){
		for(unsigned int y(0); y<sol.size(); y++){
			sol[x][y].plantes = 0.0;
			
			if(sol[x][y].type == 0){
				sol[x][y].plantes = tirage_gauss(0.7, 0.05);
			}
			else if(sol[x][y].type == 1){
				sol[x][y].plantes = tirage_gauss(0.5, 0.03);
			}
			else if(sol[x][y].type == 2){
				sol[x][y].plantes = tirage_gauss(0.3, 0.01);
			}
			
			if(sol[x][y].plantes < 0.001){
				sol[x][y].plantes = 0.001;
			}
			if(sol[x][y].plantes > 1.0){
				sol[x][y].plantes = 1.0;
			}
		}
	}
}

void terrain::initialise(double alt_roche){
	initialise_type(alt_roche);
	initialise_veg();
}

void terrain::dessine(std::ostream& flot) const{
	for(unsigned int x(0); x<sol.size(); x++){
		for(unsigned int y(0); y<sol.size(); y++){
			flot<<x<<" "<<y<<" "<<sol[x][y].type<<" "<<sol[x][y].plantes<<endl;
		}
	}
}

void terrain::evolue(double pas){
	for(unsigned int x(1); x<sol.size()-1; x++){
		for(unsigned int y(1); y<sol.size()-1; y++){
			bool rain(false);
			rain = N.pluie_au_sol(x,y);
			if(sol[x][y].type == 0){
				if(not rain){
					sol[x][y].plantes /= (pow(1.001,pas)*1.0001);
				}
				else if(rain){
					sol[x][y].plantes += sol[x][y].plantes*0.005*pas;
				}
			}
			else if(sol[x][y].type == 1){
				if(not rain){
					sol[x][y].plantes /= (pow(1.005,pas)*1.0001);
				}
				else if(rain){
					sol[x][y].plantes += ((sol[x][y].plantes+sol[x+1][y].plantes+sol[x][y+1].plantes+sol[x+1][y+1].plantes)/4.0)*0.005*pas;
				}
			}
			else if(sol[x][y].type == 2){
				if(not rain){
					sol[x][y].plantes /= (pow(1.01,pas)*1.0001);
				}
				else if(rain){
					sol[x][y].plantes += 0.005;
				}
			}
			
			if(sol[x][y].plantes < 0.001){
				sol[x][y].plantes = 0.001;
			}
			if(sol[x][y].plantes > 1.0){
				sol[x][y].plantes = 1.0;
			}
		}
	}
}
