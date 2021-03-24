#include <iostream>
#include <string>
#include <vector>
using namespace std;



int n, m;
vector<int> eaters[50];
int best;
void slowSearch(int food, vector<int>& edible, int chosen) {
	if (chosen >= best) return;
	if (food = m) {
		if (find(edible.begin(), edible.end(), 0) == edible.end())
			best = chosen;
		return;
	}

	slowSearch(food + 1, edible, chosen);

	for (int j = 0; j < eaters[food].size(); j++)
		edible[eaters[food][j]]++;
	slowSearch(food + 1, edible, chosen + 1);
	for (int j = 0; j < eaters[food].size(); j++)
		edible[eaters[food][j]]--;

}

vector<int> canEat[50], eaters[50];

void search(vector<int>& edible, int chosen) {
	if (chosen >= best) return;
	int first = 0;
	while (first < n && edible[first]>0)++first;
	if (first == n) { best = chosen; return; }

	for (int i = 0; i < canEat[first].size(); i++) {
		int food = canEat[first][i];
		for (int j = 0; j < eaters[food].size(); j++)
			edible[eaters[food][j]]++;
		search(edible, chosen + 1);
		for (int j = 0; j < eaters[food].size(); j++)
			edible[eaters[food][j]]--;
	}

}