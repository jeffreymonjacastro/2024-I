#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define vl vector<ll>

int main(){
  int n, a;
  cin >> n;

  vl sums(n + 1, 0);

  for (int i = 0; i < n; i++){
    cin >> a;
    sums[i + 1] = sums[i] + a;
  }

  map<ll, ll> seen;
  seen[0] = 1;

  


}