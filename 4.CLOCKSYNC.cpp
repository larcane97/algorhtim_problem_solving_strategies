#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <stdio.h>
#define INF 987654321;
const int CLOCKS = 16;
const int SWITCHES = 10;
using namespace std;

int sw[SWITCHES][CLOCKS] = {
	{0,1,2,-1},
	{3,7,9,11,-1},
	{4,10,14,15,-1},
	{0,4,5,6,7,-1},
	{6,7,8,10,12,-1},
	{0,2,14,15,-1},
	{3,14,15,-1},
	{4,5,7,14,15,-1},
	{1,2,3,4,5,-1},
	{3,4,5,9,13,-1}
};

int countSW[SWITCHES] = { 0 };

bool checkSyn(const vector<int>&clock) {
	bool check = true;
	for (int i = 0; i < clock.size(); i++)
		if (clock[i] != 12) {
			check = false;
			break;
		}
	return check;
}

void push(vector<int>& clock, int swtch) {
	int i = 0;
	while (sw[swtch][i] != -1) {
		clock[sw[swtch][i]] += 3;
		if(clock[sw[swtch][i]] == 15)
			clock[sw[swtch][i]] = 3;
		i++;
	}
}

int solve(vector<int>& clock, int swtch) {
	if (swtch == SWITCHES)
		return checkSyn(clock) ? 0 : INF;

	int ret = INF;
	for (int cnt = 0; cnt < 4; cnt++) {
		ret = min(ret, cnt + solve(clock, swtch + 1));
		push(clock, swtch);
	}
	return ret;
}


#include <algorithm>

int main() {
	int c;
	cin >> c;
	for (int i = 0; i < c; i++) {
		vector<int>clock;
		for (int j = 0; j < 16; j++) {
			int tmp;
			scanf("%d", &tmp);
			clock.push_back(tmp);
		}

		int ret = solve(clock, 0);
		printf("%d\n", ret);

	}

}
