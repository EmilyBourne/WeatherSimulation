CXX=g++-4.6
CC=$(CXX)
CXXFLAGS = -std=c++0x -pedantic -Wall `wx-config --cxxflags` -g -O2  -pg
LDFFLAGS += -pg
LDLIBS = -lgraph `wx-config --libs gl,core,base` -lGLU -lglut

VPATH=code

all:  Application testMontagneLue testParseur testRiviere testMontagne testVecteur2D testPotentiel testLaplacien testPotentiels testCubedAir testNuages testDessinable testChaines testSysteme testNuageEvolution testTerrain 

constantes.o: constantes.h constantes.cc

proprietes_syst.o: proprietes_syst.h proprietes_syst.cc

Vecteur2D.o: Vecteur2D.h Vecteur2D.cc

montagne.o: montagne.h montagne.cc dessinable.h chaines.h gros_chaines.h proprietes_syst.h

Potentiel.o: Potentiel.h Potentiel.cc Vecteur2D.h

ChampPotentiels.o: ChampPotentiels.h ChampPotentiels.cc Potentiel.h Vecteur2D.h montagne.h chaines.h dessinable.h gros_chaines.h proprietes_syst.h montagne_lue.h

cubed_air.o: cubed_air.h cubed_air.cc constantes.h dessinable.h proprietes_syst.h

nuages.o: nuages.h nuages.cc cubed_air.h ChampPotentiels.h Potentiel.h Vecteur2D.h montagne.h constantes.h dessinable.h proprietes_syst.h

nuages3D.o: nuages3D.h nuages3D.cc nuages.h proprietes_syst.o

chaines.o: gros_chaines.h chaines.h chaines.cc dessinable.h montagne.h proprietes_syst.h montagne_lue.h

montagne_lue.o: montagne_lue.h montagne_lue.cc gros_chaines.h proprietes_syst.h

terrain.o: terrain.h terrain.cc chaines.h nuages.h proprietes_syst.h

terrain3D.o: terrain3D.h terrain3D.cc terrain.h proprietes_syst.h

Systeme.o: Systeme.cc Systeme.h dessinable.h proprietes_syst.h ChampPotentiels.h nuages.h cubed_air.h Potentiel.h Vecteur2D.h chaines.h montagne.h constantes.h terrain.o

Systeme3D.o: Systeme3D.cc Systeme3D.h Systeme.h dessinable.h ChampPotentiels.h nuages.h cubed_air.h Potentiel.h Vecteur2D.h chaines.h montagne.h constantes.h mult_riv.h rivers.h riviere.h rivers3D.h riviere3D.h gros_chaines.h proprietes_syst.h terrain.h terrain3D.o

riviere.o: riviere.h riviere.cc Vecteur2D.h rivers.o

rivers.o: mult_riv.h rivers.h rivers.cc dessinable.h

riviere3D.o: riviere3D.h riviere3D.cc riviere.h Vecteur2D.h rivers.o

rivers3D.o: rivers3D.h rivers3D.cc mult_riv.h rivers.h dessinable.h gros_chaines.o

gros_chaines.o: gros_chaines.h gros_chaines.cc dessinable.h

parseur.o: parseur.h parseur.cc dessinable.h  Systeme3D.h nuages3D.h rivers3D.h riviere3D.h ChampPotentiels.h constantes.h

Application.o: Application.cc Application.h FenetreGL.h Systeme3D.h Systeme.h proprietes_syst.h montagne_lue.h dessinable.h

FenetreGL.o: FenetreGL.cc FenetreGL.h VueOpenGL.h Application.h

FenetreControle.o: FenetreControle.cc FenetreControle.h Application.h

VueOpenGL.o: VueOpenGL.cc VueOpenGL.h Camera.h Application.h FenetreGL.h

Camera.o: Camera.cc Camera.h

Application: Application.o FenetreGL.o FenetreControle.o VueOpenGL.o Camera.o Systeme.o Systeme3D.o ChampPotentiels.o nuages.o cubed_air.o Potentiel.o Vecteur2D.o montagne.o chaines.o constantes.o  nuages3D.o rivers.o riviere.o rivers3D.o riviere3D.o gros_chaines.o proprietes_syst.o montagne_lue.o terrain.o terrain3D.o parseur.o dessinable.h gros_chaines.o

testPotentiels: testPotentiels.cc ChampPotentiels.o Potentiel.o Vecteur2D.o montagne.o chaines.o gros_chaines.o proprietes_syst.o montagne_lue.o

testLaplacien: testLaplacien.cc ChampPotentiels.o Potentiel.o Vecteur2D.o montagne.o chaines.o gros_chaines.o proprietes_syst.o montagne_lue.o

testPotentiel: testPotentiel.cc Potentiel.o Vecteur2D.o 

testVecteur2D: testVecteur2D.cc Vecteur2D.o

testMontagne: testMontagne.cc montagne.o gros_chaines.o proprietes_syst.o

testCubedAir: testCubedAir.cc cubed_air.o constantes.o proprietes_syst.o

testNuages: testNuages.cc cubed_air.o nuages.o ChampPotentiels.o Potentiel.o Vecteur2D.o chaines.o montagne.o constantes.o gros_chaines.o proprietes_syst.o montagne_lue.o

testDessinable: testDessinable.cc dessinable.h cubed_air.o nuages.o ChampPotentiels.o Potentiel.o Vecteur2D.o montagne.o constantes.o chaines.o gros_chaines.o proprietes_syst.o montagne_lue.o

testChaines: testChaines.cc chaines.o gros_chaines.o dessinable.h montagne.o proprietes_syst.o montagne_lue.o

testSysteme: testSysteme.cc Systeme.o ChampPotentiels.o nuages.o cubed_air.o Potentiel.o Vecteur2D.o chaines.o constantes.o montagne.o gros_chaines.o proprietes_syst.o montagne_lue.o terrain.o

testNuageEvolution: testNuageEvolution.cc nuages.o cubed_air.o ChampPotentiels.o Potentiel.o Vecteur2D.o montagne.o constantes.o dessinable.h chaines.o gros_chaines.o proprietes_syst.o montagne_lue.o

testRiviere: testRiviere.cc mult_riv.h rivers.o Vecteur2D.o gros_chaines.o  dessinable.h montagne.o chaines.o riviere.o proprietes_syst.o montagne_lue.o

testTerrain: testTerrain.cc terrain.o proprietes_syst.o nuages.o chaines.o cubed_air.o constantes.o montagne.o montagne_lue.o ChampPotentiels.o Vecteur2D.o Potentiel.o gros_chaines.o

testParseur: testParseur.cc parseur.o dessinable.h  Systeme3D.o nuages3D.o rivers3D.o riviere3D.o ChampPotentiels.o Systeme.h cubed_air.o Potentiel.o Vecteur2D.o chaines.o montagne.o constantes.o mult_riv.h rivers.o riviere.o gros_chaines.o nuages.o Systeme.o proprietes_syst.o montagne_lue.o terrain.o terrain3D.o

testMontagneLue: testMontagneLue.cc montagne_lue.o proprietes_syst.o

clean:
	@-/bin/rm -f *.o
