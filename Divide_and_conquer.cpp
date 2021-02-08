#include <vector>
#include <iostream>

using namespace std;


// fastSum(x) = 1 + 2 + ... + x
int fastSum(int x) {
	// ±âÀú»ç·Ê
	if (x == 1)
		return 1;
	
	if (x % 2 == 1)
		return x + fastSum(x - 1);
	else 
		return 2 * fastSum(x / 2) + (x/2)*(x/2);
	
}

//ÀÏ¹ÝÀûÀÎ °ö¼À : O(n^2)
void normalize(vector<int>& num) {
	num.push_back(0);
	for (int i = 0; i + 1 < num.size(); i++) {
		if (num[i] < 0) {
			int borrow = (abs(num[i]) + 9) / 10;
			num[i + 1] -= borrow;
			num[i] += borrow * 10;
		}
		else {
			num[i + 1] += num[i] / 10;
			num[i] %= 10;
		}
	}
	while (num.size() > 1 && num.back() == 0) num.pop_back();
}

vector<int> multiply(const vector<int>& a, const vector<int>& b) {
	vector<int> c(a.size() + b.size() + 1, 0);
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < b.size(); j++) {
			c[i + j] += a[i] * b[j];
		}
	}
	normalize(c);
	return c;
}


// Ä«¶óÃ÷¹Ù °ö¼À ¾Ë°í¸®Áò
void addTo(vector<int>& a, const vector<int>& b, int k) {
	int t = min<int>(a.size(), b.size());
	for (int i = 0; i < k; i++)
		a.push_back(0);
	for (int i = 0; i <t; i++) {
		a[k + i] = b[i];
	}
	normalize(a);
	return;
}
void subFrom(vector<int>& a, const vector<int>& b) {
	int t = min<int>(a.size(), b.size());
	for (int i = 0; i <t; i++) {
		a[i] -= b[i];
	}
	normalize(a);
}

vector<int> karatsuba(const vector<int>& a, const vector<int>& b) {
	int an = a.size(), bn = b.size();
	if (an < bn) return karatsuba(b, a);
	if (an == 0 || bn == 0) return vector<int>();
	if (an <= 50) return multiply(a, b);

	int half = an / 2;
	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> a1(a.begin() + half, a.end());
	vector<int>b0(b.begin(), b.begin() + min<int>(half, bn));
	vector<int>b1(b.begin() + min<int>(half, bn), b.end());

	vector<int>z2 = karatsuba(a1, b1);
	vector<int>z0 = karatsuba(a0, b0);

	addTo(a0, a1, 0); addTo(b0, b1, 0);
	
	vector<int>z1 = karatsuba(a0, b0);
	subFrom(z1, z0);
	subFrom(z1, z2);
	vector<int> ret(an+bn);
	
	addTo(ret, z0, 0);
	addTo(ret, z1, half);
	addTo(ret, z2, half + half);
	return ret;

}





int main() {
	
	vector<int> a(52);
	vector<int> b(51);

	for (int i = 0; i < a.size(); i++) {
		a[i] = 1 ;
	}
	for (int i = 0; i < b.size(); i++) {
		b[i] = 2;
	}

	// vector<int>c = multiply(a, b);

	vector<int>c = karatsuba(a, b);

	for (int i = c.size() - 1; i > -1; i--) {
		cout << c[i];
	}
	cout << endl;


}