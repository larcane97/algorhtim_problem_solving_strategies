#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int r[1000], c[1000];
int n,k;

bool decision(double average) {
	vector<double>v;
	for (int i = 0; i < n; i++)
		v.push_back(average * c[i] - r[i]);
	sort(v.begin(), v.end());
	double sum = 0;
	for (int i = n - k; i < n; i++)
		sum += v[i];
	return sum >= 0;
}

double optimize() {
	double lo = -1e9, hi = 1;
	for (int it = 0; it < 100; it++) {
		double mid = (lo + hi) / 2;
		if (decision(mid))
			hi = mid;
		else
			lo = mid;
	}
	return hi;
}





int main() {
	int T;
	cin >> T;
	for (int it = 0; it < T; it++) {
		memset(r, 0, sizeof(r));
		memset(c, 0, sizeof(c));
		cin >> n >> k;
		for (int i = 0; i < n; i++)
			cin >> r[i] >> c[i];
		cout << optimize()<<endl;
	}

}