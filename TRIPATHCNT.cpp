#include <iostream>
#include <vector>

using namespace std;

int matrix[100][100] = {
	{9,-1,-1,-1},
	{5,7,-1,-1},
	{1,3,2,-1},
	{3,5,5,6}
};
int cache[100][100];
int n;
int path2(int x, int y) {
	if (x == n - 1) return matrix[x][y];

	int& ret = cache[x][y];
	if (ret != -1) return ret;
	
	ret = max(
		path2(x+1, y )+matrix[x][y] , path2(x + 1, y + 1)+matrix[x][y]
	);

	return ret;
}

int countCache[100][100];

int count(int x,int y) {
	if (x == n - 1) return 1;
	int& ret = countCache[x][y];
	if (ret != -1) return ret;
	ret = 0;
	if (path2(x + 1, y + 1) >= path2(x+1, y )) ret += count(x + 1, y + 1);
	if (path2(x + 1, y + 1) <= path2(x + 1, y)) ret += count(x + 1, y);
	return ret;
}


int main() {
	memset(cache, -1, sizeof(cache));
	memset(countCache, -1, sizeof(countCache));
	cin >> n;
	cout << path2(0,0) << endl;
	cout << count(0, 0) << endl;
}