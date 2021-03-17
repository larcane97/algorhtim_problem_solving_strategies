#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
using namespace std;


/*void strcat(char* dest, const char* src) {
	while (*dest) dest++;
	while (*src) *(dest++) = *(src++);
	*dest = 0;
}*/


int n;

//int calc(vector<int>& strLen) {
//	sort(strLen.begin(), strLen.end());
//	int curLen = 0;
//	int ret = 0;
//	for (int i = 0; i < n-1; i++) {
//		curLen +=strLen[i];
//		ret += curLen + strLen[i + 1];
//	}
//	return ret;
//}


int concat(const vector<int>& lengths) {
	priority_queue<int, vector<int>, greater<int>>pq;
	for (int i = 0; i < lengths.size(); i++) {
		pq.push(lengths[i]);
	}
	int ret = 0;
	while (pq.size() > 1) {
		int min1 = pq.top();
		pq.pop();
		int min2 = pq.top();
		pq.pop();
		pq.push(min1 + min2);
		ret += min1 + min2;
	}
	return ret;
}


int main() {
	int c;
	cin >> c;
	for (int i = 0; i < c; i++) {
		cin >> n;
		vector<int> strLen(n);
		for (int j = 0; j < n; j++)
			cin >> strLen[j];
		cout << concat(strLen) << endl;
	}
}