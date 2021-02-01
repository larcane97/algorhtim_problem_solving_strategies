#include <string>
#include <vector>
#include <iostream>
using namespace std;

typedef struct {
	int x;
	int y;
}Point;

Point direction[8] = {
	{-1,1},{0,1},{1,1},{-1,0},{1,0},{-1,-1},{0,-1},{1,-1}
};

vector<string> board = {
	{'N','N','N','N','S'},
	{'N','E','E','E','N'},
	{'N','E','Y','E','N'},
	{'N','E','E','E','N'},
	{'N','N','N','N','N'}
};

bool check = false;

void hasWord(int x, int y, const string& word) {
	static int cur = 1;
	if (cur < word.size()) {
		for (int i = 0; i < 8; i++) {
			int tmpx = x + direction[i].x;
			int tmpy = y + direction[i].y;
			if (tmpx >= 0 && tmpx < 5 && tmpy >= 0 && tmpy < 5) {
				if (board[tmpx][tmpy] == word.at(cur)) {
					cur++;
					hasWord(tmpx, tmpy, word);
					cur--;
				}
			}
		}


	}
	else {
		check = true;
	}

}

int main() {
	hasWord(2, 2, "YEN");
	cout << check << endl;
}