#ifndef PRJ_PARSEUR_H
#define PRJ_PARSEUR_H
#include <fstream>
#include <string>
#include "dessinable.h"
#include "nuages3D.h"
#include "mult_riv.h"
#include "ChampPotentiels.h"
#include "Systeme3D.h"
#include <vector>
#include "terrain3D.h"

struct member {
	string nom;
	string val;
	bool classe;
};

class parseur {
	public:
		parseur (string fichier);
		void affiche ();
		Systeme3D* sys ();
	private:
		void read ();
		void sort (vector<string>& V, size_t& i, int j);
		gros_chaine_mont* chaine (vector<member>& a);
		ChampPotentiels* champ (vector<member>& a);
		mult_riv* brook (vector<member>& a);
		void sol (vector<member>& a);
		void prop (vector<member>& s);
		void word (string& s);
		bool stringtodouble (std::string const& s, double& d);
		bool stringtoint (string const& s, int& i);
		bool getdouble (std::string s, double& a);
		bool getint (std::string s, int& a);
		bool getbool (string const& s, bool& a);
		bool getnum (string& s, double& a);
		bool getdenom (string& s, double& a);
		bool getstring (std::string& s, std::string& a);
		std::vector<std::vector<double>> divise (std::vector<double> v, int n);
		std::vector<std::vector<int>> divise (std::vector<int> v, int n);
		bool splitdouble (string s, std::vector<double>& arg);
		bool splitint (string s, std::vector<int>& arg);
		bool maths (char& a);
		void brack (string s, vector<vector<int>>& b);
		bool parantheses (vector<vector<int>> const& b, int const& a);
		
		ifstream file;
		vector<string> const classe;
		vector<vector<member>> info;
		Systeme3D* S;
		chaine_mont* M;
		ChampPotentiels* C;
		nuages3D* N;
		terrain3D* T;
};

#endif //PRJ_PARSEUR_H
