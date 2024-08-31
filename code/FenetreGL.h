#ifndef FENETREGL_H
#define FENETREGL_H
 
#include "INCLUSIONS"
#include "VueOpenGL.h"

class FenetreGL : public wxFrame //Héritage
{
public:
	FenetreGL(wxString titre, wxSize taille);
	void rafraichir();
	void onClose(wxCloseEvent &event);
	
private:
	VueOpenGL* vueopengl;
   
};
#endif
