#include <iostream>
#include <vector>

using namespace std;

#define ll long long

const ll MOD = 1e9 + 7;

int main(){
  int n; 
  cin>>n;

  vector<ll> dp(n+1, 0);

  dp[0] = 1;

  for (int i = 1; i <= n; i++){
    for (int j = 1; j <= min(6, n); j++){
      if (i-j >= 0){
        dp[i] = (dp[i] + dp[i-j]) % MOD;
      }
    }
  }

  cout << dp[n] << endl;

  return 0;
}