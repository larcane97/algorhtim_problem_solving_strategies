#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_N 10000
int n;
int e[MAX_N],m[MAX_N];

int heat() {
	vector<pair<int, int>>order;
	for (int i = 0; i < n; i++) {
		order.push_back(make_pair(-e[i], i));
	}
	sort(order.begin(), order.end());
	int ret = 0, beginEat = 0;
	for (int i = 0; i < n; i++) {
		int box = order[i].second;
		beginEat += m[box];
		ret = max(ret, beginEat + e[box]);
	}
	return ret;
}




int main() {
	int c;
	cin >> c;
	for (int i = 0; i < c; i++) {
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> m[j];
		for (int j = 0; j < n; j++)
			cin >> e[j];
		cout << heat() << endl;
		
	}
}