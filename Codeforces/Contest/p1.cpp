#include <iostream>
#include <vector>
#include <map>

#define ll long long

using namespace std;

int main(){
	ll n;
	cin >> n;

	vector<ll> a(n);
	map<ll, ll> multiple;

	for (int i = 0; i < n; i++) {
		cin >> a[i];
		multiple[a[i] %= 200]++;
	}

	ll count = 0;

	for (auto i : multiple){
		count += i.second * (i.second - 1) / 2;
	}

	cout << count << endl;
}
