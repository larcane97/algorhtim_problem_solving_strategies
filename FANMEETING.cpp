#include <iostream>
#include <vector>
#include <string>

using namespace std;

void normalize(vector<int>& a) {
	a.push_back(0);
	for (int i = 0; i+1 < a.size(); i++) {
		if (a[i] < 0) {
			int borrow = (abs(a[i]) + 9) / 10;
			a[i + 1] -= borrow;
			a[i] += borrow * 10;
		}
		else {
			a[i + 1] += (a[i] / 10);
			a[i] %= 10;
		}
	}
	while (a.size() > 1 && a.back() == 0) a.pop_back();
}


vector<int> multiply(const vector<int>& a, const vector<int>& b) {
	vector<int>c(a.size() + b.size() + 1, 0);
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < b.size(); j++) {
			c[i + j] += a[i] * b[j];
		}
	}
	//normalize(c);
	return c;
}

void addTo(vector<int>& a, const vector<int>& b, int k) {
	int t = min<int>(a.size(), b.size());
	for (int i = 0; i < k; i++)
		a.push_back(0);
	for (int i = 0; i < t; i++) {
		a[k + i] = b[i];
	}
	//normalize(a);
	return;
}
void subFrom(vector<int>& a, const vector<int>& b) {
	int t = min<int>(a.size(), b.size());
	for (int i = 0; i < t; i++) {
		a[i] -= b[i];
	}
	//normalize(a);
}

vector<int> karatsuba(const vector<int>& a, const vector<int>& b) {
	int an = a.size(), bn = b.size();
	if (an < bn) return karatsuba(b, a);
	if (an == 0 || bn == 0) return vector<int>();
	if (an <= 50) return multiply(a, b);

	int half = an / 2;
	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> a1(a.begin() + half, a.end());
	vector<int> b0(b.begin(), b.begin() + min<int>(bn,half));
	vector<int> b1(b.begin() + min<int>(bn, half) , b.end());

	vector<int>z2 = karatsuba(a1, b1);
	vector<int>z0 = karatsuba(a0, b0);

	addTo(a0, a1, 0); addTo(b0, b1, 0);

	vector<int>z1 = karatsuba(a0, b0);
	subFrom(z1, z0);
	subFrom(z1, z2);
	vector<int> ret(an + bn);

	addTo(ret, z0, 0);
	addTo(ret, z1, half);
	addTo(ret, z2, half + half);
	return ret;

}


int hugs(const string& member, const string& fen) {
	int N = member.size(), M = fen.size();
	vector<int>A(N), B(M);
	for (int i = 0; i < N; i++) A[i] = (member[i] == 'M' ? 1 : 0);
	for (int i = 0; i < M; i++) B[M-i-1] = (fen[i] == 'M' ? 1 : 0);
	
	vector<int> C = karatsuba(A, B);
	int ret = 0;
	for (int i = N - 1; i < M; i++)
		if (C[i] == 0)
			ret++;
	return ret;
}



int main() {
	int c;
	cin >> c;
	for (int i = 0; i < c; i++) {
		string member, fen;
		cin >> member;
		cin >> fen;

		cout << hugs(member, fen) << endl;
	}
}