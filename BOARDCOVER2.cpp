#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


vector<vector<pair<int, int>>>rotations;
int blockSize;

vector<string> rotate(const vector<string>& arr) {
	vector<string> ret(arr[0].size(), string(arr.size(), ' '));
	for (int i = 0; i < arr.size(); i++) {
		for (int j = 0; j < arr[i].size(); j++) {
			ret[j][arr.size() - i - 1] = arr[i][j];
		}
	}
	return ret;
}

void generateRotations(vector<string> block) {
	rotations.clear();
	rotations.resize(4);
	for (int rot = 0; rot < 4; rot++) {
		int originX = -1, originY = -1;
		for (int i = 0; i < block.size(); i++) {
			for (int j = 0; j < block[i].size(); j++) {
				if (block[i][j] == '#') {
					if (originX == -1) {
						originX = i;
						originY = j;
					}

					rotations[rot].push_back(make_pair(i - originX, j - originY));
				}
			}
		}
		block = rotate(block);
	}
	sort(rotations.begin(), rotations.end());
	rotations.erase(unique(rotations.begin(), rotations.end()), rotations.end());
	blockSize = rotations[0].size();
}



int boardH, boardW;
vector<string> board;

int covered[10][10];
int best;
int currentBlank;

bool set(int x, int y, const vector<pair<int, int>>& block, int delta) {
	bool ret = true;
	for (int i = 0; i < block.size(); i++) {
		int newX = x + block[i].first;
		int newY = y + block[i].second;
		if ((newX >= boardH || newX < 0 || newY >= boardW || newY < 0))
			ret = false;
		else {
			if(covered[newX][newY] > 0)
				ret = false;
			covered[newX][newY] += delta;
		}
	}
	return ret;
}

void search(int placed) {
	if ( placed + currentBlank / blockSize < best)
		return;
	int x = -1;
	int y = -1;
	for (int i = 0; i < boardH; i++) {
		for (int j = 0; j < boardW; j++)
			if (covered[i][j] == 0){
				x = i;
				y = j;
				break;
			}
		if (x != -1) break;
	}
	if (x == -1) {
		best = max(best, placed);
		return;
	}
	for (int i = 0; i < rotations.size(); i++) {
		if (set(x, y, rotations[i], 1)) {
			currentBlank -= blockSize;
			search(placed + 1);
			currentBlank += blockSize;
		}
		set(x, y, rotations[i], -1);
	}
	covered[x][y] = 1;
	search(placed);
	covered[x][y] = 0;
}

int solve() {
	best = 0;
	currentBlank = boardH * boardW;

	for (int i = 0; i < boardH; i++) {
		for (int j = 0; j < boardW; j++) {
			if (board[i][j] == '#') {
				covered[i][j] = 1;
				currentBlank--;
			}
			else
				covered[i][j] = 0;
		}
	}
	search(0);
	return best;
}


int main() {
	int T;
	cin >> T;
	for (int iter = 0; iter < T; iter++) {
		cin >> boardH >> boardW;
		int blockH, blockW;
		cin >> blockH >> blockW;
		vector<string>block(blockH);
		for (int i = 0; i < boardH; i++) {
			string s;
			cin >> s;
			board.push_back(s);
		}
		for (int i = 0; i < blockH; i++)
			cin >> block[i];

		generateRotations(block);
		cout << solve() << endl;
		
	}
	
}

//int main() {
//	int T;
//	cin >> T;
//	for (int i = 0; i < T; i++) {
//		cin >> H >> W;
//		cin >> R >> C;
//		for (int j = 0; j < H; j++)
//			for (int k = 0; k < W; k++)
//				cin >> BOARD[j][k];
//
//		for (int j = 0; j < R; j++) 
//			for (int k = 0; k <C; k++)
//				cin >> BLOCK[j][k];
//
//
//
//
//
//	}
//}