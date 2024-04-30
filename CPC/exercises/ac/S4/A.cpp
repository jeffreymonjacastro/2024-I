#include <bits/stdc++.h>

using namespace std;

#define cpu() ios::sync_with_stdio(false); cin.tie(nullptr)
typedef long long ll;
typedef long double lld;

const int MAX = INT32_MAX;
const int MIN = INT32_MIN;

int main(){
	cpu();

	ll n, days = 0;
	cin >> n;

	for (ll i = 0; i < n; i++){
		if (i * (i + 1) / 2 < n) {
			days++;
		} else {
			break;
		}
	}

	cout << days;
	return 0;
}