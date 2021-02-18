#include <iostream>
#include <vector>

using namespace std;

// 1. 완전탐색 : X

// 부분문제 탐색


#define INF 987654321
int cache[10001];
string str;

int getLevel(string str) {
	if (str.empty()) return 0;
	bool chk = true;
	// level 1
	for (int i = 1; i < str.size(); i++) {
		if (str[0] != str[i]) {
			chk = false;
			break;
		}
	}
	if (chk) return 1;

	// level 2
	chk = true;
	for (int i = 0; i < str.size() - 1; i++) {
		if (str[i]+1 != str[i + 1]) {
			chk = false;
			break;
		}
	}
	if (chk) return 2;

	for (int i = 0; i < str.size() - 1; i++) {
		if (str[i]-1 != str[i + 1]) {
			chk = false;
			break;
		}
	}
	if (chk) return 2;

	// level 4
	chk = true;
	char a, b;
	a = str[0], b = str[1];
	for (int i = 2; i < str.size(); i++) {
		if (i % 2 == 0 && a != str[i]) {
			chk = false;
			break;
		}
		if (i % 2 == 1 && b != str[i]) {
			chk = false;
			break;
		}
	}
	if (chk) return 4;

	// level 5
	chk = true;
	char d = str[0] - str[1];
	for (int i = 1; i < str.size() - 1; i++) {
		if (d != str[i] - str[i + 1]) {
			chk = false;
			break;
		}
	}
	if (chk) return 5;

	return 10;

}


int minLevel(int begin) {
	int& ret = cache[begin];
	if (ret != -1) return ret;
	if (begin+2 > str.size())
		return ret = getLevel(str.substr(begin));
	ret = INF;
	if(begin+4 < str.size())
		ret = min(ret, getLevel(str.substr(begin, 5)) + minLevel( begin + 5));
	if (begin + 3 < str.size())
		ret = min(ret, getLevel(str.substr(begin, 4)) + minLevel(begin + 4));
	if (begin + 2 < str.size())
		ret = min(ret, getLevel(str.substr(begin, 3)) + minLevel(begin + 3));
	
	

 	return ret;

}




int main() {
	int c;
	cin >> c;
	for (int i = 0; i < c; i++) {
		memset(cache, -1, sizeof(cache));
		cin >> str;
		cout << minLevel(0) << endl;
	}
	
}