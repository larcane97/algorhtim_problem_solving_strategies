#include <iostream>
#include <vector>

using namespace std;
double cache[51][101];
int arr[51][51], deg[51];
int n, d, p, q;


// ¿ÏÀüÅ½»ö
double search(vector<int>& path) {
	if (path.size() == d + 1) {
		if (path.back() != q) return 0.0;

		double ret = 1.0;
		for (int i = 0; i + 1 < path.size(); i++) {
			ret /= deg[path[i]];
		}
		return ret;
	}
	double ret = 0;
	for (int there = 0; there < n; there++) {
		if (arr[path.back()][there]) {
			path.push_back(there);
			ret += search(path);
			path.pop_back();
		}
	}
	return ret;
}


// µ¿Àû°èÈ¹¹ı
double search2(int here, int days) {
	if (days == d) return (here == q ? 1.0 : 0.0);
	double& ret = cache[here][days];
	if (ret != -0.5) return ret;
	ret = 0.0;
	for (int i = 0; i < n; i++) {
		if (arr[here][i])
			ret += search2(i, days + 1) / deg[here];
	}
	
	return ret;

}

double search3(int here, int days) {
	if (days == 0) return (here == q ? 1.0 : 0.0);
	double& ret = cache[here][days];
	if (ret > -0.5) return ret;
	ret = 0.0;
	for (int there = 0; there < n; there++) {
		if (arr[here][there]) {
			ret += search3(there, days - 1) / deg[there];
		}
	}
	return ret;
}

int main() {
	int c;
	cin >> c;
	for (int i = 0; i < c; i++) {
		memset(cache, -1, sizeof(cache));
		memset(arr, 0, sizeof(arr));
		memset(deg, 0, sizeof(deg));
		cin >> n >> d >> p;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				cin >> arr[i][j];
				if (arr[i][j])
					deg[i]++;
			}
		int t;
		cin >> t;
		for (int j = 0; j < t; j++) {
			cin >> q;

			cout << search3(q,d) << endl;
		}


	}
}