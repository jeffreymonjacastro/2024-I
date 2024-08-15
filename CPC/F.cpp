#include <bits/stdc++.h>
using namespace std;
#define cpu()                                                                  \
  ios::sync_with_stdio(false);                                                 \
  cin.tie(nullptr);
#define ll long long
#define lld long double

const int mod = 1e9 + 7;

void solve() {
  int n, W;
  cin >> n >> W;

  vector<int> w(n);
  vector<int> v(n);
  int max = 0;

  for (int i = 0; i < n; i++) {
    cin >> w[i] >> v[i];
    max += v[i];
  }

  vector<ll> dp(max + 1, 1e9);
  dp[0] = 0;

  for (int i = 0; i < n; i++) {
    for (int j = max; j >= v[i]; j--) {
      dp[j] = min(dp[j], dp[j - v[i]] + w[i]);
    }
  }

  int ans = 0;
  for (int i = 0; i <= max; i++) {
    if (dp[i] <= W) {
      ans = i;
    }
  }

  cout << ans << endl;
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