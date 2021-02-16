#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool match(const string& w, const string& s) {
	int pos = 0;
	while (pos < s.size() && pos < w.size() && (w[pos] == '?' || w[pos] == s[pos]))
		pos++;
	if (pos == w.size())
		return pos == s.size(); // w와 s가 모두 동시에 끝에 도달했을 경우 true를 반환
	if (w[pos] == '*') // pos == s.size()인 경우 포함
		for(int skip = 0; pos + skip <= s.size(); skip++)
			if (match(w.substr(pos + 1), s.substr(pos + skip)))
				return true;
	return false;
}

int cache[101][101];
string W, S;

bool matchMemoized(int w, int s) {
	int& ret = cache[w][s];
	if (ret != -1) return ret;
	while (s < S.size() && w < W.size() &&
		(W[w] == '?' || W[w] == S[s])) {
		w++;
		s++;
	}
	if (w == W.size()) return s == S.size();

	if (W[w] == '*') {
		for (int skip = 0; skip + s <= S.size(); skip++) {
			if (matchMemoized(w + 1, s + skip))
				return ret = 1;
		}
	}
	return ret = 0;
}



int main() {
	int c;
	cin >> c;
	for (int i = 0; i < c; i++) {
		vector<string> store;
		int n;
		cin >> W;
		cin >> n;
		for (int j = 0; j < n; j++) {
			memset(cache, -1, sizeof(cache));
			cin >> S;
			if (matchMemoized(0, 0))
				store.push_back(S);
		}

		for (int k = 0; k < store.size(); k++) {
			cout << store.at(k) << endl;
		}
		store.clear();
	}
}