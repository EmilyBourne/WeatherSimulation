#include "VueOpenGL.h"
#include "Application.h"

VueOpenGL::VueOpenGL(wxWindow* parent, wxSize const& taille, 
			wxPoint const& position)
:wxGLCanvas(parent, wxID_ANY, position, taille, wxSUNKEN_BORDER),
	camera()
{
    Connect(wxEVT_PAINT, wxPaintEventHandler(VueOpenGL::dessine));
    Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(VueOpenGL::appuiTouche));
    
    Connect(wxEVT_MOTION, wxMouseEventHandler(VueOpenGL::mouvementSouris));
	Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(VueOpenGL::clicSouris));
	Connect(wxEVT_LEFT_UP, wxMouseEventHandler(VueOpenGL::clicSouris));
	Connect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(VueOpenGL::clicSouris));
	Connect(wxEVT_RIGHT_UP, wxMouseEventHandler(VueOpenGL::clicSouris));
	Connect(wxEVT_MOUSEWHEEL, wxMouseEventHandler(VueOpenGL::moletteSouris));
	
    SetFocus();
}

void VueOpenGL::InitOpenGL() 
{
    SetCurrent();
    glEnable(GL_BLEND) ;								//transparence
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;	//transparence
    
    glEnable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, 4./3., 1.0, 1000.0);
 
	glClearColor(119/255.0, 181/255.0, 245/255.0, 1.0);//couleur du fond
	

	int argc = 1;
    char* argv[1] = {""};
    glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_DOUBLE);
 
	glMatrixMode(GL_MODELVIEW);
}

void VueOpenGL::appuiTouche(wxKeyEvent& event)
{
    switch(event.GetKeyCode())
    {
         // décrémente l'angle phi de la caméra lorsque l'on appuie sur la flèche gauche
        case WXK_LEFT:
            camera.depl_lat(-0.1);
            break;
        // incrémente l'angle phi de la caméra lorsque l'on appuie sur la flèche droite       
        case WXK_RIGHT:
             camera.depl_lat(+0.1);
             break;
        // décrémente l'angle theta de la caméra lorsque l'on appuie sur la flèche haut        
        case WXK_UP:
            camera.depl_vert(-0.1);
            break;
        // incrémente l'angle theta de la caméra lorsque l'on appuie sur la flèche bas      
        case WXK_DOWN:
            camera.depl_vert(+0.1);
            break;
        // diminue le rayon de la  caméra si on appuie sur 'W'
        case 'W': //Attention
            camera.zoom(-1.0);
            break;
        // augmente le rayon de la caméra si on appuie sur 'S'
        case 'S':
            camera.zoom(+1.0);
            break;
		// Pause sur la touche 'P'
		case 'P':
			wxGetApp().pause();
			break;
		// Retour à l'origine en appuyant sur 'O'
		case 'O':
            camera.origine();
            break;
        // Controle de l'orage
        case 'L':
			wxGetApp().parametre(102, 1);
			break;
    }
    Refresh(false);
}

void VueOpenGL::mouvementSouris(wxMouseEvent& event)
{
	if (event.RightIsDown())
	{
		int x(0), y(0);
		event.GetPosition(&x,&y);
		
		camera.depl_vert((-(lySouris-y))/60.0);
		camera.depl_lat((+(lxSouris-x))/60.0);
		
		event.GetPosition(&lxSouris,&lySouris);
		Refresh(false);
	}
}
void VueOpenGL::clicSouris(wxMouseEvent& event)
{
	event.GetPosition(&lxSouris,&lySouris);
}

void VueOpenGL::moletteSouris(wxMouseEvent& event)
{
	camera.zoom(-event.GetWheelRotation()/60.0);
}

void VueOpenGL::dessine(wxPaintEvent& event)
{
    SetCurrent();
     //initialise les données liées à la gestion de la profondeur
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     
    glLoadIdentity(); 
 
    // place la caméra
    camera.setVue();
                     
    //Commandes de dessin ici
    
	wxGetApp().dessine();
	
    //passage a l'ecran
	glFlush();
    SwapBuffers();
}
