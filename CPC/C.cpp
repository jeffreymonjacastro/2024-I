#include <bits/stdc++.h>
using namespace std;
#define cpu()                                                                  \
  ios::sync_with_stdio(false);                                                 \
  cin.tie(nullptr);
#define ll long long
#define lld long double

const int mod = 1e9 + 7;

void solve() {
  int n;
  cin >> n;
  vector<int> v(n + 1);
  v[0] = 1e9;

  for (int i = 1; i <= n; i++)
    cin >> v[i];

  vector<int> dp(n + 1);
  dp[0] = 0;
  dp[1] = 0;

  for (int i = 2; i <= n; i++) {
    dp[i] =
        min(abs(v[i] - v[i - 1]) + dp[i - 1], abs(v[i] - v[i - 2]) + dp[i - 2]);
  }

  cout << dp[n] << endl;
}

int main() {
  cpu();
  int t;
  t = 1;
  // cin >> t;
  while (t--)
    solve();
  return 0;
}