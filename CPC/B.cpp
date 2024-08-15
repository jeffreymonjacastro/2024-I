#include <bits/stdc++.h>
using namespace std;
#define cpu()                                                                  \
  ios::sync_with_stdio(false);                                                 \
  cin.tie(nullptr);
#define ll long long
#define lld long double

const int mod = 1e9 + 7;

void solve() {
  int n, a, b, c;
  cin >> n >> a >> b >> c;

  vector<int> M(n + 1);

  M[0] = 0;

  for (int i = 1; i <= n; i++) {
    M[i] = -1e9;
    if (i >= a) {
      M[i] = max(M[i], M[i - a] + 1);
    }
    if (i >= b) {
      M[i] = max(M[i], M[i - b] + 1);
    }
    if (i >= c) {
      M[i] = max(M[i], M[i - c] + 1);
    }
  }

  cout << M[n] << endl;
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