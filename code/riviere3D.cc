#include "riviere3D.h"
#include "INCLUSIONS"
#include <cmath>
#include "proprietes_syst.h"
using namespace std;

riviere3D::riviere3D (gros_chaine_mont* m)
: riviere (m)
{}

riviere3D::riviere3D (gros_chaine_mont* m, int debutx, int debuty)
: riviere (m, debutx, debuty)
{}

mult_riv* riviere3D::copie() const{
		return new riviere3D(*this);
	}

riviere3D::~riviere3D(){}

void riviere3D::dessine (ostream& flot) const {
	glPushMatrix();
	glTranslated(-(Proprietes::nx)/2.0,-(Proprietes::ny)/2.0,1.0);
	for (size_t i(1); i<route.size()-1; ++i) {
		if (route[i].lac==false) {
			glLineWidth(3);
			glColor3ub(0,0,200);
			glBegin(GL_LINE_STRIP);
			
			glVertex3d(route[i-1].i , route[i-1].j,M->alti(route[i-1].i, route[i-1].j)+0.1);
			glVertex3d(route[i].i, route[i].j,M->alti(route[i].i, route[i].j)+0.1);
			
			glEnd();
			
			glBegin(GL_LINE_STRIP);
			
			glVertex3d(route[i].i, route[i].j,M->alti(route[i].i, route[i].j)+0.1);
			glVertex3d(route[i+1].i, route[i+1].j,M->alti(route[i+1].i, route[i+1].j)+0.1);
			
			glEnd();
		}
		else {
			//commence plus à droit possible, devient plus à gauche dans le lac
			int a(Proprietes::nx);
			//commence plus à gauche possible, devient plus à droit dans le lac
			int b(0);
			//commence plus en haut possible, devient plus en bas dans le lac
			int c(Proprietes::ny);
			//commence plus en bas possible, devient plus en haut dans le lac
			int d(0);
			//commence avec l'altitude maximale pour devenir la surface
			double min(Proprietes::nz);
			
			bool e(true);
			for (size_t j(i); e==true and j<route.size(); ++j) {
				if (route[j].lac==false) {
					e=false;
				}
				else {
					if (route[j].i<a){
						a=route[j].i;
					}
					if (route[j].i>b){
						b=route[j].i;
					}
					if (route[j].j<c){
						c=route[j].j;
					}
					if (route[j].j>d){
						d=route[j].j;
					}
				}
				++i;
			}
			for (int z(c); z<d; ++z) {
				double haut(M->alti(a,z));
				if(haut<min){
				min=haut;
				}
			}
			for (int z(a); z<b; ++z) {
				double haut(M->alti(z,d));
				if(haut<min){
				min=haut;
				}
			}
			for (int z(d); z>c; z=z-1) {
				double haut(M->alti(b,z));
				if(haut<min){
				min=haut;
				}
			}
			for (int z(b); z>a; z=z-1) {
				double haut(M->alti(z,c));
				if(haut<min){
				min=haut;
				}
			}
				
			glBegin(GL_QUAD_STRIP);
			
			glColor4ub(0,0,200, 255);
			glVertex3d(a,c,min+0.1);
			glVertex3d(a, d,min+0.1);
			glVertex3d(b,c,min+0.1);
			glVertex3d(b, d,min+0.1);
			
			glEnd();
			
			//i=i-1;
		}
	}
	glPopMatrix();
}
