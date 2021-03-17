#include <iostream>
#include <vector>
#include <string>

using namespace std;

char board[5][5];

bool isWin(int num,bool turn) {
	if (num > 25) return turn ? false : true;
	int x = num / 5;
	int y = num % 5;
	bool check = false;
	for (int i = x; i < 5; i++) {
		//if (check) break;
		for(int j=y;j<5;j++){

			// (check) break;
			if (board[i][j] == '.') {
				if (i + 1 < 5 && board[i + 1][j] == '.') {
					board[i][j] = '#';
					board[i + 1][j] = '#';
					check |= isWin(num + 1, !turn);
					board[i][j] = '.';
					board[i + 1][j] = '.';
				}
				if (j + 1 < 5 && board[i][j + 1] == '.') {
					board[i][j] = '#';
					board[i][j + 1] = '#';
					check |= isWin(num + 2, !turn);
					board[i][j] = '.';
					board[i][j + 1] = '.';
				}
				if ((i + 1 < 5 && board[i + 1][j] == '.') &&
					(j + 1 < 5 && board[i + 1][j + 1] == '.')
					) {
					board[i][j] = '#';
					board[i + 1][j] = '#';
					board[i + 1][j + 1] = '#';
					check |= isWin(num + 1, !turn);
					board[i][j] = '.';
					board[i + 1][j] = '.';
					board[i + 1][j + 1] = '.';

				}
				if ((j + 1 < 5 && board[i][j + 1] == '.') &&
					(j + 1 < 5 && board[i + 1][j + 1] == '.')
					) {
					board[i][j] = '#';
					board[i][j + 1] = '#';
					board[i + 1][j + 1] = '#';
					check |= isWin(num + 2, !turn);
					board[i][j] = '.';
					board[i][j + 1] = '.';
					board[i + 1][j + 1] = '.';
				}
			}
			else
				check |= isWin(num + 1, !turn);
		}
	}
	// 내 차례이고 이긴다면
	if (turn && check) return true;
	// 내 차례이고 진다면
	if (turn && !check) return false;
	// 상대 차례이고 이긴다면
	if (!turn && check) return false;
	// 상대 차례이고 진다면
	if (!turn && !check) return true;
}

int main() {
	int c;
	cin >> c;
	for (int i = 0; i < c; i++) {
		for (int j = 0; j < 5; j++)
			for (int k = 0; k < 5; k++)
				cin >> board[j][k];
		
		bool ret = isWin(0, true);
		if (ret)
			cout << "WINNING" << endl;
		else
			cout << "LOSING" << endl;

	}

	
}