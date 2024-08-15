#include <bits/stdc++.h>
using namespace std;
#define cpu()                                                                  \
  ios::sync_with_stdio(false);                                                 \
  cin.tie(nullptr);
#define ll long long
#define lld long double

const int mod = 1e9 + 7;

void solve() {
  int n, k;
  cin >> n >> k;
  vector<int> v(n + 1);
  v[0] = 1e9;

  for (int i = 1; i <= n; i++)
    cin >> v[i];

  vector<int> dp(n + 1);
  dp[0] = 0;
  dp[1] = 0;

  for (int i = 2; i <= n; i++) {
    for (int j = 1; j <= k; j++) {
      if (i - j < 0)
        break;
      if (j == 1)
        dp[i] = abs(v[i] - v[i - j]) + dp[i - j];
      else
        dp[i] = min(dp[i], abs(v[i] - v[i - j]) + dp[i - j]);
    }
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