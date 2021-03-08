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


int main() {
	int n;
	cin >> n;
	memset(cache, -1, sizeof(cache));
	cout << tiling(n) << endl;

}