#include <bits/stdc++.h>
using namespace std;

struct Punkt{

	long double x,y;

	bool operator== (const Punkt& inny) const{
		return x == inny.x && y == inny.y;
	}

	bool operator!= (const Punkt& inny) const{
		return !((Punkt){x,y} == inny);
	}

	bool operator< (const Punkt& inny) const{\
		if (x < inny.x){
			return true;
		}
		else if (x == inny.x){
			return y < inny.y;
		}
		else{
			return false;
		}
	}
};

void wypisz(vector <Punkt> punkty){
	#ifdef SORTOWANIE
		sort(punkty.begin(),punkty.end());
	#endif
	printf("[(%.1Lf,%.1Lf)",punkty[0].x,punkty[0].y);
	for (int i = 1;i < punkty.size();i++){
		printf(", (%.1Lf,%.1Lf)",punkty[i].x,punkty[i].y);	
	}
	printf("]\n");
}

Punkt policz_srodek(const vector<Punkt>& punkty){
	Punkt srodek = {0,0};
	for (long long i = 0;i < punkty.size();i++){
		srodek.x += punkty[i].x;
		srodek.y += punkty[i].y;
	}
	srodek.x /= punkty.size();
	srodek.y /= punkty.size();
	return srodek;
}

vector <Punkt> posortuj_katowo_wzdledem_srodka(vector <Punkt>& punkty){
	Punkt srodek = policz_srodek(punkty);
	vector<pair<long double,Punkt>> kat_i_punkt; 
	for (int i = 0;i < punkty.size();i++){
		kat_i_punkt.push_back({atan2(punkty[i].y - srodek.y, punkty[i].x - srodek.x)+M_PI,punkty[i]});		
	}
	sort(kat_i_punkt.begin(),kat_i_punkt.end());
	for (int i = 0;i < punkty.size();i++){
		punkty[i] = kat_i_punkt[i].second;
	}
	return punkty;
}

bool czy_punkt_nie_jest_w_wektorze(vector <Punkt> punkty, Punkt do_sprawdzenia){
	for (int i = 0;i < punkty.size();i++){
		if (punkty[i] == do_sprawdzenia){
			return false;
		}
	}
	return true;
}

bool czy_punkt_nie_jest_w_wielokacie(vector <Punkt> punkty, Punkt do_sprawdzenia){
	double odpowiedz = 0;
	//cout << "do_sprawdzenia = " << do_sprawdzenia.x << "," << do_sprawdzenia.y << endl;
	for (int i = 0;i < punkty.size();i++){
		Punkt jeden = punkty[i];
		Punkt dwa   = punkty[(i + 1) % punkty.size()];
		long double strona = (do_sprawdzenia.x - jeden.x)*(dwa.y - jeden.y) - 
							 (do_sprawdzenia.y - jeden.y)*(dwa.x - jeden.x);
							 //cout << "strona: " << strona << " x: " << jeden.x << "," << jeden.y << " y: " << dwa.x << "," << dwa.y << endl;
		if (strona == 0){
			return true;
		}
		if (odpowiedz == 0){
			if (strona > 0){
				odpowiedz = 1;
			}
			else{
				odpowiedz = -1;
			}
		}
		else{
			if (odpowiedz < 0 && strona > 0){
				return true;
			}
			if (odpowiedz > 0 && strona < 0){
				return true;
			}
		}
	}
	return false;
}

bool sprawdz_czy_wszystkie_sa_w_srodku(vector <Punkt> kandydaci_do_odpowiedzi, vector <Punkt> punkty){
	if (kandydaci_do_odpowiedzi.size() <= 2){
		return false;
	}
	for (int i = 0;i < punkty.size();i++){
		if (czy_punkt_nie_jest_w_wektorze(kandydaci_do_odpowiedzi,punkty[i])){
			if (czy_punkt_nie_jest_w_wielokacie(kandydaci_do_odpowiedzi,punkty[i])){
				return false;
			}
		}
	}
	return true;
}

int main(){
	int n;
	cin >> n;
	vector<Punkt> punkty(n);
	vector<Punkt> odpowiedz(n+2);
	vector<Punkt> kandydaci_do_odpowiedzi;
	for (int i = 0; i < n;i++){
		cin >> punkty[i].x >> punkty[i].y;
	}
	if (n <= 3){
		wypisz(punkty);
	}
	posortuj_katowo_wzdledem_srodka(punkty);
	int ilosc_przypadkow = (1 << n);
	for (int numer = 1;numer < ilosc_przypadkow;numer++){
		for (int bit = 0;bit < 21;bit++){
			if(numer & (1 << bit)){
				kandydaci_do_odpowiedzi.push_back(punkty[bit]);
			}
		}
		if (sprawdz_czy_wszystkie_sa_w_srodku(kandydaci_do_odpowiedzi,punkty)){
			if (kandydaci_do_odpowiedzi.size() < odpowiedz.size()){
				odpowiedz = kandydaci_do_odpowiedzi;
			}
		}
		kandydaci_do_odpowiedzi.clear();
	}
	wypisz(odpowiedz);

return 0;
}
