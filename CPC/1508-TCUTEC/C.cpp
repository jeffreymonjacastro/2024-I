#include <bits/stdc++.h>
using namespace std;
#define cpu()                                                                  \
  ios::sync_with_stdio(false);                                                 \
  cin.tie(nullptr);
#define ll long long
#define lld long double

const int mod = 1e9 + 7;

void solve() {
  int t, x1, y1, x2, y2, count = 0;
  cin >> t >> x1 >> y1 >> x2 >> y2;
  string s;
  cin >> s;

  for (int i = 0; i < t; i++) {
    if (x1 == x2 && y1 == y2)
      break;

    if (s[i] == 'N' && y1 < y2) {
      y1++;
    } else if (s[i] == 'S' && y1 > y2) {
      y1--;
    } else if (s[i] == 'E' && x1 < x2) {
      x1++;
    } else if (s[i] == 'W' && x1 > x2) {
      x1--;
    }

    count++;
  }

  if (x1 == x2 && y1 == y2)
    cout << count;
  else
    cout << -1;
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