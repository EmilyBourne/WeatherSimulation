#ifndef PRJ_CUBED_AIR_H
#define PRJ_CUBED_AIR_H
#include <vector>
#include <iostream>
#include "dessinable.h"

//La classe des cubes d'air
class CubedAir : public dessinable {
	public:
		//constructeur
		CubedAir(std::vector<double> Vit, double Z, double const& h_infinie, double const& cte, double const& Tau);
		CubedAir();
		//get
		bool nuage() const;
		std::vector<double> vitesse () const;
		bool pleut() const;
		int source_humi() const;
		int& source_humi();
		double Tau() const;
		int temp() const;
		int press() const;
		//augmentation de tau
		void Tau(double pourcentage);
		//set
		//fonction qui affiche des valeurs calculé
		void affiche (std::ostream& flot=std::cout) const;
		//fonction dessine qui vient du classe dessinable
		virtual void dessine (std::ostream& flot=std::cout) const;
		//fonction qui décide s'il y a un nuage ou pas
		void calculate(double const& h_infinie, double const& cte);
		//calculer si il pleut ou pas
		void pluie(double dt);
	private:
		//calcule des valeurs necessaire pour décider s'il y a un nuage ou pas
		void set_values(double const& h_infinie, double const& cte);
		//taux de humidité
		double tau;
		//vitesse en chaque point
		std::vector<double> vit;
		//carré de la vitesse donné par les champs potentiels
		double v2;
		//enthalpie par unité de masse
		double h;
		//Temperature
		double T;
		//Pression
		double P;
		//Pression 
		double P_eau;
		//Pression air saturée
		double P_rose;
		//hauteur
		double z;
		//1 s'il y a un nuage, 0 sinon
		bool cloud;
		//1 s'il pleut, 0 sinon
		bool Pluie;
		//0 si rien, 1 si une riviere, 2 si un lac, 3 si orage(grande source humi)
		int humi;
};


#endif // PRJ_CUBED_AIR_H
