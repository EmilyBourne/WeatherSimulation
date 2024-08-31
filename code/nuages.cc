#include <iostream>
#include "nuages.h"
#include <cmath>
#include "constantes.h"
#include "proprietes_syst.h"
using namespace std;

//constructeur
nuages::nuages (ChampPotentiels c)
: sky(Proprietes::nx, std::vector<std::vector<CubedAir>> (Proprietes::ny, std::vector<CubedAir> (Proprietes::nz, CubedAir()))), climat(0)
{
	initialise_sky(c);
}

//fonction utilisé dans le constructeur qui crée le ciel en initialisant ses valeurs dans chaque cube d'air
void nuages::initialise_sky(ChampPotentiels C) {
	//initialisation des valeurs utilisé dans tous les calculs pour les cubes d'air
	double h_infinie (7*Physique::R*Proprietes::T_infinie/(2*Physique::M_air_sec));
	double cte (pow(Proprietes::v_infinie, 2)/2 + h_infinie);
	double tau (8*pow(10,-3));
	//remplir le ciel avec les cubes
	for (int i(1); i<Proprietes::nx-1; ++i) {
		for (int j(1); j<Proprietes::ny-1; ++j) {
			for (int k(1); k<Proprietes::nz-1; ++k) {
				vector<double> vent(C.vitesse(i, j, k));
				CubedAir a(vent, k, h_infinie, cte, tau);
				sky[i][j][k]=a;
			}
		}
	}
}

void nuages::init_source_humi(mult_riv& R, gros_chaine_mont& M){
	for (int i(1); i<Proprietes::nx-1; ++i) {
		for (int j(1); j<Proprietes::ny-1; ++j) {
			for (int k(1); k<Proprietes::nz-3; ++k) {
				double h(M.alti(i,j));
				if(R.lac_ici(i,j,k) and k+2 > h){
					sky[i][j][k+2].source_humi() = 2;
				}
				else if(R.position(i,j,k) and k+2 > h){
					sky[i][j][k+2].source_humi() = 1;
				}
				else{
					sky[i][j][k+2].source_humi() = 0;
				}
			}
		}
	}
}

//méthode d'affichage
void nuages::affiche (std::ostream& flot) const {
	for (int i(1); i<Proprietes::nx-1; ++i) {
		for (int j(1); j<Proprietes::ny-1; ++j) {
			for (int k(1); k<Proprietes::nz-1; ++k) {
				flot << i << ' ' << j << ' ' << k;
				sky[i][j][k].affiche(flot);
			}
		}
	}
}

//méthode d'affichage venant de la classe dessinable
void nuages::dessine (std::ostream& flot) const {
	affiche(flot);
}

bool nuages::nuage_ici(unsigned int i,unsigned int j,unsigned int k) const{
	bool etat(false);
	if((i<=sky.size())and(j<=sky[i].size())and(k<=sky[i][j].size())){
		etat = sky[i][j][k].nuage();
	}
	return etat;
}

bool nuages::pluie_ici(unsigned int i,unsigned int j, unsigned int k) const{
	return sky[i][j][k].pleut();
}

bool nuages::pluie_au_sol(unsigned int i,unsigned int j) const{
	bool gouttes(false);
	if(i<sky.size()){
		if(j<sky[i].size()){
			for(size_t k(1); k<sky[i][j].size()-1; k++){
				if(pluie_ici(i,j,k)==1){
					gouttes = true;
				}
			}
		}
	}
	return gouttes;
}

//fonction qui trouve le cube précedente par rapport au vent
vector<double> nuages::precedente (double dt, int i, int j, int k) const {
	vector<double> speed (sky[i][j][k].vitesse());
	double di(-dt*speed[0]);
	di=di*Proprietes::lambdaNum/Proprietes::lambdaDenom;
	di=trunc(di);
	di=di+i;
	if (di>=Proprietes::nx-1) {
		di=Proprietes::nx-2;
	}
	else if (di<=0) {
		di=1;
	}
	double dj(-dt*speed[1]);
	dj=dj*Proprietes::lambdaNum/Proprietes::lambdaDenom;	
	dj=trunc(dj);
	dj=dj+j;
	if (dj>=Proprietes::ny-1) {
		dj=Proprietes::ny-2;
	}
	else if (dj<=0) {
		dj=1;
	}
	double dk(-dt*speed[2]);
	dk=dk*Proprietes::lambdaNum/Proprietes::lambdaDenom;
	dk=trunc(dk);
	dk=dk+k;
	if (dk>=Proprietes::nz-1) {
		dk=Proprietes::nz-2;
	}
	else if (dk<=0) {
		dk=1;
	}
	return {di, dj, dk};
}

void nuages::evolue_nuage (double dt) {
	for (int i(1); i<Proprietes::nx-1; ++i) {
		for (int j(1); j<Proprietes::ny-1; ++j) {
			for (int k(1); k<Proprietes::nz-1; ++k) {
				vector<double> ijk (precedente(dt, i, j, k));
				if (ijk[0]!=i or ijk[1]!=j or ijk[2]!=k) {
					bool P(sky[ijk[0]][ijk[1]][ijk[2]].nuage());
					bool C(sky[i][j][k].nuage());
					if (C==true and P==false) {
						sky[i][j][k].Tau(-1.7);
					}
					else if (C==false and P==true) {
						sky[i][j][k].Tau(5.0);
					} 
				}
				//evolution pour les cubes source d'humidité
				if(sky[i][j][k].source_humi() == 1 and k<Proprietes::nz-3){
					sky[i][j][k+2].Tau(0.12*dt);
				}
				else if(sky[i][j][k].source_humi() == 2 and k<Proprietes::nz-3){
					sky[i][j][k+2].Tau(0.3*dt);
				}
				else if(sky[i][j][k].source_humi() == 3){
					sky[i][j][k].Tau(5*dt);
				}
			}
		}
	}
	calculate();
}

void nuages::pluie (double dt) {
	for (int i(1); i<Proprietes::nx-1; ++i) {
		for (int j(1); j<Proprietes::ny-1; ++j) {
			for (int k(1); k<Proprietes::nz-1; ++k) {
				sky[i][j][k].pluie(dt);
			}
		}
	}
	calculate();
}

void nuages::evolue(double pas){
	evolue_nuage(pas);
	pluie(pas);
}

void nuages::calculate () {
	double h_infinie (7*Physique::R*Proprietes::T_infinie/(2*Physique::M_air_sec));
	double cte (pow(Proprietes::v_infinie, 2)/2 + h_infinie);
	for (int i(0); i<Proprietes::nx; ++i) {
		for (int j(0); j<Proprietes::ny; ++j) {
			for (int k(0); k<Proprietes::nz; ++k) {
				sky[i][j][k].calculate(h_infinie, cte);
			}
		}
	}
}

void nuages::orage_go(){
	int h(Proprietes::nz-4);
	if(h>4){
		for(size_t x(2); x < sky.size(); ++x){
			for(size_t y(1); y < sky[x].size(); ++y){
				if(sky[x][y][h].source_humi() == 0){
					sky[x][y][h].source_humi() = 3;
					sky[x][y][h-1].source_humi() = 3;
					sky[x][y][h-2].source_humi() = 3;
				}
			}
		}
	}
}


void nuages::orage_stop(){
	int h(Proprietes::nz-4);
	for(size_t x(2); x < sky.size(); ++x){
		for(size_t y(1); y < sky[x].size(); ++y){
			if(sky[x][y][h].source_humi() == 3){
				sky[x][y][h].source_humi() = 0;
				sky[x][y][h-1].source_humi() = 0;
				sky[x][y][h-2].source_humi() = 0;
			}
		}
	}
}

bool nuages::orage_switch(bool onoff){
	bool storm(false);
	if(climat == 0 and onoff==true){
		climat = 1;
		orage_go();
		storm = true;
	}
	else if(climat==1 and onoff==false){
		climat = 0;
		orage_stop();
		storm =false;
	}
	return storm;
}

bool nuages::orage_switch(){
	bool storm(false);
	if(climat == 0){
		storm = true;
	}
	else if(climat==1){
		storm =false;
	}
	return orage_switch(storm);
}
