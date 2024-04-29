#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
	int n, total = 0;
	cin >> n;

	vector<int> v(n);

	for (int i = 0; i < n; i++){
		cin >> v[i];
		total += v[i];
	}

	sort(v.begin(), v.end(), greater<int>());

	int sum = 0;
	int count = 0;

	for (int i = 0; i < n; i++){
		sum += v[i];
		total -= v[i];
		count++;

		if (sum > total) {
			cout << count;
			break;
		}
	}

	return 0;
}