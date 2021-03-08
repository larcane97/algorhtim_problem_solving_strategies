#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


const int MAX = 2000000000 + 1;
int n,k, cacheLen[501], cacheCnt[501], arr[500];
int lis(int start) {
	int& ret = cacheLen[start + 1];
	if (ret != -1) return ret;
	ret = 1;
	for (int next = start + 1; next < n; next++) {
		if (start == -1 || arr[next] > arr[start]) {
			ret = max(ret, lis(next) + 1);
		}
	}
	return ret;
}

int count(int start) {
	if (lis(start) == 1) return 1;
	int& ret = cacheCnt[start + 1];
	if (ret != -1) return ret;
	ret = 0;
	for (int next = start + 1; next < n; next++) {
		if ((start == -1 || arr[next] > arr[start]) && lis(start) == lis(next) + 1) {
			ret = min<long long>(MAX, (long long)ret + count(next));
		}
	}
	return ret;
}


void reconstruct(int start, int skip, vector<int>& l) {
	if (start != -1) l.push_back(arr[start]);
	vector<pair<int, int>> followers;
	for (int next = start + 1; next < n; next++) {
		if ((start == -1 || arr[next] > arr[start]) && lis(start) == lis(next)+1)
			followers.push_back(make_pair(arr[next], next));
	}
	sort(followers.begin(), followers.end());
	for (int i = 0; i < followers.size(); i++) {
		int idx = followers[i].second;
		int cnt = count(idx);
		if (cnt <= skip)
			skip -= cnt;
		else {
			reconstruct(idx, skip, l);
			break;
		}
	}
}

int main() {
	cin >> n >> k;
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	memset(cacheCnt, -1, sizeof(cacheCnt));
	memset(cacheLen, -1, sizeof(cacheLen));
	cout << lis(-1) << endl;
	count(-1);
	vector<int> ans;
	reconstruct(-1, k-1, ans);
	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i] << " ";
	}


}
