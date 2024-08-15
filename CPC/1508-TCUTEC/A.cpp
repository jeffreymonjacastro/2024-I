#include <bits/stdc++.h>
using namespace std;
#define cpu()                                                                  \
  ios::sync_with_stdio(false);                                                 \
  cin.tie(nullptr);
#define ll long long
#define lld long double

const int mod = 1e9 + 7;

void solve() {
  int n, a, b, c = 0;
  cin >> n >> a >> b;

  vector<int> groups(n);

  for (int i = 0; i < n; i++)
    cin >> groups[i];

  ll ans = 0;
  for (int i = 0; i < n; i++) {
    if (groups[i] == 1) {
      if (a > 0) {
        a--;
      } else if (b > 0) {
        b--;
        c++;
      } else if (c > 0) {
        c--;
      } else
        ans += 1;
    }
    if (groups[i] == 2) {
      if (b > 0)
        b--;
      else
        ans += 2;
    }
  }

  cout << ans << '\n';
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