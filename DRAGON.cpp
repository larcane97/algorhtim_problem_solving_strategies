#include <iostream>
#include <vector>
#include <string>
#include <cassert>
using namespace std;

int p,l;

string cache[51];

string dragon(int n) {
	string& ret = cache[n];
	if (ret != "") return ret;
	if (n == 0) return ret = "FX";
	string s = dragon(n - 1);
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == 'X' || s[i] == 'Y') {
			if (s[i] == 'X') ret += "X+YF";

			if (s[i] == 'Y') ret += "FX-Y";
		}
		else
			ret += s[i];
	}
	return ret;
}

// solution

void curve(const string& seed, int generations) {
	if (generations == 0) {
		cout << seed;
		return;
	}
	for (int i = 0; i < seed.size(); i++) {
		if (seed[i] == 'X')
			curve("X+YF", generations - 1);
		else if (seed[i] == 'Y')
			curve("FX-Y", generations - 1);
		else
			cout << seed[i];
	}
}

const int MAX = 1000000000 + 1;
int length[51];

void precalc() {
	length[0] = 1;
	for (int i = 1; i <= 50; i++) {
		length[i] = min(MAX, length[i - 1] * 2 + 2);
	}
}

const string EXPAND_X = "X+YF";
const string EXPAND_Y = "FX-Y";

char expand(const string& dragonCurve, int generations, int skip) {
	if (generations == 0) {
		assert(skip < dragonCurve.size());
		return dragonCurve[skip];
	}
	for (int i = 0; i < dragonCurve.size(); i++) {
		if (dragonCurve[i] == 'X' || dragonCurve[i] == 'Y') {
			if (skip >= length[generations])
				skip -= length[generations];
			else if (dragonCurve[i] == 'X')
				return expand(EXPAND_X, generations - 1, skip);
			else
				return expand(EXPAND_Y, generations - 1, skip);
		}
		else if (skip > 0)
			--skip;
		else
			return dragonCurve[i];
	}
}






int main() {
	//int c;
	//cin >> c;
	//for (int i = 0; i < c; i++) {
	//	cache->clear();
	//	int n;
	//	cin >> n >> p >> l;
	//	string s = dragon(n);
	//	for (int i = p-1; i < p-1 + l; i++) {
	//		cout << s[i];
	//	}
	//	cout << endl;

	//}

	string seed = "FX";
	curve(seed, 2);
	
	
	
}