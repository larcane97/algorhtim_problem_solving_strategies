#include <iostream>
#include <vector>

using namespace std;


int n,r[1000], p[1000];
int tmpR[1000];
int ans[1000];

int gcd(int p, int q) {
	if (q == 0) return p;
	return gcd(q, p % q);
}

int totalgcd() {
	int p = r[0];
	for (int i = 1; i < n; i++)
		p = gcd(p, r[i]);
	return p;
}

bool check() {
	bool chk = true;
	for (int i = 0; i < n; i++)
		if (p[i] > ans[i]) {
			chk = false;
			break;
		}
	return chk;
}

void makeTmpR() {
	int a = totalgcd();
	for (int i = 0; i < n; i++)
		tmpR[i] = r[i] / a;
}

void print() {
	makeTmpR();
	int count = 1;
	while (true) {
		for (int i = 0; i < n; i++)
			ans[i] = count * tmpR[i];
		count++;
		if (check()) break;
	}
	for (int i = 0; i < n; i++)
		cout << ans[i]-p[i] << " ";
	cout << endl;
}



int main() {
	int c;
	cin >> c;
	for (int iter = 0; iter < c; iter++) {
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> r[i];
	
		for (int i = 0; i < n; i++)
			cin >> p[i];

		print();
		

	}
}