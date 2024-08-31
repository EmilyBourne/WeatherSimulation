#include "rivers.h"
#include "proprietes_syst.h"
using namespace std;

//mèthode dessine de la classe dessinable
void rivers::dessine (std::ostream& flot) const {
	for(int i(0); i<Proprietes::nx; ++i) {
		for(int j(0); j<Proprietes::ny; ++j) {
			for (int k(0); k<Proprietes::nz; ++k) {
				bool b (false);
				for (size_t l(0); l<mon_range.size() and b==false; ++l) {
					if (mon_range[l]->position(i, j, k)==true) {
						b=true;
					}
				}
				flot << i << ' ' << j << ' ' << k << ' ' << b << endl;
			}
		}
		flot<< endl;
	}
}

//regarde s'il y a une rivière là ou pas
bool rivers::position(int x, int y, int z) const{
	bool rhone(false);
	int t(mon_range.size());
	for (int i(0); i<t; ++i) {
		bool h(mon_range[i]->position(x, y, z));
		if (h==true) {
			rhone = true;
		}
	}
	return rhone;
}

bool rivers::lac_ici(int x, int y, int z) const{
	bool leman(false);
	int t(mon_range.size());
	for (int i(0); i<t; ++i) {
		bool h(mon_range[i]->lac_ici(x, y, z));
		if (h==true) {
			leman = true;
		}
	}
	return leman;
}

//copie
mult_riv* rivers::copie() const{
	
	vector<mult_riv*> chaine_clone;
	for(size_t i(0); i<mon_range.size(); ++i){
		chaine_clone.push_back((*mon_range[i]).copie());
	}
	rivers* clone(new rivers(chaine_clone));
	return clone;
}


//constructeurs

rivers::rivers (gros_chaine_mont* M, vector<vector<int>> list, bool verbeuse, ostream& flot) {
	for (unsigned int i(0); i<list.size(); ++i) {
		if (list[i].size()!= 2) {
			if (verbeuse){
				flot << "erreur de déclaration de riviere " << i << "!!" << endl;
			}
		}
		else {
			mon_range.push_back(new riviere(M, list[i][0], list[i][1]));
		}
	}
}

rivers::rivers (gros_chaine_mont* M, int n, bool verbeuse, ostream& flot) {
	for (int i(0); i<n; ++i) {
		mon_range.push_back(new riviere(M));
	}
}

rivers::rivers (vector<mult_riv*>const& list) {
	for (unsigned int i(0); i<list.size(); ++i) {
		mon_range.push_back(list[i]->copie());
	}
}

rivers::rivers () {}

rivers::~rivers(){
	for (unsigned int i(0); i<mon_range.size(); ++i) {
		delete mon_range[i];
		mon_range[i]=nullptr;
	}
}

void rivers::affiche (ostream& flot) const {
	for (size_t i(0); i<mon_range.size(); ++i) {
		mon_range[i]->affiche(flot);
	}
}

/*
rivers*& operator= (rivers* const& m) {
	return m->copie();
}
*/
