#include <iostream>
#include <vector>

using namespace std;

//#define MAX 5
//int Arr[MAX];
//bool Select[MAX];
//
//
//void Print() {
//	for (int i = 0; i < MAX; i++) {
//		if (Select[i] == true)
//			cout << Arr[i] << " ";
//	}
//	cout << endl;
//}
//
//
//void DFS(int idx, int cnt) {
//	if (cnt == 3) {
//		Print();
//		return;
//	}
//	for (int i = idx; i < MAX; i++) {
//		if (Select[i] == true) continue;
//		Select[i] = true;
//
//		DFS(i, cnt + 1);
//		Select[i] = false;
//
//	}
//
//}
//
//
//int main() {
//	for (int i = 0; i < MAX; i++) {
//		Arr[i] = i + 1;
//	}S
//	DFS(0, 0);
//
//}

void print(vector<int>& arr) {
	for (int i = 0; i < arr.size(); i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	return;

}

void DFS(vector<bool>&arr,vector<int>&ans,int cur,int count) {

	if (ans.size() == count) {
		print(ans);
		return;
	}

	for (int i = 0; i < arr.size(); i++) {
		if (arr[i])
			continue;
		arr[i] = true;
		ans.push_back(i + 1);
		DFS(arr, ans,i + 1,count);
		ans.pop_back();
		arr[i] = false;
	}


}


int main() {
	vector<bool>arr = { false,false,false ,false};
	vector<int>ans;
	DFS(arr, ans,0,3);

}