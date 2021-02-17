#include <iostream>
#include <vector>

using namespace std;


// 완전 탐색
int lis(vector<int>& S) {
	if (S.empty()) return 0;
	int ret = 0;
	for (int i = 0; i < S.size(); i++) {
		vector<int>B;
		for (int j = i + 1; j < S.size(); j++) {
			if (S[j] > S[i]) B.push_back(S[j]);
		}
		ret = max(lis(B)+1, ret);
	}
	return ret;
}

// 동적 계획법
int n;
int cache[100], S[100];
int lis2(int start) {
	int& ret = cache[start];
	if (ret != -1) return ret;
	ret = 1;
	for (int next = start + 1; next < n; next++) {
		if (S[start] < S[next])
			ret = max(ret, lis2(next) + 1);
	}
	return ret;
}


// 처음부터 끝까지 자동으로 최대값 탐색
int cache2[101];

int lis3(int start) {
	int& ret = cache2[start+1];
	if (ret != -1) return ret;
	ret = 1;
	for (int next = start + 1; next < n; next++) {
		if (start == -1 || S[start] < S[next])
			ret = max(ret, lis3(next)+1);
	}
	return ret;
}



int main() {
	vector<int>A = { 1,5,4,3,2,8 };
	memset(cache, -1, sizeof(cache));
	memset(cache2, -1, sizeof(cache2));
	n = 5;
	S[0] = 1, S[1] = 5, S[2] = 4, S[3] = 3, S[4] = 2, S[5] = 8;
	cout << lis(A) << endl;
	cout << lis3(-1) << endl;

}