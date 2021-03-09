#include <iostream>
#include <vector>
#include <string>

using namespace std;


const int EMPTY = -987654321;
int n, board[50];
int cache[50][50];
int play(int left, int right) {
	if (left > right) return 0;
	int& ret = cache[left][right];
	if (ret != EMPTY) return ret;

	ret = max(
		board[left] - play(left + 1, right),
		board[right] - play(left, right - 1)
	);
	if (right - left + 1 >= 2) {
		ret = max(ret, -play(left + 2, right));
		ret = max(ret, -play(left, right - 2));
	}
	return ret;
}


//int game(vector<int>& board,bool turn) {
//	if (board.empty()) return 0;
//	int score = 0;
//	vector<int> v1(board.begin() + 1, board.end());
//	vector<int> v2(board.begin(), board.end() - 1);
//	
//	int cand1 = board[0] + game(v1, !turn);
//	int cand2 = board[board.size() - 1] + game(v2, !turn);
//	int cand3 = -1001;
//	int cand4 = -1001;
//	if (board.size() >= 2) {	
//		vector<int>v3(board.begin() + 2, board.end());
//		vector<int>v4(board.begin(), board.end()-2);
//		int cand3 = game(v3, !turn);
//		int cand4 = game(v4, !turn);
//	}
//	if (turn) {
//		int cand = max(cand1, cand2);
//		cand = max(cand, cand3);
//		cand = max(cand, cand4);
//		score += cand;
//	}
//	else {
//		int cand = max(cand1, cand2);
//		cand = max(cand, cand3);
//		cand = max(cand, cand4);
//		score -= cand;
//	}
//	return score;
//}

void resetCache() {
	for (int i = 0; i < 50; i++) 
		for (int j = 0; j < 50; j++)
			cache[i][j] = EMPTY;
}

int main() {
	int c;
	cin >> c;
	for (int i = 0; i < c; i++) {
		resetCache();
		int n;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> board[j];
		cout << play(0, n - 1) << endl;
	}
}