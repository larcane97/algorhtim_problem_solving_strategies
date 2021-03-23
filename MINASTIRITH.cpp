#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
const double pi = 2.0 * acos(0);
double x[100], y[100], r[100];
pair<double, double> ranges[100];

void convertToRange() {
	for (int i = 0; i < n; i++) {
		double loc = fmod(2 * pi + atan2(x[i], y[i]), 2 * pi);
		double range = 2.0 * asin(r[i] / 16.0);
		ranges[i] = make_pair(loc - range, loc + range);
	}
	sort(ranges, ranges + n);
}

const int INF = 987654321;

int solveLinear(int begin, int end) {
	int used = 0, idx = 0;
	while (begin < end) {
		double maxCover = -1;
		while (idx < n && ranges[idx].first <= begin) {
			maxCover = max(maxCover, ranges[idx].second);
			idx++;
		}
		if (maxCover <= begin) return INF;
		begin = maxCover;
		used++;
	}
	return used;
}

int solveCircular() {
	int ret = INF;
	sort(ranges, ranges + n);
	for (int i = 0; i < n; i++) {
		if (ranges[i].first <= 0 || ranges[i].second >= 2 * pi) {
			double begin = fmod(ranges[i].second, 2 * pi);
			double end = fmod(ranges[i].first + 2 * pi, 2 * pi);
			ret = min(ret, 1 + solveLinear(begin, end));
		}
	}
	return ret;
}

int main() {
	int c;
	cin >> c;
	for (int i = 0; i < c; i++) {
		cin >> n;
		for (int j = 0; j < n; j++) {
			cin >> x[j] >> y[j] >> r[j];
		}
		convertToRange();
		cout << solveCircular() << endl;

	}
}