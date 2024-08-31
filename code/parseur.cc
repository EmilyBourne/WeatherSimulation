#include <iostream>
#include "parseur.h"
#include <cmath>
#include "chaines.h"
#include <stack>
#include "rivers3D.h"
#include "riviere3D.h"
#include "montagne_lue.h"
using namespace std;

parseur::parseur (string fichier)
: file(fichier), classe({"montagne", "Application","ChampPotentiels", "rivers3D", "chaine_mont", "riviere3D", "Systeme3D", "Proprietes", "terrain3D"}) {
	string s;
	getline(file,s);
	file.close();
	file.open(s);
	read();
}

void parseur::read (){
	vector<string> V;
	string s;
	while (getline(file,s)) {
		V.push_back(s);
	}
	size_t j(0);
	sort (V, j, -1);
	vector<gros_chaine_mont*> mont;
	vector<mult_riv*> riv;
	/* trouve classes qui ont besoin d'être initialisé avant les autres, eg Proprietes, montagnes
	 * trouve tous les autres pour les initialiser après
	 * */
	vector<int> colonne(5, -1);
	vector<int> colonne_riv;
	for (int i(0), taille(info.size()); i<taille; ++i) {
		if (info[i][0].nom=="Proprietes") {
			colonne[0]=i;
		}
		else if (info[i][0].nom=="ChampPotentiels") {
			colonne[1]=i;
		}
		else if (info[i][0].nom=="chaine_mont" or info[i][0].nom=="montagne") {
			colonne.push_back(i);
		}
		else if (info[i][0].nom=="riviere3D" or info[i][0].nom=="rivers3D") {
			colonne_riv.push_back(i);
		}
		else if (info[i][0].nom=="Systeme3D") {
			colonne[2]=i;
		}
		else if (info[i][0].nom=="Application") {
			colonne[3]=i;
		}
		else if (info[i][0].nom=="terrain3D") {
			colonne[4]=i;
		}
	}
	//s'il faut, initialise les propriétés
	if (colonne[0]!=-1) {
		prop(info[colonne[0]]);
	}
	//crée tous les montagnes et les stocke dans un tableau de gros_chaine_mont
	for (j=5; j<colonne.size(); ++j) {
		mont.push_back(chaine(info[colonne[j]]));
	}
	/* Crée un montagne3D et le stocke dans les attributs en utilisant le tableau de gros_chaine_mont.
	 * Si ceci est vide, la montagne sera d'altitude 0 de partout
	 * */
	M=new chaine_mont(mont);
	//s'il y a un champ définie, on le crée comme démandé, sinon, on en crée par défaut
	if (colonne[1]==-1) {
		member mm ({"NUL", "", true});
		vector<member> vm ({mm});
		C=champ(vm);
	}
	else {
		C=champ(info[colonne[1]]);
	}
	for (j=0; j<colonne_riv.size(); ++j) {
		riv.push_back(brook(info[colonne_riv[j]]));
	}
	rivers3D* R (new rivers3D(riv));
	N=new nuages3D(*C, M);
	N->init_source_humi(*R, *M);
	sol(info[colonne[4]]);
	S=new Systeme3D(M,C, N, T, R);
}

void parseur::sort (vector<string>& V, size_t& i, int j) {
	//cherche balise d'ouverture, soit classe, soit premier membre d'un classe
	int d(V[i].find('<'));
	while (d==-1) {
		++i;
		d=V[i].find('<');
	}
	//cherche fin de la balise d'ouverture, s'il y en a pas affiche un message d'erreur
	//TRY
	int f(V[i].find('>'));
	if (f==-1) {
		cerr << "Erreur no >" << endl;
	}
	else {
		//prendre le nom sans '<' et '>'
		string a(V[i].substr(d+1, f-d-1));
		bool boo(true);
		do {
			//enlève info dont on n'a plus besoin
			int t(V[i].size());
			if (f==t-1) {
				V[i]="";
				++i;
			}
			else {
				V[i]=V[i].substr(f+1, t-f-1);
			}
			bool b(false);
			//vérifie si la balise est une classe ou pas
			for (size_t k(0); k<classe.size() and b==false; ++k) {
				if (a==classe[k]) {
					b=true;
				}
			}
			//si c'est une classe refaire la fonction sort mais dans un nouveau colonne d'info
			if (b==true) {
				info.push_back({});
				info[info.size()-1].push_back({a, "", true});
				sort(V,i,info.size()-1);
				//si on a examiné tous les classes on sort de la fonction
				if (i==V.size()-1) {
					break;
				}
			}
			else if (a[0]=='!' and a[1]=='-' and a[2]=='-') {
				//si c'est un commentaire on trouve le fin et on passe tous qu'on ne veut pas lire
				int e(V[i].find("-->"));
				while (e==-1) {
					++i;
					e=V[i].find("-->");
				}
				t=V[i].size();
				if (e==t-3) {
					V[i]="";
				}
				else {
					V[i]=V[i].substr(e+3, t-e-3);
				}
			}
			else if (a[0]=='/') {
				/* Si c'est une balise de fermeture on remets les fleches pour qu'il puisse être traité
				 * de la bonne façon plus tard et on le remets dans le tableau.
				 * On n'utilise ceci que si la classe est vide
				 * */
				i=i-1;
				V[i]='<'+a+'>';
			}
			else {
				//si ce n'est ni un commentaire ni une classe, stocker les données
				member m({a, "", false});
				bool cont (true);
				while (cont==true) {
					//cherche la balise de fermeture il n'y en a pas, ajoute la ligne au valeur d'être analysé
					d=V[i].find("</");
					if (d==-1) {
						m.val=m.val+' '+V[i];
						++i;
					}
					else {
						//s'il y a une balise de fermeture, ajoute tous l'information qui se trouve derrière ceci
						m.val=m.val+V[i].substr(0,d);
						V[i]=V[i].substr(d+2, V[i].size()-d-2);
						/*cherche fin de la balise. S'il n'y en a pas donner un message d'erreur
						 * et arreter les boucles
						 * */
						f=V[i].find('>');
						if (f==-1) {
							cerr << "erreur no >" << endl;
							cont=false;
							boo=false;
						}
						else if (m.nom==V[i].substr(0,f)) {
							/*si on a trouvé et c'est la bonne balise arreter ce boucle et effacer
							 * les données dont on n'a plus besoin
							 * */
							cont=false;
							t=V[i].size();
							if (f==t-1) {
								V[i]="";
								++i;
							}
							else {
								V[i]=V[i].substr(f+1,V[i].size()-f-1);
							}
						}
						else if (m.nom!=V[i].substr(0,f)) {
							//si c'est la mauvaise balise on coupe les boucles
							cerr << "erreur not same name" << endl;
							cont=false;
							boo=false;
						}
					}
				}
				//on ajoute l'information recolté au colonne d'info
				info[j].push_back(m);
			}
			//cherche balise d'ouverture, soit fin de la classe, soit prochain membre de la classe
			d=V[i].find('<');
			while (d==-1) {
				++i;
				d=V[i].find('<');
			}
			//cherche fin de la balise d'ouverture, s'il y en a pas affiche un message d'erreur
			f=V[i].find('>');
			if (f==-1) {
				cerr << "Erreur no >" << endl;
				boo=false;
			}
			else {
				//prendre le nom sans '<' et '>'
				a=V[i].substr(d+1, f-d-1);
				if (a[0]=='/') {
					//si c'est une balise de fermeture arrete le boucle
					boo=false;
					if (info[j][0].nom!=a.substr(1, a.size()-1)) {
						//si ce n'est pas la bonne balise affiche un message d'erreur
						cerr << "Erreur" << endl;
					}
					else {
						//si oui, effacer les données dont on n'a plus besoin
						int t(V[i].size());
						if (f==t-1) {
							V[i]="";
						}
						else {
							V[i]=V[i].substr(f+1, t-f-1);
						}
					}
				}
			}
		} while (boo==true);
	}
}

void parseur::affiche () {
	for (size_t i(0); i<info.size(); ++i) {
		for (size_t j(0); j<info[i].size(); ++j) {
			cout << "nom     : " << info[i][j].nom << endl;
			cout << "valeur  : " << info[i][j].val << endl;
			cout << "classe? : " << info[i][j].classe << endl << endl;
		}
		cout << endl << endl;
	}
}

void parseur::prop (vector<member>& s) {
	bool err(true);
	for(size_t i(1); i<s.size() and err==true; ++i) {
		if (s[i].nom=="v_infinie") {
			err=getdouble(s[i].val, Proprietes::v_infinie);
			if (err==false) {
				Proprietes::v_infinie=20.0;
				cerr << "Erreur de v_infinie" << endl;
			}
		}
		else if (s[i].nom=="T_infinie") {
			err=getdouble(s[i].val, Proprietes::T_infinie);
			if (err==false) {
				Proprietes::T_infinie=20.0;
				cerr << "Erreur de T_infinie" << endl;
			}
		}
		else if (s[i].nom=="P_infinie") {
			err=getdouble(s[i].val, Proprietes::P_infinie);
			if (err==false) {
				Proprietes::P_infinie=20.0;
				cerr << "Erreur de P_infinie" << endl;
			}
		}
		else if (s[i].nom=="nx") {
			err=getint(s[i].val, Proprietes::nx);
			if (err==false) {
				Proprietes::nx=20.0;
				cerr << "Erreur de nx" << endl;
			}
		}
		else if (s[i].nom=="ny") {
			err=getint(s[i].val, Proprietes::ny);
			if (err==false) {
				Proprietes::ny=20.0;
				cerr << "Erreur de ny" << endl;
			}
		}
		else if (s[i].nom=="nz") {
			err=getint(s[i].val, Proprietes::nz);
			if (err==false) {
				Proprietes::nz=30;
				cerr << "Erreur de nz" << endl;
			}
		}
		else if (s[i].nom=="lambda") {
			err=getnum(s[i].val, Proprietes::lambdaNum);
			if (err==false) {
				Proprietes::lambdaNum=20.0;
				cerr << "Erreur de lambda" << endl;
			}
			else {
				err=getdenom(s[i].val, Proprietes::lambdaDenom);
				if (err==false) {
					Proprietes::lambdaDenom=29.0;
					cerr << "Erreur de lambda" << endl;
				}
			}
		}
	}
}

ChampPotentiels* parseur::champ (vector<member>& a) {
	ChampPotentiels c;
	c.initialise(*M);
	if (a[1].nom=="arguments") {
		vector<double> arg;
		splitdouble(a[1].val, arg);
		if (arg.size()==1) {
			c.resolution(arg[0], *M);
		}
		else if (arg.size()==2) {
			c.resolution(arg[0], *M, arg[1]);
		}
		else {
			bool verb;
			bool b(getbool(a[1].val, verb));
			if (b==true) {
				c.resolution (arg[0], *M, arg[1], arg[2], verb);
			}
			else {
				c.resolution (arg[0], *M, arg[1], arg[2]);
			}
		}
	}
	else {
		double eps(0.1), errmax(1e-4);
		int intermax(3000);
		bool verb(false);
		bool b (true);
		for (size_t i(0); i<a.size() and b==true; ++i) {
			if (a[i].nom=="epsilon") {
				b=getdouble(a[i].val, eps);
			}
			else if (a[i].nom=="errmax") {
				b=getdouble(a[i].val, errmax);
			}
			else if (a[i].nom=="intermax") {
				b=getint(a[i].val, intermax);
			}
			else if (a[i].nom=="verbeuse") {
				b=getbool(a[i].val, verb);
			}
		}
		c.resolution (eps, *M, errmax, intermax, verb);
	}
	C=new ChampPotentiels(c);
	return C;
}

gros_chaine_mont* parseur::chaine (vector<member>& a) {
	bool b(true);
	if (a[0].nom=="montagne") {
		vector<double> arg;
		if (a[1].nom=="arguments") {
			b=splitdouble(a[1].val, arg);
			if (b==false) {
				arg={15, 15, 18, 5, 10};
			}
		}
		else {
			arg={15, 15, 18, 5, 10};
			for (size_t i(1); i<a.size(); ++i) {
				if (a[i].nom=="centreX") {
					b=getdouble(a[i].val,arg[0]);
					if (b==false) {
						arg[0]=15;
					}
				}
				else if (a[i].nom=="centreY") {
					b=getdouble(a[i].val,arg[1]);
					if (b==false) {
						arg[1]=15;
					}
				}
				else if (a[i].nom=="hauteur") {
					b=getdouble(a[i].val,arg[2]);
					if (b==false) {
						arg[2]=18;
					}
				}
				else if (a[i].nom=="etalementX") {
					b=getdouble(a[i].val,arg[3]);
					if (b==false) {
						arg[3]=5;
					}
				}
				else if (a[i].nom=="etalementY") {
					b=getdouble(a[i].val,arg[4]);
					if (b==false) {
						arg[4]=10;
					}
				}
			}
		}
		return new montagne(arg[0], arg[1], arg[2], arg[3], arg[4]);
	}
	else if (a[0].nom=="chaine_mont") {
		if (a.size()==1) {
			return new chaine_mont({new montagne_lue()});
		}
		else if(a[1].nom=="arguments") {
			string s;
			b=getstring(a[1].val, s);
			if (b==true) {
				double dbl;
				b=getdouble(a[1].val, dbl);
				if (b==false) {
					dbl=1.0;
				}
				return new chaine_mont(s, dbl);
			}
			else {
				b=true;
				vector<double> d;
				b=splitdouble(a[1].val, d);
				vector<vector<double>> m;
				m=divise(d, 5);
				if (b==true) {
					bool verb;
					b=getbool(a[1].val, verb);
					if (b==true) {
						return new chaine_mont(m, verb);
					}
					return new chaine_mont(m);
				}
			}
		}
		else {
			bool eststring(false);
			string s;
			vector<double> d;
			bool verb;
			bool estverb(false);
			double zscale(1.0);
			for (size_t i(1); i<a.size() and b==true; ++i) {
				if (a[i].nom=="list") {
					b=splitdouble(a[1].val, d);
				}
				else if (a[i].nom=="verbeuse") {
					b=getbool(a[i].val, verb);
					if (b==true) {
						estverb=true;
					}
				}
				else if (a[i].nom=="fichier") {
					eststring=getstring(a[i].val, s);
				}
				else if (a[i].nom=="zscale") {
					b=getdouble(a[i].val, zscale);
				}
			}
			if (eststring==true) {
				return new chaine_mont(s,zscale);
			}
			else {
				vector<vector<double>> m;
				if (b==true) {
					m=divise(d, 2);
				}
				if (estverb==true) {
					return new chaine_mont(m, verb);
				}
				else {
					return new chaine_mont(m);
				}
			}
		}
	}
	cerr << "Vous avez oublié d'écrire votre montagne!" << endl;
	return new montagne({15, 15, 18, 5, 10});
}

mult_riv* parseur::brook (vector<member>& a) {
	bool b(true);
	if (a[0].nom=="riviere3D") {
		if (a.size()==1) {
			return new riviere3D(M);
		}
		else if (a[1].nom=="arguments") {
			vector<double> debut;
			b=splitdouble(a[1].val, debut);
			if (b==true and debut.size()>=2) {
				return new riviere3D(M, debut[0], debut[1]);
			}
		}
		else{
			vector<int> debut (2, 0);
			int x(0);
			for (size_t i(1); i<a.size() and b==true; ++i) {
				if (a[i].nom=="debutx") {
					b=getint(a[i].val,debut[0]);
					if (b==true) {
						++x;
					}
				}
				else if (a[i].nom=="debuty") {
					b=getint(a[i].val,debut[1]);
					if (b==true) {
						++x;
					}
				}
			}
			if (b==true and x==2) {
				return new riviere3D(M, debut[0], debut[1]);
			}
		}
	}
	else if (a[0].nom=="rivers3D") {
		if (a.size()==1) {
			return new rivers3D(M);
		}
		else if (a[1].nom=="arguments") {
			bool verb;
			bool estverb;
			estverb=getbool(a[1].val, verb);
			vector<int> d;
			b=splitint(a[1].val, d);
			if (d.size()==1) {
				if (estverb==true) {
					return new rivers3D(M, d[0], verb);
				}
				else {
					return new rivers3D(M, d[0]);
				}
			}
			else {
				vector<vector<int>> m;
				m=divise(d, 2);
				if (b==true) {
					if (estverb==true) {
						return new rivers3D (M, m, verb);
					}
					else {
						return new rivers3D (M, m);
					}
				}
			}
		}
		else {
			vector<int> d;
			int n;
			bool verb;
			bool estverb;
			for (size_t i(1); i<a.size() and b==true; ++i) {
				if (a[i].nom=="list") {
					b=splitint(a[1].val, d);
				}
				else if (a[i].nom=="verbeuse") {
					b=getbool(a[i].val, verb);
					if (b==true) {
						estverb=true;
					}
				}
				else if (a[i].nom=="n") {
					b=getint(a[i].val, n);
				}
			}
			if (b==true) {
				if (d.size()==0) {
					if (estverb==true) {
						return new rivers3D(M, n, verb);
					}
					else {
						return new rivers3D(M, n);
					}
				}
				else {
					vector<vector<int>> m;
					m=divise(d, 2);
					if (estverb==true) {
						return new rivers3D (M, m, verb);
					}
					else {
						return new rivers3D (M, m);
					}
				}
			}
		}
	}
	cerr << "Erreur de rivière" << endl;
	return new rivers3D(M);
}

void parseur::sol (vector<member>& a) {
	T=new terrain3D(*M, *N);
	bool b(false);
	double d;
	if (a.size()>=2) {
		b=stringtodouble(a[1].val, d);
	}
	if (b==true) {
		T->initialise(Proprietes::nz*d);
	}
}

bool parseur::stringtoint (string const& a, int& i) {
	i=0;
	bool b(false);
	for (size_t j(0); j<a.size(); ++j) {
		if ((a[j]>='0') and (a[j]<='9')) {
			i=i*10+(a[j] - '0');
			b=true;
		}
	}
	return b;
}

bool parseur::stringtodouble (string const& s, double& d) {
	int p (s.find('.'));
	string a;
	string b;
	bool boo;
	if (p!=-1) {
		a=s.substr(0,p);
		b=s.substr(p+1, s.size()-p-1);
	}
	else {
		a=s;
	}
	int i;
	boo=stringtoint(a,i);
	if (b.size()!=0) {
		double e(0.0);
		int s(b.size()-1);
		for (int t(s); t>=0; t=t-1) {
			if ((b[t]>='0') and (b[t]<='9')) {
				e=e+(b[t] - '0');
				e=e/10.0;
			}
		}
		d=i+e;
	}
	else {
		d=i;
	}
	return boo;
}

bool parseur::getdouble (string s, double& a) {
	int moins(s.find('-'));
	int plus(s.find('+'));
	int fois(s.find('*'));
	int divi(s.find('/'));
	int puiss(s.find('^'));
	vector<vector<int>> bracket;
	brack(s, bracket);
	bool b(true);
	if (moins==-1 and plus==-1 and fois==-1 and divi==-1 and bracket.size()==0) {
		b=stringtodouble(s,a);
	}
	else if (moins!=-1 and parantheses(bracket, moins)==false) {
		if (moins!=0) {
			double c;
			b=getdouble('0'+s.substr(0,moins), c);
			if (b==true) {
				b=getdouble (s.substr(moins+1, s.size()-moins-1),a);
				a=c-a;
			}
		}
		else {
			b=getdouble (s.substr(1, s.size()-1), a);
			a=-a;
		}
	}
	else if (plus!=-1 and parantheses(bracket, plus)==false) {
		double c;
		b=getdouble(s.substr(0,plus), c);
		if (b==true) {
			b=getdouble (s.substr(plus+1, s.size()-plus-1),a);
			a=c+a;
		}
	}
	else if (fois!=-1 and parantheses(bracket, fois)==false) {
		double c;
		b=getdouble(s.substr(0,fois), c);
		if (b==true) {
			b=getdouble (s.substr(fois+1, s.size()-fois-1),a);
			a=c*a;
		}
	}
	else if (divi!=-1 and parantheses(bracket, fois)==false) {
		double c;
		b=getdouble(s.substr(0,moins), c);
		if (b==true) {
			b=getdouble (s.substr(moins+1, s.size()-moins-1),a);
			if(a!=0) {
				a=c/a;
			}
			else {
				b=false;
			}
		}
	}
	else if (puiss!=-1 and parantheses(bracket, puiss)==false){
		double c;
		b=getdouble(s.substr(0,puiss), c);
		if (b==true) {
			b=getdouble (s.substr(puiss+1, s.size()-puiss-1),a);
			a=pow(c,a);
		}
	}
	else {
		b=getdouble(s.substr(bracket[0][0]+1, bracket[0][1]-bracket[0][0]-1), a);
	}
	return b;
}

bool parseur::getint (string s, int& a) {
	int moins(s.find('-'));
	int plus(s.find('+'));
	int fois(s.find('*'));
	int divi(s.find('/'));
	bool b(true);
	if (moins==-1 and plus==-1 and fois==-1 and divi==-1) {
		b=stringtoint(s,a);
	}
	else if (moins<plus and moins<fois and moins<divi) {
		int c;
		b=stringtoint('0'+s.substr(0,moins),c);
		if (b==true) {
			b=getint (s.substr(moins+1, s.size()-moins-1),a);
			a=c-a;
		}
	}
	else if (plus<moins and plus<fois and plus<divi) {
		int c;
		b=stringtoint(s.substr(0,plus),c);
		if (b==true) {
			b=getint (s.substr(plus+1, s.size()-plus-1),a);
			a=c+a;
		}
	}
	else if (fois<moins and fois<plus and fois<divi) {
		int c;
		b=stringtoint(s.substr(0,fois),c);
		if (b==true) {
			b=getint (s.substr(fois+1, s.size()-fois-1),a);
			a=c*a;
		}
	}
	else {
		int c;
		b=stringtoint(s.substr(0,divi),c);
		if (b==true) {
			b=getint (s.substr(divi+1, s.size()-divi-1),a);
			if(a!=0) {
				a=c/a;
			}
			else {
				b=false;
			}
		}
	}
	return b;
}

bool parseur::getbool (string const& s, bool& a) {
	int t(s.find("true"));
	int f(s.find("false"));
	if(t!=-1) {
		a=true;
		return true;
	}
	else if (f!=-1) {
		a=false;
		return true;
	}
	else {
		return false;
	}
}

bool parseur::getnum (string& s, double& a) {
	int m(s.find('/'));
	if (m==-1) {
		return getdouble(s, a);
	}
	else {
		return getdouble(s.substr(0,m), a);
	}
}

bool parseur::getdenom (string& s, double& a) {
	int m(s.find('/'));
	if (m==-1) {
		a=1;
		return true;
	}
	else {
		return getdouble(s.substr(m+1, s.size()-m-1), a);
	}
}

bool parseur::getstring (string& s, string& a) {
	int d(s.find('"'));
	if (d==-1) {
		return false;
	}
	else {
		int f(s.substr(d+1, s.size()-2).find('"'));
		if (f==-1) {
			return false;
		 }
		string b("");
		if (d!=0) {
			b=s.substr(0, d);
		}
		int t(s.size());
		a=s.substr(d+1, f);
		if (f==t-1) {
			s=b;
		}
		else {
			s=b+s.substr(d+f+1, t-f-d-1);
		}
		return true;
	}
}

vector<vector<double>> parseur::divise (vector<double> v, int n) {
	vector<vector<double>> d;
	int c(v.size()%n);
	if (c!=0) {
		cerr << "Erreur d'écriture de fichier" << endl;
	}
	int j(0);
	vector<double> e;
	for (size_t i(0); i<v.size(); ++i) {
		e.push_back(v[i]);
		++j;
		if (j==n) {
			d.push_back(e);
			e.clear();
			j=0;
		}
	}
	return d;
}

vector<vector<int>> parseur::divise (vector<int> v, int n) {
	vector<vector<int>> d;
	int c(v.size()%n);
	if (c!=0) {
		cerr << "Erreur d'écriture de fichier" << endl;
	}
	int j(0);
	vector<int> e;
	for (size_t i(0); i<v.size(); ++i) {
		e.push_back(v[i]);
		++j;
		if (j==n) {
			d.push_back(e);
			e.clear();
			j=0;
		}
	}
	return d;
}

bool parseur::splitdouble (string s, vector<double>& arg) {
	int a(0);
	bool boo(true);
	bool b(false);
	bool c(false);
	bool d;
	do {
		d=false;
		int n(0);
		for (size_t i(0); i<s.size() and d==false; ++i) {
			if (b==false and (((s[i]>='0') and (s[i]<='9')) or s[i]=='-')) {
				b=true;
				++n;
			}
			else if (b==true and ((s[i]<'0') or (s[i]>'9')) and maths(s[i])==false) {
				b=false;
				arg.push_back(0);
				boo=getdouble(s.substr(0,i), arg[a]);
				++a;
				s=s.substr(i,s.size()-i);
				d=true;
			}
		}
		if (n==0) {
			c=true;
		}
		if (b==true) {
			arg.push_back(0);
			boo=stringtodouble(s, arg[a]);
		}
	} while (b==false and boo==true and c==false);
	return boo;
}

bool parseur::splitint (string s, vector<int>& arg) {
	int a(0);
	bool boo(true);
	bool b(false);
	bool c(false);
	bool d;
	do {
		d=false;
		int n(0);
		for (size_t i(0); i<s.size() and d==false; ++i) {
			if (b==false and (((s[i]>='0') and (s[i]<='9')) or s[i]=='-')) {
				b=true;
				++n;
			}
			else if (b==true and ((s[i]<'0') or (s[i]>'9')) and maths(s[i])==false) {
				b=false;
				arg.push_back(0);
				boo=stringtoint(s.substr(0,i), arg[a]);
				++a;
				s=s.substr(i,s.size()-i);
				d=true;
			}
		}
		if (n==0) {
			c=true;
		}
		if (b==true) {
			arg.push_back(0);
			boo=stringtoint(s, arg[a]);
		}
	} while (b==false and boo==true and c==false);
	return boo;
}

bool parseur::maths (char& a) {
	vector<char> c ({'-', '+', '^', '/', '*', '.', '(', ')'});
	for (int i(0); i<8; ++i) {
		if (a==c[i]) {
			return true;
		}
	}
	return false;
}

void parseur::brack (string s, vector<vector<int>>& b) {
	int a(-1);
	stack<char> c;
	for (size_t i(0); i<s.size(); ++i) {
		if (s[i]=='(') {
			c.push(i);
		}
		else if (s[i]==')') {
			b.push_back({c.top(), i});
			c.pop();
			++a;
		}
	}
	if (c.empty()==false) {
		cerr << "Erreur de paranthèses" << endl;
	}
}

bool parseur::parantheses (vector<vector<int>> const& b, int const& a) {
	bool c(false);
	for(size_t i(0); i<b.size() and c==false; ++i) {
		if (a>b[i][0] and a<b[i][1]) {
			c=true;
		}
	}
	return c;
}

Systeme3D* parseur::sys () {
	return S;
}
