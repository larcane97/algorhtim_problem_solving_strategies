#include <iostream>
#include <vector>

using namespace std;

double n, m, r;

long long L = 2000000000;

int ratio(long long b, long long a) {
	return (a * 100) / b;
}

int neededGames(long long games, long long won) {
	if (ratio(games, won) == ratio(games + L, won + L)) return -1;
	long long lo = 0, hi = L;
	while (lo + 1 < hi) {
		long long mid = (lo + hi) / 2;
		if (ratio(games, won) == ratio(games + mid, won + mid))
			lo = mid;
		else
			hi = mid;
	}
	return hi;
}

//
//int game() {
//	double lo = 0, hi = n;
//	double candR, mid;
//	for (int iter = 0; iter < 100; iter++) {
//		mid = (lo + hi) / 2.0;
//		candR = (mid +m) / (mid+n) * 100.0;
//		if (candR > r + 1)
//			hi = mid;
//		else
//			lo = mid;
//	}
//	if (hi==n)
//		return -1;
//	else return (int)ceil(mid);
//}

int main() {
	int c;
	cin >> c;
	for (int i = 0; i<c; i++) {
		cin >> n >> m;
		r = (m/n) * 100.0;
		cout << neededGames(n,m) << endl;
	}
}