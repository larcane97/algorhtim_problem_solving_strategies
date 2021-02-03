#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>

using namespace std;

bool isFriends[10][10];
bool isConnected[10];

int checkPossibleConnect(int n) {
	int ret = 0;
	// 기저사례 : 모든 짝이 맞춰진 경우
	bool isFinished = true;
	int firstFriend = -1;
	for (int i = 0; i < n; i++) {
		if (!isConnected[i]) {
			isFinished = false;
			firstFriend = i;
			break;
		}
	}
	if (isFinished) return 1;
	
	for (int i = firstFriend+1; i < n; i++) {
		if (isFriends[firstFriend][i] && !isConnected[i]) {
			isConnected[firstFriend] = isConnected[i] = true;
			ret +=checkPossibleConnect(n);
			isConnected[firstFriend] = isConnected[i] = false;
		}
	}
	return ret;
}

int main() {
	int c, n, m;
	cin >> c;
	for (int k = 0; k < c; k++) {
		cin >> n >> m;

		for (int i = 0; i <n; i++) {
			for (int j = 0; j <n; j++)
				isFriends[i][j] = false;
			isConnected[i] = false;
		}

		int a, b;
		for (int i = 0; i < m; i++) {
			scanf("%d %d",&a,&b);
			isFriends[a][b] = isFriends[b][a] = true;
		}
		int ret = checkPossibleConnect(n);
		printf("%d\n", ret);


	}
}