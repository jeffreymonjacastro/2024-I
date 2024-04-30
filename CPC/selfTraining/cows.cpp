#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
  int n, m; 
  cin >> n >> m;
  
  vector<vector<int>> P(n+1, vector<int>(3, 0));

  for (int i = 1; i <= n; i++) {
    int a; cin >> a;
    P[i][0] = P[i-1][0] + (a == 1);
    P[i][1] = P[i-1][1] + (a == 2);
    P[i][2] = P[i-1][2] + (a == 3);
  }

  for (int i = 0; i <= n; i++) {
    cout << P[i][0] << " " << P[i][1] << " " << P[i][2] << "\n";
  }

  for (int i = 0; i < m; i++) {
    int a, b; cin >> a >> b;
    cout << P[b][0]-P[a-1][0] << " ";
    cout << P[b][1]-P[a-1][1] << " ";
    cout << P[b][2]-P[a-1][2] << "\n";
  }
}