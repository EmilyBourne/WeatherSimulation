#include "rivers3D.h"
#include "INCLUSIONS"
#include "riviere3D.h"
using namespace std;

//constructeurs

rivers3D::rivers3D (gros_chaine_mont* M, vector<vector<int>> list, bool verbeuse, ostream& flot) {
	for (unsigned int i(0); i<list.size(); ++i) {
		if (list[i].size()!= 2) {
			if (verbeuse){
				flot << "erreur de déclaration de riviere " << i << "!!" << endl;
			}
		}
		else {
			mon_range.push_back(new riviere3D(M, list[i][0], list[i][1]));
		}
	}
}

rivers3D::rivers3D (gros_chaine_mont* M, int n, bool verbeuse, ostream& flot) {
	for (int i(0); i<n; ++i) {
		mon_range.push_back(new riviere3D(M));
	}
}

rivers3D::rivers3D (vector<mult_riv*>const& list)
: rivers(list)
{}

//déstructeur
rivers3D::~rivers3D() {}

//dessine
void rivers3D::dessine (ostream& flot) const {
	for (unsigned int i(0); i<mon_range.size(); ++i) {
		mon_range[i]->dessine(flot);
	}
}	

//copie
mult_riv* rivers3D::copie() const{
	
	vector<mult_riv*> chaine_clone;
	for(size_t i(0); i<mon_range.size(); ++i){
		chaine_clone.push_back((*mon_range[i]).copie());
	}
	rivers* clone(new rivers3D(chaine_clone));
	return clone;
}
