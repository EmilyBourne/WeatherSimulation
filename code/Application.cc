#include "Application.h"
#include "proprietes_syst.h"
#include "parseur.h"

bool Application::OnInit()
{	
	parseur P("parseurnom.txt");
	monde = P.sys();
	
	fenetreGL=new FenetreGL(wxT("Nuages"), wxSize(800,600));
	
	fenetreControle=new FenetreControle();
	
	fenetreControle->Show(true);
	
	SetTopWindow(fenetreGL);
	
	timer=new wxTimer(this);
	timer->Start(150);
		Connect(wxID_ANY, wxEVT_TIMER, wxTimerEventHandler(Application::monde_evolue));
	timer->Stop();
	
	return (fenetreGL!=0 && fenetreControle!=0);
}

void Application::dessine(std::ostream& flot)
{
	monde->dessine(flot);
}

void Application::rafraichir(){
	fenetreGL->rafraichir();
}

void Application::monde_evolue(wxTimerEvent& event){
	monde->evolue((event.GetInterval())/1000.0);
	rafraichir();
}

void Application::orage(bool encours){
	fenetreControle->boxOrageChange(monde->orage_switch(encours));
}

void Application::orage(){
	fenetreControle->boxOrageChange(monde->orage_switch());
}

void Application::quitter()
{
    fenetreGL->Destroy();
    fenetreControle->Destroy();
    ExitMainLoop();
}

void Application::parametre (unsigned int code_param, unsigned int changement){
		switch(code_param)
    {
		// change l'affichage de la pression
        case 101:
            orage(changement);
            break;
        // change l'affichage de la temperature       
        case 102:
             orage();
             break;
        //change la pause
        case 103:
            pause(changement);
            break;
        // change la pause       
        case 104:
             pause();
             break;     
        // change l'affichage de la pression
        case 121:
            monde->parametre(121,changement);
            break;
        // change l'affichage de la temperature       
        case 122:
             monde->parametre(122,changement);
             break;
    }
}

void Application::pause(bool onoff){
	if (onoff) {
				timer->Stop();
			} else {
				timer->Start();
			}
}

void Application::pause(){
	if (timer->IsRunning()) {
				pause(true);
				fenetreControle->boxPlayChange(false);
			} else {
				pause(false);
				fenetreControle->boxPlayChange(true);
			}
}

IMPLEMENT_APP(Application)
