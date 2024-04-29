#include <bits/stdc++.h>

using namespace std;

#define cpu() ios::sync_with_stdio(false); cin.tie(nullptr)
typedef long long ll;
typedef long double lld;

const int MAX = INT32_MAX;
const int MIN = INT32_MIN;

void solve(vector<ll> &psum1, vector<ll> &psum2){
  int type, l, r;
  cin >> type >> l >> r;

  if (type == 1){
    cout << psum1[r] - psum1[l-1] << endl;
  } else {
    cout << psum2[r] - psum2[l-1] << endl;
  }
}

int main(){
  int n, m;
  cin >> n;

  vector<ll> v(n), psum1(n+1), psum2(n+1);
  psum1[0] = psum2[0] = 0;

  for(int i = 0; i < n; i++)
    cin>>v[i];

  for(int i = 1; i <= n; i++)
    psum1[i] = psum1[i-1] + v[i-1];

  sort(v.begin(), v.end());
  for(int i = 1; i <= n; i++)
    psum2[i] = psum2[i-1] + v[i-1];

  cin >> m;

  while(m--)
    solve(psum1, psum2);
}