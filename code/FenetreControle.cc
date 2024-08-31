#include "FenetreControle.h"
#include "Application.h"

FenetreControle::FenetreControle()
: 	wxFrame(0, wxID_ANY, wxT("Contrôles"), wxDefaultPosition, wxSize(300, 120), wxCAPTION),
	orage(new wxCheckBox(this, wxID_ANY, wxT("orage"))),
	temperature(new wxCheckBox(this, wxID_ANY, wxT("temperature"))),
	pression(new wxCheckBox(this, wxID_ANY, wxT("pression"))),
	play(new wxCheckBox(this, wxID_ANY, wxT("play/pause")))
{	
	Connect(wxID_ANY, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(FenetreControle::BoxCheck));
	
	wxBoxSizer* hsizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* vsizer = new wxBoxSizer(wxVERTICAL);
	
	//Affichage
	vsizer->Add(orage, 0, wxTOP, 5);
	vsizer->Add(temperature, 0, wxTOP, 5);
	vsizer->Add(pression, 0, wxTOP, 5);
	vsizer->Add(play, 0, wxTOP, 5);
	
	hsizer->Add(vsizer, 1, wxLEFT | wxRIGHT| wxEXPAND, 20);
	
	SetSizer(hsizer);
}

void FenetreControle::BoxCheck(wxCommandEvent& event){
	wxGetApp().parametre(101, orage->GetValue());
	wxGetApp().parametre(122, temperature->GetValue());
	wxGetApp().parametre(121, pression->GetValue());
	
	unsigned int stop(play->GetValue());
	
	if(stop==1){
		stop = 0;
	}
	else {
		stop = 1;
	}
	
	wxGetApp().parametre(103, stop);
	wxGetApp().rafraichir();
}

void FenetreControle::boxOrageChange(bool onoff){
	orage->SetValue(onoff);
}

void FenetreControle::boxPlayChange(bool onoff){
	play->SetValue(onoff);
}

