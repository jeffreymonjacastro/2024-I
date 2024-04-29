#include <bits/stdc++.h>

using namespace std;

#define cpu() ios::sync_with_stdio(false); cin.tie(nullptr)
typedef long long ll;
typedef long double lld;

const int MAX = INT32_MAX;
const int MIN = INT32_MIN;

int main(){
  int n;
  cin >> n;

  int c;
  for (int i = 0; i < n; i++) {
    c = 0;
    for (int j = 0; j < n; j++){
      cout << c << " ";
    }
    cout << endl;
  }
  


  return 0;
}