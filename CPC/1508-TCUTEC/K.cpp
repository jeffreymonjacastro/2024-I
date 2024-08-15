#include <bits/stdc++.h>
using namespace std;
#define cpu()                                                                  \
  ios::sync_with_stdio(false);                                                 \
  cin.tie(nullptr);
#define ll long long
#define lld long double

const int mod = 1e9 + 7;

void solve() {

  unordered_map<int, int> front, back;
  unordered_set<int> all_numbers;
  int n;
  cin >> n;
  int ai, bi;
  for (size_t i = 0; i < n; i++) {

    cin >> ai >> bi;

    all_numbers.insert(ai);
    all_numbers.insert(bi);

    if (ai != bi) {
      if (front.find(ai) == front.end())
        front[ai] = 1;
      else
        front[ai]++;
      if (back.find(bi) == back.end())
        back[bi] = 1;
      else
        back[bi]++;

    } else {
      if (front.find(ai) == front.end())
        front[ai] = 1;
      else
        front[ai]++;
    }
  }

  ll ans = INT_MAX;

  for (auto val : all_numbers) {
    ll f = (front.find(val) != front.end()) ? front[val] : 0;
    ll b = (back.find(val) != back.end()) ? back[val] : 0;

    // cout << val << " " << front[val] << " " << back[val] << endl;
    ll coso = 0;
    ll prom = (n + 2 - 1) / 2;

    if (f >= prom)
      ans = min(ans, coso);

    if (f + b >= prom) {
      ll temp = min(abs(prom - f), b);
      ans = min(ans, temp);
    }
  }

  if (ans == INT_MAX)
    cout << -1 << endl;
  else
    cout << ans << endl;
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