#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
    //Take inputs
    int n, k, a;
    cin >> n >> k;

    //Keep track of all the previous sums
    //If there is a sum that differ exactly k units from the current one
    //Append answer the total occurrence of that sum
    map<ll,int> seen;
    seen[0] = 1;
    ll ans = 0;
    ll sums = 0;
    while (n--){
        cin >> a;
        sums += a;
        if (seen.count(sums-k)){
            ans += seen[sums-k];
        }
        seen[sums]++;
    }
    //Output
    cout << ans << endl;

    for (auto i : seen){
        cout << i.first << " " << i.second << endl;
    }

    return 0;
}