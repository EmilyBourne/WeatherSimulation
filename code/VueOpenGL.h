#ifndef VUEOPENGL_H
#define VUEOPENGL_H

#include "INCLUSIONS"
#include "Camera.h"


class VueOpenGL : public wxGLCanvas
{
public:
	VueOpenGL(wxWindow* parent, wxSize const& taille=wxDefaultSize, 
				wxPoint const& position=wxDefaultPosition);
	
	void InitOpenGL();
	
	void appuiTouche(wxKeyEvent& event);
	
	void mouvementSouris(wxMouseEvent& event);
	void clicSouris(wxMouseEvent& event);
	void moletteSouris(wxMouseEvent& event);
	
private:
	void dessine(wxPaintEvent& event);
	Camera camera;
	int lxSouris;
	int lySouris;
	
};

#endif
