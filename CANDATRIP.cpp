#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
int n, k;
vector<pair<int, pair<int, int>>>arr;
int check[8030000];


int f() {
	sort(arr.begin(), arr.end());
	int count = 0;
	for (int i = 0; i < n; i++) {
		int last = arr[i].first;
		int current = last - arr[i].second.first;
		int d = arr[i].second.second;
		while (current<=last) {
			check[current]++;
			current += d;
		}
	}
	int a = 0;
	int i;
	for (i = 0; i <= arr[arr.size() - 1].first; i++) {
		a += check[i];
		if (a >= k) {
			break;
		}
	}
	return i;
}

int main() {
	int T;
	cin >> T;
	for (int it = 0; it < T; it++) {
		cin >> n >> k;
		for (int i = 0; i < n; i++) {
			int L, M, G;
			cin >> L >> M >> G;
			arr.push_back(make_pair(L, make_pair(M, G)));
		}
		cout << f() << endl;
		arr.clear();
	}
}
*/


int n, k;
int l[5000], m[5000], g[5000];

bool decision(int dist) {
	int ret = 0;
	for (int i = 0; i < n; i++)
		if (dist >= l[i] - m[i])
			ret += (min(dist, l[i]) - (l[i] - m[i])) / g[i] + 1;
	return ret >= k;
}

int optimize() {
	int lo = -1, hi = 8030001;
	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;
		if (decision(mid))
			hi = mid;
		else
			lo = mid;
	}
	return hi;
}