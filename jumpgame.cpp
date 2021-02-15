#include <iostream>
#include <vector>

int board[7][7] = {
	{2,5,1,6,1,4,1},
	{6,1,1,2,2,9,3},
	{7,2,3,2,1,3,1},
	{1,1,3,1,7,1,2},
	{4,1,2,3,4,1,2},
	{3,3,1,2,3,4,1},
	{1,5,2,9,4,7,-1}
};



bool jumpRecur(int x, int y) {
	//±âÀú»ç·Ê1
	if (x < 0 || x>6) return false;
	if (y < 0 || y>6) return false;
	//±âÀú»ç·Ê2
	if (board[x][y] == -1) return true;

	int move = board[x][y];
	/*
	if (jumpRecur(x + move, y)) {
		return true;
	}
	if (jumpRecur(x, y + move)) {
		return true;
	}
	return false;
	*/
	return jumpRecur(x + move, y) || jumpRecur(x, y + move);
}

int n = 7;
int cache[100][100];

bool jumpDynamic(int x, int y) {
	if (x > n - 1 || y > n - 1) return 0;
	if (x == n - 1 && y == n - 1) return 1;

	int& ret = cache[x][y];
	if (ret != -1) return ret;
	int move = board[x][y];
	return ret = jumpDynamic(x + move, y) + jumpDynamic(x, y + move);
}


using namespace std;
int main() {
	memset(cache, -1, sizeof(cache));
	cout << jumpRecur(0, 0) << endl;
	cout << jumpDynamic(0, 0) << endl;
}