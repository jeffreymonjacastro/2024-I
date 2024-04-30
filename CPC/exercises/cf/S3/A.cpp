#include <bits/stdc++.h>

using namespace std;

#define cpu() ios::sync_with_stdio(false); cin.tie(nullptr)
typedef long long ll;
typedef long double lld;

const int MAX = INT32_MAX;
const int MIN = INT32_MIN;

int main(){
	int n, k;
	cin >> n >> k;

	vector<bool> b(n, true);

	int a;
	for (int i = 0; i < n; i++){
		cin>>a;
		if (a + k > 5){
			b[i] = false;
		}
	}

	int n_groups = 0;
	for (int i = 0; i < n; i++){
		if (b[i])
			n_groups++;
	}

	cout << n_groups / 3;

  	return 0;
}