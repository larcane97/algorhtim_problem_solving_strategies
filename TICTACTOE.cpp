#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool isFinished(const vector<string>& board, char turn);

int bijection(const vector<string>& board) {
	int ret = 0;
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			ret = ret * 3;
			if (board[x][y] == 'o') ret++;
			else if (board[x][y] == 'x') ret += 2;
		}
	}
	return ret;
}

int cache[19683];

int canWin(vector<string>& board, char turn) {
	if (isFinished(board, 'o' + 'x' - turn)) return -1;
	int& ret = cache[bijection(board)];
	if (ret != -2) return ret;

	int minValue = 2;
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			if (board[x][y] == '.') {
				board[x][y] = turn;
				minValue = min(minValue, canWin(board, 'o' + 'x' - turn));
				board[x][y] = '.';
			}
		}
	}
	if (minValue == 0 || minValue == 2) return ret = 0;

	return ret -= minValue;
}