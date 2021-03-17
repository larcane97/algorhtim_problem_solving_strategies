#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n;
int begin[100], end[100];
int schedule() {
	vector<pair<int, int>>order;
	for (int i = 0; i < n; i++)
		order.push_back(make_pair(end[i], begin[i]));
	sort(order.begin(), order.end());

	int earliest = 0, selected = 0;
	for (int i = 0; i < order.size(); i++) {
		int meetingBegin = order[i].second;
		int meetingEnd = order[i].first;

		if (earliest <= meetingBegin) {
			earliest = meetingEnd;
			selected++;
		}
	}
	return selected;
}