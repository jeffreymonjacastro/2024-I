#include <bits/stdc++.h>
using namespace std;
#define cpu()                                                                  \
  ios::sync_with_stdio(false);                                                 \
  cin.tie(nullptr);
#define ll long long
#define lld long double

const int mod = 1e9 + 7;

void solve() {
  int n, x, y, sum = 0;
  cin >> n >> x;

  for (int i = 0; i < n; i++) {
    cin >> y;
    sum += y;
  }

  if (sum == 0)
    cout << 0 << '\n';
  else if (abs(sum) <= x)
    cout << 1 << '\n';
  else {
    if (abs(sum) % x == 0) {
      cout << abs(sum) / x << '\n';
    } else {
      cout << (abs(sum) / x) + 1 << '\n';
    }
  }
}

int main() {

#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);   // for taking input
  freopen("output.txt", "w", stdout); // for displaying output
#endif

  cpu();
  int t;
  t = 1;
  // cin >> t;
  while (t--)
    solve();
  return 0;
}