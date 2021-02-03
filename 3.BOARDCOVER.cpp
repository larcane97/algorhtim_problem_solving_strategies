#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
char BOARD[20][20];

int h, w;

int isPossibleBlock(int i, int j) {

	//case 1
	int i1_1 = i, j1_1 = j + 1;
	int i1_2 = i + 1, j1_2 = j + 1;
	if (i1_2 < h && j1_2 < w)
		if (BOARD[i1_1][j1_1] == '.' && BOARD[i1_2][j1_2] == '.')
			return 1;

	//case 2
	int i2_1 = i + 1, j2_1 = j;
	int i2_2 = i + 1, j2_2 = j - 1;
	if (i2_2 < h && j2_2 >= 0)
		if (BOARD[i2_1][j2_1] == '.' && BOARD[i2_2][j2_2] == '.')
			return 2;

	//case 3
	int i3_1 = i + 1, j3_1 = j;
	int i3_2 = i + 1, j3_2 = j + 1;
	if (i3_2 < h && j3_2 < w)
		if (BOARD[i3_1][j3_1] == '.' && BOARD[i3_2][j3_2] == '.')
			return 3;

	//case 4
	int i4_1 = i - 1, j4_1 = j;
	int i4_2 = i - 1, j4_2 = j + 1;
	if (i4_2 >= 0 && j4_2 < w)
		if (BOARD[i4_1][j4_1] == '.' && BOARD[i4_2][j4_2] == '.')
			return 4;

	return -1;

}

int countBoardCover(int num) {
	if (num == (h - 1) * (w - 1))
		return 1;

	//x,y변환
	int i = num / w; // 0 
	int j = num % w; // 5


	//기저사례 : 마지막까지 탐색한 경우
	int ret = 0;

	if (BOARD[i][j] == '.') {
		if (isPossibleBlock(i, j) == 1) {
			int i1_1 = i, j1_1 = j + 1;
			int i1_2 = i + 1, j1_2 = j + 1;
			BOARD[i1_1][j1_1] = BOARD[i1_2][j1_2] = '#';
			ret +=countBoardCover(num + 1);
			BOARD[i1_1][j1_1] = BOARD[i1_2][j1_2] = '.';
		}
		if (isPossibleBlock(i, j) == 2) {
			int i2_1 = i + 1, j2_1 = j;
			int i2_2 = i + 1, j2_2 = j - 1;
			BOARD[i2_1][j2_1] = BOARD[i2_2][j2_2] = '#';
			ret +=countBoardCover(num + 1);
			BOARD[i2_1][j2_1] = BOARD[i2_2][j2_2] = '.';
		}
		if (isPossibleBlock(i, j) == 3) {
			int i3_1 = i + 1, j3_1 = j;
			int i3_2 = i + 1, j3_2 = j + 1;
			BOARD[i3_1][j3_1] = BOARD[i3_2][j3_2] = '#';
			ret += countBoardCover(num + 1);
			BOARD[i3_1][j3_1] = BOARD[i3_2][j3_2] = '.';
		}
		if (isPossibleBlock(i, j) == 4) {
			int i4_1 = i - 1, j4_1 = j;
			int i4_2 = i - 1, j4_2 = j + 1;
			BOARD[i4_1][j4_1] = BOARD[i4_2][j4_2] = '#';
			ret += countBoardCover(num + 1);
			BOARD[i4_1][j4_1] = BOARD[i4_2][j4_2] = '.';
		}
		// 불가능한 경우
		if (isPossibleBlock(i, j) == -1)
			return 0;

	}
	else {
		countBoardCover(num + 1);
	}

	return ret;

}

int main() {
	int c;
	cin >> c;

	for (int i = 0; i < c; i++) {

		for (int a = 0; a < 20; a++) {
			for (int b = 0; b < 20; b++)
				BOARD[a][b] = 0;
		}
		scanf("%d %d ", &h, &w);
		for (int j = 0; j < h; j++) {
			for (int k = 0; k < w; k++)
				scanf("%c", &BOARD[j][k]);
			while (cin.get() != '\n');
		}
		printf("\n");

		for (int j = 0; j < h; j++) {
			for (int k = 0; k < w; k++)
				printf("%c", BOARD[j][k]);
			printf("\n");
		}
		int ret = countBoardCover(0);
		printf("%d\n", ret);
	}

}
*/
int h, w;
const int coverType[4][3][2] = {
	{ {0,0},{1,0},{0,1} },
	{{0,0},{0,1},{1,1}},
	{{0,0},{1,0},{1,1}},
	{{0,0},{1,0},{1,-1}}
};

bool set(vector<vector<int>>& board, int y, int x, int type, int delta) {
	bool ok = true;
	for (int i = 0; i < 3; i++) {
		const int ny = y + coverType[type][i][0];
		const int nx = x + coverType[type][i][1];
		if (ny < 0 || ny >= board.size() || nx < 0 || nx >= board[0].size())
			ok = false;
		else if ((board[ny][nx] += delta) > 1)
			ok = false;
	}
	return ok;
}

int cover(vector<vector<int>>& board) {
	int y = -1, x = -1;
	for (int i = 0; i <h; i++) {
		for (int j = 0; j < w; j++) {
			if (board[i][j] == 0) {
				y = i;
				x = j;
				break;
			}
		}
		if (y != -1)	break;
	}

	if (y == -1) return 1;
	int ret = 0;
	for (int type = 0; type < 4; type++) {
		if (set(board, y, x, type, 1))
			ret += cover(board);
		set(board, y, x, type, -1);
	}
	return ret;
}

int main() {
	int c;
	cin >> c;
	
	for (int i = 0; i < c; i++) {

		scanf("%d %d", &h, &w);
		vector<vector<int>>BOARD(h);
		for (int j = 0; j < h; j++)
			BOARD.push_back(vector<int>(w));
		
		for (int j = 0; j < h; j++) {
			for (int k = 0; k < w; k++) {
				char tmp;
				scanf("%c", &tmp);
				tmp == '.' ? (BOARD[j]).push_back(0) : (BOARD[j]).push_back(1);
			}
			while (cin.get() != '\n');
		}
		printf("\n");

		for (int j = 0; j < h; j++) {
			for (int k = 0; k < w; k++)
				printf("%d", BOARD[j][k]);
			printf("\n");
		}

		int ret = cover(BOARD);
		printf("%d\n", ret);
	}
}