#ifndef FENETRECONTROLE_H
#define FENETRECONTROLE_H
 
#include "INCLUSIONS"

class FenetreControle : public wxFrame //Héritage
{
public:
	FenetreControle();
	virtual ~FenetreControle() {}
	void boxOrageChange(bool onoff);
	void boxPlayChange(bool onoff);
	
private:
	wxCheckBox* orage;
	wxCheckBox* temperature;
	wxCheckBox* pression;
	wxCheckBox* play;
	
	void BoxCheck(wxCommandEvent& event);
   
};
#endif
