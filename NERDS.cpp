#include <iostream>
#include <vector>
#include "vector2.h"
#include <algorithm>

using namespace std;



polygon giftWrap(const vector<vector2>& points) {
	int n = points.size();
	polygon hull;

	vector2 pivot = *min_element(points.begin(), points.end());
	hull.push_back(pivot);
	while (true) {
		vector2 ph = hull.back(), next = points[0];
		for (int i = 1; i < n; i++) {
			double cross = ccw(ph, next, points[i]);
			double dist = (next-ph).norm() - (points[i]-ph).norm();

			if (cross > 0 || (cross == 0 && dist < 0))
				next = points[i];
		}
		if (next == pivot) break;
		hull.push_back(next);
	}
	return hull;
}

bool poygonIntersects(const polygon& p, const polygon& q) {
	int n = p.size(), m = q.size();

	if (isInside(p[0], q) || isInside(q[0], p)) return true;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (segmentIntersects(p[i], p[(i + 1) % n], q[j], q[(j + 1) % m]))
				return true;

	return false;
}

int main() {
	int c;
	cin >> c;
	for (int iter = 0; iter < c; iter++) {
		vector<vector2> nerd;
		vector<vector2> notNerd;
		int n;
		cin >> n;
		for (int i = 0; i < n; i++) {
			int isNerd;
			double x, y;
			cin >> isNerd >> x >> y;
			if (isNerd)
				nerd.push_back(vector2(x, y));
			else
				notNerd.push_back(vector2(x, y));
		}
		polygon p = giftWrap(nerd);
		polygon q = giftWrap(notNerd);
		if (poygonIntersects(p, q))
			cout << "THEORY IS INVAILD" << endl;
		else
			cout << "THEORY HOLDS" << endl;
	}
}

