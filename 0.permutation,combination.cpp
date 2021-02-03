#include <iostream>
#include <vector>

using namespace std;

#define MAX 5
int Arr[MAX];
bool Select[MAX];


void Print() {
	for (int i = 0; i < MAX; i++) {
		if (Select[i] == true)
			cout << Arr[i] << " ";
	}
	cout << endl;
}


void DFS(int idx, int cnt) {
	if (cnt == 3) {
		Print();
		return;
	}
	for (int i = idx; i < MAX; i++) {
		if (Select[i] == true) continue;
		Select[i] = true;

		DFS(i, cnt + 1);
		Select[i] = false;

	}

}


int main() {
	for (int i = 0; i < MAX; i++) {
		Arr[i] = i + 1;
	}
	DFS(0, 0);

}