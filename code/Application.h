#ifndef APPLICATION_H
#define APPLICATION_H

#include "INCLUSIONS"
#include "FenetreGL.h"
#include "FenetreControle.h"
#include "iostream"
#include "Systeme3D.h"
#include "Systeme.h"

class Application : public wxApp
{
public:
	void dessine(std::ostream& flot=std::cout);
	void orage(bool encours);
	void orage();
	void quitter();
	
	//codes parametre	: (121) Systeme::parametre code 121 	, (122) Systeme::parametre code 122	, (101) orage(bool encours)					, (102) orage()			, (103) pause								, (104) pause
	//codes changement	: (121)/ (1)true (0) false				, (122)/ (1) true (0) false			, (101)/ (1) orage(true) (0) orage(false)	, (102)/ (any) orage()	, (103)/ (1) pause(true) (0) pause(false)	, (104)/ (any) pause()
	virtual void parametre (unsigned int code_param, unsigned int changement);
	
	void rafraichir();
	
	void pause(bool onoff);
	void pause();
	
private:
	bool OnInit(); //pour l'initialisation de l'app
	void monde_evolue(wxTimerEvent& event);
	
	FenetreGL* fenetreGL;
	
	FenetreControle* fenetreControle;
	
	Systeme3D* monde;
	
	wxTimer* timer;
};

DECLARE_APP(Application)

#endif
