// kod na drugi etap rekrutacji pwr racing team napisznay przez Piotra S
#include <bits/stdc++.h>
using namespace std;

struct Punkt{

	long double x,y; // polozenie punktu

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


// zwraca punkt ktory jest srodkiem (srednia wszystkich punktow)
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

// oblicza odległosc z wzoru pitagorasa
long double kwadrat_odlegosc(const Punkt pierwszy, const Punkt drugi){
	return (pierwszy.x - drugi.x)*(pierwszy.x - drugi.x)+
		   (pierwszy.y - drugi.y)*(pierwszy.y - drugi.y);
}


// zwraca punkt ktory jest najbardziej oddalony od srodka
Punkt znajdz_najdalszy_od_srodka(const vector<Punkt>& punkty, const Punkt& srodek){
	long double maxymalna_odleglosc = 0;
	long double aktualna_odleglosc = 0;
	long long index_najdalszego_punktu;
	for (long long i = 0;i < punkty.size();i++){
		aktualna_odleglosc = kwadrat_odlegosc(punkty[i],srodek);
		if (aktualna_odleglosc > maxymalna_odleglosc){
			maxymalna_odleglosc = aktualna_odleglosc;
			index_najdalszego_punktu = i;
		}
	}
	return punkty[index_najdalszego_punktu];
}

// poruwnuje odlegloszci dwuch punktow wzgledem poczatku i zwraca true kiedy pierwszy punkt jest blizej
bool blizszy_punkt(const Punkt startowy, const Punkt pierwszy, const Punkt drugi){
	if (kwadrat_odlegosc(startowy,pierwszy)<
		kwadrat_odlegosc(startowy,drugi)){
		return true;
	}
	return false;
}

// szuka pierwszego punktu ktory jest na lewo od punktu startowego (od wektra skierowanego przeciwnie do srodka)
Punkt znajdz_nastepny_punkt(const vector<Punkt>& punkty, const Punkt& srodek, const Punkt& startowy){
	long double kat_do_srodka = atan2(startowy.y - srodek.y, startowy.x - srodek.x);//(srodek.y - startowy.y,srodek.x - startowy.x);
	long double aktualny_kat = 0;
	long double nowy_kat = 0;
	long double najmniejszy_kat = 10;
	long long index_punkt_odpowiedzi;
	for (long long i = 0;i < punkty.size();i++){
		if (punkty[i].x == startowy.x && punkty[i].y == startowy.y){ // sprawdzam czy punkt ktorego szukam jest inny od starowego
			continue;
		}
		// licze kat i sprwiam ze jest wiekszy od katu srodek
		aktualny_kat = atan2(punkty[i].y - startowy.y, punkty[i].x - startowy.x);
		if (aktualny_kat <= kat_do_srodka){
			aktualny_kat += M_PI * 2;
		}
		// tworze kat ktory wzgledem kata srodka jet w zakresie (0,2*pi]
		nowy_kat = aktualny_kat - kat_do_srodka;
		if (nowy_kat == najmniejszy_kat){
			// sprawdzam przypadek kiedy dwa punkt sa w lini (wtedy biore punkt blirzej startowego)
			if (blizszy_punkt(startowy, punkty[i], punkty[index_punkt_odpowiedzi])){
				index_punkt_odpowiedzi = i;
			}
		}
		// sprawdzam czy nowy kat jest najmniejszy jak tak to go wybiertam jako potencalna odpowiedz
		if (nowy_kat < najmniejszy_kat){
			najmniejszy_kat = nowy_kat;
			index_punkt_odpowiedzi = i;
		}
	}
	return punkty[index_punkt_odpowiedzi];
}

// szuka najbardziej lewych punktow ktore beda odpowiedza
vector <Punkt> znajdz_zewnetrzne_elementy(const vector<Punkt>& punkty, const Punkt& srodek, const Punkt& najdalszy){
	vector<Punkt> odpowiedz;
	odpowiedz.push_back(najdalszy);
	Punkt nastepny_punkt;
	do{
		nastepny_punkt = znajdz_nastepny_punkt(punkty, srodek, odpowiedz[odpowiedz.size()-1]);
		odpowiedz.push_back(nastepny_punkt);
	}while(nastepny_punkt != najdalszy);
	odpowiedz.pop_back();
	return odpowiedz;
}

// wypisawanie w taki sposub jak zadanie oczekuje a dla latwiejszego testowane mozna posortowac by wyniki były jednakowe
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

int main(){
	long long n;
	cin >> n;
	vector<Punkt> punkty(n);
	for (long long i = 0;i < n;i++){
		cin >> punkty[i].x >> punkty[i].y;
	}
	if (n <= 3){
		wypisz(punkty);
	}
	Punkt srodek = policz_srodek(punkty);
	Punkt najdalszy = znajdz_najdalszy_od_srodka(punkty,srodek);
	wypisz(znajdz_zewnetrzne_elementy(punkty,srodek,najdalszy));

return 0;
}
