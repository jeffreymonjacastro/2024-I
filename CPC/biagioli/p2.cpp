#include <iostream>
#include <vector>

#define ll unsigned long long

using namespace std;

int main(){
  int n;
  cin>>n;

  // vector<ll> p(n);
  // p[0] = 1;

  // for(int i = 1; i < n; i++){
  //   p[i] = p[i-1] * (i+1);
  // }

  // for (int i = 1; i < n; i++){
  //   cout << p[i] << " = " << p[i-1] << " * " << i + 1 << endl;
  // }

  ll fact = 1;
  for (int i = 1; i <= n; i++){
    fact *= i;
  }

  cout << fact;

  return 0;
}