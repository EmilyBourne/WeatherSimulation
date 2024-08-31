#ifndef CAMERA_H
#define CAMERA_H
 
#include "INCLUSIONS"
 
class Camera
{
public:
	//constructeur
	Camera(double R=80.0, double THETA=0.44, double PHI=0.61);
	//methodes
	void setVue() const;
	void zoom(double valeur, double min = 1.0, double max = 100.0);
	void depl_lat(double valeur);
	void depl_vert(double valeur, double min=0.1, double max=1.0);
	void origine();
	//get
	double r() const;
	double theta() const;
	double phi() const;
	//set
	double& r();
	double& theta();
	double& phi();
	
private:
   double r_;
   double theta_;
   double phi_;
};
#endif
