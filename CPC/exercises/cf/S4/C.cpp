#include <bits/stdc++.h>
 
using namespace std;

#define cpu() ios::sync_with_stdio(false); cin.tie(nullptr)
typedef long long ll;
typedef long double lld;

const int MAX = INT32_MAX;
const int MIN = INT32_MIN;
 
void solve(){
  string s;
  cin >> s;

  int m, l, r;
  cin >> m;

  vector<bool> p(s.length() - 1, false);

  for (int i = 0; i < s.length()-1; i++){
    if (s[i+1] == s[i]) 
      p[i] = true;
  }

  vector<int> psum(s.length());

  for (int i = 0; i < s.length()-1; i++){
    psum[i+1] = psum[i] + p[i];
  }

  for (int i = 0; i < m; i++){
    cin >> l >> r;

    cout << psum[r-1] - psum[l-1] << endl;  
  }

}

int main(){
  solve();
}