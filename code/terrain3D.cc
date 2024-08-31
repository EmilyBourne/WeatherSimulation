#include "terrain3D.h"
#include "proprietes_syst.h"

terrain3D::terrain3D (chaine_mont& mont, nuages& sky)
: terrain(mont, sky)
{ }

void terrain3D::dessine(std::ostream& flot) const{
	
	glPushMatrix();
	glTranslated(-(Proprietes::nx)/2.0 + 0.5,-(Proprietes::ny)/2.0 + 0.5,0.9);
	
	glColor3ub(243*0.5, 214 , 23*0.5);
	GLUquadric* quadrique=gluNewQuadric();
	gluDisk(quadrique, 0.0, ((Proprietes::nx + Proprietes::ny)/2.0)*5, 30, 1);
	gluDeleteQuadric(quadrique);
	
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(-(Proprietes::nx)/2.0,-(Proprietes::ny)/2.0,1);
	
	for(int a(0); a<Proprietes::nx; ++a){
		for(int b(0); b<Proprietes::ny; ++b){
			if(sol[a][b].type==0){
				glColor3ub(243*(1-sol[a][b].plantes), 214, 23*(1-sol[a][b].plantes));
			}		
			else if(sol[a][b].type==1){
				glColor3ub(167,103 + (255-103)*sol[a][b].plantes,38);
			}
			else if(sol[a][b].type==2){
				glColor3ub(103,103 + (255-103)*sol[a][b].plantes,103);
			}
			
			glBegin(GL_QUAD_STRIP);
			glVertex3d(a,b,M.alti(a,b));
			glVertex3d(a,b+1,M.alti(a,b+1));
			glVertex3d(a+1,b,M.alti(a+1,b));
			glVertex3d(a+1,b+1,M.alti(a+1,b+1));
			glEnd();
			
		}
	}
	glPopMatrix();
}

