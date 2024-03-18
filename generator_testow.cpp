// tworzy losowa testy
// na wejsciu dostaje {liczbe_punktow_do_wypisania} {minimalny_zakres_liczb} {maxymalny_zakres_liczb}
#include <bits/stdc++.h>
using namespace std;

random_device rd;
mt19937 mt(rd());

double daj_rand_od_zera_do_jeden(){
	return (double)mt() / mt.max();
}

double liczba_z_zakresu(int mniejsza_liczba, int wieksza_liczba){
	return mniejsza_liczba + daj_rand_od_zera_do_jeden() *
	       (wieksza_liczba - mniejsza_liczba);
}

int main(){
	int n = 10;
	double mniejsza_liczba = -5;
	double wieksza_liczba = 5;
	cin >> n >> mniejsza_liczba >> wieksza_liczba;
	cout << n << endl;
	for (int i = 0;i < n;i++){
		double wartos_x = liczba_z_zakresu(mniejsza_liczba,wieksza_liczba);
		double wartos_y = liczba_z_zakresu(mniejsza_liczba,wieksza_liczba);
		cout << wartos_x << " " << wartos_y << endl;
	}
	

return 0;
}
