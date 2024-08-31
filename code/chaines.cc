#include "chaines.h"
#include "montagne_lue.h"

using namespace std;

//mèthode dessine de la classe dessinable
void chaine_mont::dessine (std::ostream& flot) const {
	for (unsigned int i(0); i<mon_range.size(); ++i) {
		mon_range[i]->dessine(flot);
	}
}

//calcule de l'altitude
double chaine_mont::alti(double coord1, double coord2) const{
	double h(0);
	int t(mon_range.size());
	for (int i(0); i<t; ++i) {
		double nh(mon_range[i]->alti(coord1, coord2));
		if (h<nh) {
			h=nh;
		}
	}
	return h;
}

//copie
gros_chaine_mont* chaine_mont::copie() const{
	
	vector<gros_chaine_mont*> chaine_clone;
	for(size_t i(0); i<mon_range.size(); ++i){
		chaine_clone.push_back((*mon_range[i]).copie());
	}
	chaine_mont* clone(new chaine_mont(chaine_clone));
	return clone;
}


//constructeurs

chaine_mont::chaine_mont (vector<vector<double>> list, bool verbeuse, ostream& flot) {
	for (unsigned int i(0); i<list.size(); ++i) {
		if (list[i].size()!= 5) {
			if (verbeuse){
				flot << "erreur de déclaration de montagne " << i << "!!" << endl;
			}
		}
		else {
			mon_range.push_back(new montagne(list[i][0], list[i][1], list[i][2], list[i][3], list[i][4]));
		}
	}
}

chaine_mont::chaine_mont (vector<gros_chaine_mont*> list) {
	for (unsigned int i(0); i<list.size(); ++i) {
		mon_range.push_back(list[i]->copie());
	}
}

chaine_mont::chaine_mont (string fichier,double zscale) 
: mon_range(1,new montagne_lue(fichier, zscale))
{ }

chaine_mont::~chaine_mont(){
	for (unsigned int i(0); i<mon_range.size(); ++i) {
		delete mon_range[i];
		mon_range[i]=nullptr;
	}
}

std::vector<gros_chaine_mont*>& chaine_mont::mes_montagnes(){
	return mon_range;
}

chaine_mont::chaine_mont(){}
