#include <bits/stdc++.h>
using namespace std;
#define cpu()                                                                  \
  ios::sync_with_stdio(false);                                                 \
  cin.tie(nullptr);
#define ll long long
#define lld long double

const int mod = 1e9 + 7;

ll recursive(ll n, vector<int> &v, ll div, ll init, ll end) {
  if (init == end)
    return v[init];
  else {
    return v[end]
  }
}

void solve() {
  int n;
  cin >> n;
  vector<int> v(n);

  for (int i = 0; i < n; i++)
    cin >> v[i];

  sort(v.begin(), v.end());
}

int main() {

#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);   // for taking input
  freopen("output.txt", "w", stdout); // for displaying output
#endif

  int t;
  t = 1;
  // cin>>t;
  while (t--)
    solve();
  return 0;
}