#include "nuages3D.h"
#include "proprietes_syst.h"
#include "INCLUSIONS"
#include <sstream>

using namespace std;

	void nuages3D::dessine (std::ostream& flot) const{
		for (int i(1); i<Proprietes::nx-1; ++i) {
			for (int j(1); j<Proprietes::ny-1; ++j) {
				for (int k(1); k<Proprietes::nz-1; ++k) {
					//dessin pression et temp
					if (i%5==2 and j%5==2 and k%5==2) {
						if (k>M->alt(i,j)) {
							glColor3f(0,0,0);
							if (affiche_pression==true) {
								glPushMatrix();
								glTranslated((i-(Proprietes::nx)/2),(j-(Proprietes::ny)/2),k+1);
								glRasterPos3f(0,0,0);
								string a(inttostring(sky[i][j][k].press()));
								glutBitmapString(GLUT_BITMAP_HELVETICA_12, (unsigned char*)a.c_str());
								glPopMatrix();
							}
							if (affiche_temperature==true) {
								glPushMatrix();
								glTranslated((i-(Proprietes::nx)/2),(j-(Proprietes::ny)/2),k+1);
								glRasterPos3f(0,0,0);
								string a(inttostring(sky[i][j][k].temp()));
								glutBitmapString(GLUT_BITMAP_HELVETICA_12, (unsigned char*)a.c_str());
								glPopMatrix();
							}
						}
					}
					//dessin nuage
					if(nuage_ici(i,j,k)){
						if(pluie_ici(i,j,k)==true){
							glColor4d(0.5,0.5,0.5,0.7);
						}
						else{
							glColor4d(1.0,1.0,1.0,0.7);
						}
						glPushMatrix();
						glTranslated((i-(Proprietes::nx)/2),(j-(Proprietes::ny)/2),k+1);
					
						glBegin(GL_QUADS);
	
						glVertex3d(0.5,0.5,0.5);
						glVertex3d(-0.5,0.5,0.5);
						glVertex3d(-0.5,0.5,-0.5);
						glVertex3d(0.5,0.5,-0.5);
			
						glVertex3d(0.5,-0.5,0.5);
						glVertex3d(0.5,0.5,0.5);
						glVertex3d(0.5,0.5,-0.5);
						glVertex3d(0.5,-0.5,-0.5);
 
						glVertex3d(0.5,-0.5,0.5);
						glVertex3d(-0.5,-0.5,0.5);
						glVertex3d(-0.5,-0.5,-0.5);
						glVertex3d(0.5,-0.5,-0.5);
 
						glVertex3d(-0.5,-0.5,0.5);
						glVertex3d(-0.5,0.5,0.5);
						glVertex3d(-0.5,0.5,-0.5);
						glVertex3d(-0.5,-0.5,-0.5);
 
						glVertex3d(0.5,-0.5,0.5);
						glVertex3d(0.5,0.5,0.5);
						glVertex3d(-0.5,0.5,0.5);
						glVertex3d(-0.5,-0.5,0.5);
 
						glVertex3d(0.5,-0.5,-0.5);
						glVertex3d(0.5,0.5,-0.5);
						glVertex3d(-0.5,0.5,-0.5);
						glVertex3d(-0.5,-0.5,-0.5);
 
						glEnd();
						glPopMatrix();
					}
				}
			}
		}
	}
	
	void nuages3D::parametre (unsigned int code_param, unsigned int changement){
		switch(code_param)
    {
         // change l'affichage de la pression
        case 1:
            if(changement == 0){
				affiche_pression = false;
			}
			else if(changement == 1){
				affiche_pression = true;
			}
			
            break;
        // change l'affichage de la temperature       
        case 2:
             if(changement == 0){
				affiche_temperature = false;
			}
			else if(changement == 1){
				affiche_temperature = true;
			}
             break;
    }
}
	
	bool nuages3D::nuage_ici(unsigned int i,unsigned int j,unsigned int k) const{
		return (nuages::nuage_ici(i,j,k));	
	}
	
	nuages3D::nuages3D (ChampPotentiels c, gros_chaine_mont* m)
	: nuages(c), affiche_pression(false), affiche_temperature(false), M(m)
	{}

	bool& nuages3D::Pression () {return affiche_pression; }
	bool& nuages3D::Temperature () {return affiche_temperature; }

	string nuages3D::inttostring (int i) const {
		stringstream ss;
		ss << i;
		return ss.str();
	}
