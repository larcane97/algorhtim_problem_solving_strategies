#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1000000007;
int cache[101];

int tiling(int n) {
	if (n <= 1) return 1;
	int& ret = cache[n];
	if (ret != -1) return ret;

	return ret = (tiling(n - 1) + tiling(n - 2)) % MOD;

}

int asyTiling(int n) {
	if (n % 2 == 1)
		return (tiling(n) - tiling(n / 2) + MOD) % MOD;
	
	int ret = tiling(n);
	ret = (ret - tiling(n / 2) + MOD) % MOD;
	ret = (ret - tiling(n / 2 - 1) + MOD) % MOD;
	return ret;
}

int cache2[101];
int asyTiling2(int n) {
	if (n <= 2) return 0;
	int& ret = cache2[n];
	if (ret != -1) return ret;
	ret = asyTiling2(n - 2) % MOD;
	ret = (ret + asyTiling2(n - 4)) % MOD;
	ret = (ret + tiling(n - 3)) % MOD;
	ret = (ret + tiling(n - 3)) % MOD;
	return ret;

}

int tilingCompleteSearch(int n) {
	if (n <= 1) return 1;
	return (tilingCompleteSearch(n - 1) + tilingCompleteSearch(n - 2)) % MOD;
}


int main() {
	int c;
	cin >> c;
	for (int i = 0 ; i < c; i++) {
		memset(cache, -1, sizeof(cache));
		memset(cache2, -1, sizeof(cache2));
		int n;
		cin >> n;
		cout << asyTiling(n) << endl;
		cout << asyTiling2(n) << endl;
		//cout << tilingCompleteSearch(n) << endl;
		
	}
}