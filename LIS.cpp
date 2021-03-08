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


int cache3[101],choices[101];

// 실제 정답을 저장
int lis4(int start) {
	int& ret = cache3[start + 1];
	if (ret != -1) return ret;
	ret = 1;
	int bestNext = -1;
	for (int next = start + 1; next < n; next++) {
		if (start == -1 || S[start] < S[next]) {
			int cand = lis4(next) + 1;
			if (cand > ret) {
				ret = cand;
				bestNext = next;
			}
		} 
	}
	choices[start + 1] = bestNext;
	return ret;
}

void reconstruct(int start, vector<int>& seq) {
	if (start != -1) seq.push_back(S[start]);
	int next = choices[start + 1];
	if (next != -1) reconstruct(next, seq);
}



int main() {
	vector<int>A = { 1,5,4,3,2,8 };
	memset(cache, -1, sizeof(cache));
	memset(cache2, -1, sizeof(cache2));
	memset(cache3, -1, sizeof(cache3));
	memset(choices, -1, sizeof(choices));
	n = 5;
	S[0] = 1, S[1] = 5, S[2] = 4, S[3] = 3, S[4] = 2, S[5] = 8;
	cout << lis(A) << endl;
	cout << lis4(-1) << endl;
	vector<int>ans;
	reconstruct(0, ans);
	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i] << " ";
	}
	cout << endl;

}