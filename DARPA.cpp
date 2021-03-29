#include <iostream>
#include <vector>
using namespace std;

bool decision(const vector<double>& location, int cameras, double gap) {
	double limit = -1;
	int installed = 0;
	for (int i = 0; i < location.size(); i++) {
		if (limit <= location[i]) {
			installed++;
			limit = location[i] + gap;
		}
	}
	return installed >= cameras;
}

double optimize(const vector<double>& location, int cameras) {
	double lo = 0, hi = 241;
	for (int it = 0; it < 100; it++) {
		double mid = (lo + hi) / 2.0;

		if (decision(location, cameras, mid))
			lo = mid;
		else
			hi = mid;
	}
	return lo;
}
