#include <iostream>
#define inf -987654321
using namespace std;


// Memoization
int n, triangle[100][100];
int cache[100][100];
int path2(int x, int y) {
	if (x == n - 1) return triangle[x][y];

	int& ret = cache[x][y];
	if (ret != -1) return ret;
	return ret = max( path2(x+1,y), path2(x+1,y+1)) + triangle[x][y];
}


int arr[5][5] = {
	{1,inf,inf,inf,inf},
	{2,4,inf,inf,inf},
	{8,16,8,inf,inf},
	{32,64,32,64},
	{128,256,128,256,128}
};
int maxPath[5][5];
int main() {
	memset(maxPath, -1, sizeof(maxPath));

	maxPath[0][0] = arr[0][0];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j <= i; j++) {
			maxPath[i + 1][j] = max(maxPath[i + 1][j], arr[i + 1][j] + maxPath[i][j]);
			maxPath[i + 1][j + 1] = max(maxPath[i + 1][j + 1], arr[i + 1][j + 1] + maxPath[i][j]);
		}
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j <= i; j++)
			cout << maxPath[i][j] << ' ';
		cout << endl;
	}

}