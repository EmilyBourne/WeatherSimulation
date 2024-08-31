#include "Camera.h"
#include <cmath>
//get
double Camera::r() const
{
	return r_;
}

double Camera::theta() const
{
	return theta_;
}

double Camera::phi() const
{
	return phi_;
}

//set
double& Camera::r()
{
	return r_;
}

double& Camera::theta()
{
	return theta_;
}

double& Camera::phi()
{
	return phi_;
}

//constructeur
Camera::Camera(double R, double THETA, double PHI)
: r_(R), theta_(THETA), phi_(PHI)
{
	
}

//methodes
void Camera::setVue() const
{
	gluLookAt(r_*sin(theta_)*sin(phi_), r_*sin(theta_)*cos(phi_), r_*cos(theta_), 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
}

void Camera::zoom(double valeur, double min, double max)
{
	if((r_+valeur)<=min){
		r_ = min;
	}
	else if((r_+valeur)>=max){
		r_ = max;
	}
	else if((r_+valeur)>min){
		r_ += valeur;
	}
}

void Camera::depl_lat(double valeur)
{
	phi_ += valeur;
}

void Camera::depl_vert(double valeur, double min, double max)
{
	if((theta_+valeur)<=min){
		theta_ = min;
	}
	else if((theta_+valeur)>=max){
		theta_ = max;
	}
	else if((theta_+valeur)){
		theta_ += valeur;
	}
}

void Camera::origine(){
	r_=80.0; 
	theta_=0.44;
	phi_=0.61;
}
