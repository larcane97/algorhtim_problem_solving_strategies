#include <iostream>
#include <vector>
#include <string>
using namespace std;

int n, capacity;
int volume[100], need[100];
int cache[1001][100];
string name[100];

int pack(int capacity, int item) {
	if (item == n) return 0;
	int& ret = cache[capacity][item];
	if (ret != -1) return ret;
	// 담지 않을 경우
	ret = pack(capacity, item + 1);
	// 담을 경우
	if (capacity >= volume[item])
		ret = max(ret, pack(capacity - volume[item], item + 1) + need[item]);
	return ret;
}

void reconstruct(int capacity, int item, vector<string>& picked) {
	if (item == n) return;
	if (pack(capacity, item) == pack(capacity, item + 1))
		reconstruct(capacity, item + 1, picked);
	else {
		picked.push_back(name[item]);
		reconstruct(capacity - volume[item], item + 1, picked);
	}
}


int main() {
	int c;
	cin >> c;
	for (int i = 0; i < c; i++) {
		cin >> n >> capacity;
		memset(cache, -1, sizeof(cache));
		for (int j = 0; j < n; j++)
			cin >> name[j] >> volume[j] >> need[j];
		cout << pack(capacity,0) << endl;
		vector<string> picked;
		reconstruct(capacity,0,picked);
		for (int i = 0; i < picked.size(); i++) {
			cout << picked[i] << endl;
		}
	}
}
