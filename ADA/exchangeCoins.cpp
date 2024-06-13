#include <iostream>
#include <vector>

using namespace std;

int main(){
  int n; cin>>n;
  vector<int> coins(n);

  for (int i = 0; i < n; i++){
    cin >> coins[i];
  }

  int x; cin>>x;

  vector<int> M(x+1, 0);

  for (int i = 1; i <= x; i++){
    M[i] = 1e9;
    for (int j = 1; j <= coins.size(); j++){
      if (i >= coins[j-1]){
        M[i] = min(M[i], M[i - coins[j-1]] + 1);
      }
    }
  }

  cout << M[x] << endl;

  return 0;
}