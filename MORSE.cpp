#include <iostream>
#include <vector>
#include <string>
using namespace std;

int n, m;
int skip;
void generate(int n, int m, string s) {
	if (skip < 0) return;
	if (n == 0 && m == 0) {
		if(skip==0) cout << s << endl;
		skip--;
		return;
	}
	if (n > 0) generate(n - 1, m, s + "-");
	if (m > 0) generate(n, m - 1, s + "o");

}

const int M = 1000000000 + 100;
int bino[201][201];

void calcBino() {
	memset(bino, 0, sizeof(bino));
	for (int i = 0; i <= 200; i++) {
		bino[i][0] = bino[i][i] = 1;
		for (int j = 1; j < i; j++) {
			bino[i][j] = min(M, bino[i - 1][j] + bino[i-1][j-1]);
		}
	}
}

void generate3(int n, int m, string s) {
	if (skip < 0) return;
	if (n == 0 && m == 0) {
		if (skip == 0) cout << s << endl;
		skip--;
		return;
	}
	if (bino[n + m][n] < skip) {
		skip -= bino[n + m][n];
		return;
	}
	if (n > 0) generate3(n - 1, m, s + "-");
	if (m > 0) generate3(n, m - 1, s + "o");
}

string kth(int n, int m, int skip) {
	if (n == 0) return string(m, 'o');
	if (skip < bino[n + m - 1][n - 1]) {
		return "-" + kth(n - 1, m, skip);
	}
	return "o" + kth(n, m - 1, skip - bino[n + m - 1][n - 1]);
}


int main() {	
	int k;
	cin >> n >> m;
	cin >> k;
	skip = k - 1;
	string s = "";
	calcBino();
	generate3(n, m, s);
	cout << kth(n, m, k-1) << endl;
}