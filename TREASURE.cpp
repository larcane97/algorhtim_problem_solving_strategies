#include <iostream>
#include <vector>
#include "vector2.h"
#include <cassert>

using namespace std;

typedef vector<vector2> polygon;

const double EPSILON = 1e-9;

bool lineIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& x) {
	double det = (b - a).cross(d - c);
	if (fabs(det) < EPSILON) return false;

	x = a + (b - a) * ((c - a).cross(d - c) / det);
	return true;


}

polygon cutPoly(const polygon& p, const vector2& a, const vector2& b) {
	int n = p.size();
	vector<bool> inside(n);

	for (int i = 0; i < n; i++)
		inside[i] = ccw(a, b, p[i]) >= 0;

	polygon ret;

	for (int i = 0; i < n; i++) {
		int j = (i + 1) % n;

		if (inside[i]) ret.push_back(p[i]);

		if (inside[i] != inside[j]) {
			vector2 cross;
			assert(lineIntersection(p[i], p[j], a, b, cross));
			ret.push_back(cross);
		}
	}
	return ret;
}


double calcArea(polygon p) {
	int n = p.size();
	double ret = 0;
	for (int i = 0; i < n; i++) {
		int j = (i + 1) % n;
		ret += p[i].x * p[j].y - p[j].x * p[i].y;
	}
	return fabs(ret) / 2.0;
}


void intersection(const polygon& p, double x1, double y1, double x2, double y2) {
	vector2 a(x1, y1), b(x2, y1), c(x2, y2), d(x1, y2);
	polygon ret = cutPoly(p, a, b);
	ret = cutPoly(ret, b, c);
	ret = cutPoly(ret, c, d);
	cout << calcArea(ret) << endl;
	ret = cutPoly(ret, d, a);
	cout << calcArea(ret) << endl;
}


int main() {
	int c;
	cin >> c;
	for (int iter = 0; iter < c; iter++) {
		int n;
		double x1, x2, y1, y2;
		cin >> x1 >> y1 >> x2 >> y2 >> n;
		polygon p;
		for (int i = 0; i < n; i++) {
			double x, y;
			cin >> x >> y;
			p.push_back(vector2(x, y));
		}
		intersection(p, x1, y1, x2, y2);
	
	}
}