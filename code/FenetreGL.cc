#include "FenetreGL.h"
#include "Application.h"

FenetreGL::FenetreGL(wxString titre, wxSize taille)
: wxFrame(0, wxID_ANY, titre, wxDefaultPosition, taille, 
			wxDEFAULT_FRAME_STYLE & ~ (wxRESIZE_BORDER | wxRESIZE_BOX | wxMAXIMIZE_BOX)),
			vueopengl(new VueOpenGL(this))
{	
	Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(FenetreGL::onClose)); //Marche pas, pourquoi?? devrait enlever la segmentation fault a la fermeture du programme
	
	Center();
	Show(true);
	vueopengl->InitOpenGL();
}

void FenetreGL::rafraichir(){
	vueopengl->Refresh(false);
}

void FenetreGL::onClose(wxCloseEvent &event){
	wxGetApp().quitter();
}
