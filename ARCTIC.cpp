#include <iostream>
#include <vector>
#include <queue>


using namespace std;


int n;
double dist[101][101];

bool decision(double d) {
	vector<bool> visited(n, false);
	visited[0] = true;
	queue<int>q;
	q.push(0);
	int seen = 0;
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		seen++;
		for(int there=0;there<n;there++)
			if (!visited[there] && dist[here][there] <= d) {
				visited[there] = true;
				q.push(there);
			}
	}
	return seen == n;
}

double optimize() {
	double lo = 0, hi = 1416.00;
	for (int it = 0; it < 100; it++) {
		double mid = (lo + hi) / 2;
		if (decision(mid))
			hi = mid;
		else
			lo = mid;
	}
	return lo;
}


int main() {
	int c;
	cin >> c;

	for (int i = 0; i < c; i++) {
		cin >> n;
		vector<pair<double, double>>a;
		for (int j = 0; j < n; j++) {
			double x, y;
			cin >> x >> y;
			a.push_back(make_pair(x, y));
		}
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				if (j == k) dist[j][k] = 0;
				else {
					dist[j][k] = sqrt(pow((a[j].first - a[k].first), 2) + pow((a[j].second - a[k].second), 2));
				}
			}
		}
		cout << optimize() << endl;

	}
}