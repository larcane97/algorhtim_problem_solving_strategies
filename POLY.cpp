#include <iostream>
#include <vector>

using namespace std;

const int MOD = 10 * 1000 * 1000;
int cache[101][101];

int poly(int n, int first) {
	if (n == first) return 1;

	int& ret = cache[n][first];
	if (ret != -1) return ret;
	ret = 0;
	for (int second = 1; second <= n-first; second++) {
		int add = first + second - 1;
		add *= poly(n - first, second);
		add %= MOD;
		ret += add;
		ret %= MOD;
	}
	return ret;
}

int main() {
	int c;
	cin >> c;
	for (int i = 0; i < c; i++) {
		int n;
		memset(cache, -1, sizeof(cache));
		cin >> n;
		int ret = 0;
		for (int i = 1; i <= n; i++)
			ret += poly(n, i);
		cout << ret%MOD << endl;
	}
}