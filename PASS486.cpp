#include <iostream>
#include <vector>

using namespace std;

const int TM = 10 * 1000 * 1000;

int factors[TM + 1];
const int MAX = 10 * 1000 * 1000;
void getFactorsBrute() {
	memset(factors, 0, sizeof(factors));
	for (int div = 1; div <= MAX; div++) {
		for (int multiple = div; multiple <= TM; multiple += div)
			factors[multiple]++;
	}
}
int n;

int CountFactor(int lo, int hi) {
	int ret = 0;
	for (int i = lo; i <= hi; i++) {
		if (factors[i] == n) ret++;
	}
	return ret;
}

int main() {
	getFactorsBrute();
	int c;
	cin >> c;
	for (int iter = 0; iter < c; iter++) {
		int hi, lo;
		cin >> n >> lo >> hi;
		cout << CountFactor(lo, hi) << endl;
	}
}