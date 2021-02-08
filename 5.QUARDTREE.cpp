#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <istream>
#define MAX_SIZE 20
using namespace std;

char decompressed[20][20];

void decompress(string::iterator& it, int y, int x, int size) {
	char head = *(it++);
	if (head == 'b' || head == 'w') {
		for (int dy = 0; dy < size; dy++) {
			for (int dx = 0; dx < size; dx++) {
				decompressed[y + dy][x + dx] = head;
			}
		}
	}
	else {
		int half = size / 2;
		decompress(it, y, x, half);
		decompress(it, y, x + half, half);
		decompress(it, y + half, x,half);
		decompress(it, y + half, x + half, half);
	}
}

string reverse(string::iterator& it) {
	char head = *it;
	++it;
	if (head == 'b' || head == 'w')
		return string(1,head);
	string upperLeft = reverse(it);
	string upperRight = reverse(it);
	string lowerLeft = reverse(it);
	string lowerRight = reverse(it);

	return string("x") + lowerLeft + lowerRight + upperLeft + upperRight;
}

int main() {
	int c;
	cin >> c;
	for (int i = 0; i < c; i++) {
		string arr;
		cin >> arr;
		string::iterator it = arr.begin();
		
		cout << reverse(it) << endl;

	}
	

}