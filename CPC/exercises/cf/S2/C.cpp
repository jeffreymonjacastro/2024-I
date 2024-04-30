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
  for (int i = 0; i <= n; i++) {
    c = 0;
    for (int j = 0; j <= n; j++){
      if (i == 0 && j >= n - i)
        cout << c++;
      else if (j >= n - i)
        cout << c++ << " ";
      else
        cout << "  ";
    }

    c--;

    for (int j = n-1; j >= 0; j--){
      if (i > j && j == 0)
        cout << --c;
      else if (i > j)
        cout << --c << " ";
    }

    cout << endl;
  }

  for (int i = 0; i < n; i++){
    c = 0;
    for (int j = 0; j <= n; j++){
      if (i == n-1 && j > i)
        cout << c++;
      else if (j > i)
        cout << c++ << " ";
      else 
        cout << "  ";
    }

    c--;

    for (int j = n-1; j > 0; j--){
      if (c == 1)
        cout << --c;
      else if (j > i)
        cout << --c << " ";
    }
    cout << endl;
  }
  


  return 0;
}