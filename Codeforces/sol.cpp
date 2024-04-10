#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL);
#define ll long long
#define f first
#define s second

void solve(){
  int n, c = 0;
  cin>>n;

  for (int i = 0; i <= n; i ++){
    c = 0;
    for (int j = 0; j <= n; j++){
      if (i + j > n-1) {
        cout << c++ << " ";
      }
      else cout << "  ";
    }

    for (int j = 0; j <= n; j++){
      if (i + j == n) {
        cout << c-- << " ";
      }
    }
    cout << endl;
  }
}

int main(){
  FASTIO
  // ll t=1;
  // //cin>>t;
  // while(t--)
  solve();
  return 0;
}