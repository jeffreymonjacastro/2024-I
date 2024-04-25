#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
	int r, c, cant_fil = 0, cant_col = 0, fil = 0, col = 0;
	cin >> r >> c;

	vector<vector<char>> m(r, vector<char>(c));

	for (int i = 0; i < r; i++){
		for (int j = 0; j < c; j++)
	  		cin >> m[i][j];
	}

	bool flag;
	for (int i = 0; i < r; i++){
		flag = true;
		for (int j = 0; j < c; j++) {
			if (m[i][j] == 'S')
				flag = false;
		}

		if (flag) {
			cant_fil++;
			fil += c;
		}
	}

	for (int j = 0; j < c; j++){
		flag = true;
		for (int i = 0; i < r; i++){
			if (m[i][j] == 'S')
				flag = false;
		}

		if (flag) {
			cant_col++;
			col += r;
		}
	}

	cout << (fil + col) - (cant_fil * cant_col);

	return 0;
}