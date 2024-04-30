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
  
  unordered_map<string,int> m;

  string team;
  for (int i = 0; i < n; i++){
    cin>>team;
    m[team]++;
  }

  pair<string, int> winner;

  for (auto i: m){
    if (i.second > winner.second)
      winner = i;
  }

  cout << winner.first;
}