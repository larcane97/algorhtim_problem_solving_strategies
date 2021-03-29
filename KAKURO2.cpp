#include <iostream>
#include <vector>

using namespace std;



int getSize(int mask);

int getSum(int mask);

int getCandidates(int len, int sum, int known) {
	int allSets = 0;

	for (int set = 0; set < 1024; set += 2) {
		if ((set & known) == known
			&& getSize(set) == len
			&& getSum(set) == sum) {
			allSets |= set;
		}
	}
	return allSets & ~known;
}

int candidates[10][46][1024];

void generateCandidates() {
	memset(candidates, 0, sizeof(candidates));

	for (int set = 0; set < 1024; set += 2) {
		int l = getSize(set), s = getSum(set);
		int subset = set;
		while (true) {
			candidates[l][s][subset] |= (set & ~subset);
			if (subset == 0) break;
			subset = (subset - 1) & set;
		}
	}
}

const int MAXN = 20;
int n, color[MAXN][MAXN], value[MAXN][MAXN], hint[MAXN][MAXN][2];
int q, sum[MAXN * MAXN], length[MAXN * MAXN], known[MAXN * MAXN];

void put(int x, int y, int val) {
	for (int h = 0; h < 2; h++) 
		known[hint[x][y][h]] += (1 << val);
	value[x][y] = val;
}

void remove(int x, int y, int val) {
	for (int h = 0; h < 2; h++)
		known[hint[x][y][h]] -= (1 << val);
	value[x][y] = 0;
}

int getCandHint(int hint) {
	return candidates[length[hint]][sum[hint]][known[hint]];
}

int getCandCoord(int x, int y) {
	return getCandHint(hint[x][y][0]) & getCandHint(hint[x][y][1]);
}

void printSolution();

#define WHITE 1
bool search() {
	int x = -1, y = -1, minCands = 1023;
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < n; i++) {
			if (color[j][i] == WHITE && value[j][i] == 0) {
				int cands = getCandCoord(j, i);
				if (getSize(minCands) > getSize(cands)) {
					minCands = cands;
					x = i, y = j; 
				}
			}
		}
	}
	if (minCands == 0) return false;
	if (x == -1) {
		printSolution();
		return true;
	}
	for(int val=1;val<=9;val++)
		if (minCands & (1 << val)) {
			put(x, y, val);
			if (search()) return true;
			remove(x, y, val);
		}
	return false;
}
