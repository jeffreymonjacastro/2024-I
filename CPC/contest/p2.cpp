#include <iostream>

using namespace std;

void solve(){
	long long n;
	cin>>n;

	long long sum = n;

	for (long long i = n; i > 0; i/=2){
		sum += i/2;
	}

	cout<<sum<<endl;
}

int main(){
	int t;
	cin>>t;

	while(t--){
		solve();
	}
}