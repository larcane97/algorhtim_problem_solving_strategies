#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int price[20];
int favor[20];
int cache[10000000];
int n;
int sushi(int m) {
	if (m < 0) return 0;
	int& ret = cache[m];
	if (ret != -1) return ret;
	ret = 0;
	for (int i = 0; i < n; i++) {
		if(m-price[i] >=0)
			ret = max(ret, sushi(m - price[i]) + favor[i]);
	}
	return ret;
}

#define MAX_BUDGET 1000000000
int c[20000 + 1];

int sushi2(int m) {
	int ret = 0;
	for (int budget = 1; budget <= m; budget++) {
		c[budget%20001] = 0;
		for (int dish = 0; dish < n; dish++) {
			if (budget >= price[dish])
				c[budget%20001] = max(
					c[budget%20001], c[(budget - price[dish])%20001] + favor[dish]
				);
		}
		ret = max(ret, c[budget%20001]);
	}
	return ret;
}

int c2[201];

int sushi3(int m) {
	int ret = 0;
	c2[0] = 0;
	for (int budget = 1; budget <= m; budget++) {
		int cand = 0;
		for (int dish = 0; dish < n; dish++) {
			if (budget >= price[dish]) {
				cand = max(cand,
					c[(budget-price[dish])%201] + favor[dish]);
			}
		}
		c[budget % 201] = cand;
		ret = max(ret, cand);
	}
	return ret;
}


int main() {
	int c;
	cin >> c;
	for (int i = 0; i < c; i++) {
		memset(cache, -1, sizeof(cache));
		memset(favor, 0, sizeof(favor));
		memset(price, 0, sizeof(price));
		int  m;
		cin >> n >> m;
		for (int j = 0; j < n; j++) {
			cin >> price[j] >> favor[j];
		}
		cout << sushi(m) << endl;
	}
}