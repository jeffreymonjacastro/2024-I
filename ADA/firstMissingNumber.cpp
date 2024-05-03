#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
//
////int Binary(vector<int>& A, int l, int r){
////	int m = (l + r) / 2;
////
////	if (r - l > 1){
////		if (A[m] == m)
////			return Binary(A, m+1, r);
////		else
////			return Binary(A, l, m);
////	} else
////		return A[m-1] + 1;
////}
////
////void solve(vector<int>& A){
////	int n = A.size() - 1;
////
////	if (A[1] != 1)
////		cout << 1;
////	else if (A[n] == n)
////		cout << n + 1;
////	else
////		cout << Binary(A, 1, n);
////}
////
////int main(){
////	int n;
////	cin>>n;
////	vector<int> A(n + 1);
////
////	for(int i = 1; i <= n; i++) cin>>A[i];
////
////	solve(A);
////
////	return 0;
////}
//
//
//int Binary(vector<int>& A, int l, int r){
//	int m = (l + r + 1) / 2;
//
//	if (r > l){
//		if (A[m - 1] == m)
//			return Binary(A, m, r);
//		else
//			return Binary(A, l, m - 1);
//	} else
//		return A[m-1] + 1;
//}
//
//int firstMissingPositive(vector<int>& nums) {
//	sort(nums.begin(), nums.end());
//
//	int n = nums.size();
//
//	if (nums[0] != 1)
//		return 1;
//	else if (nums[n - 1] == n)
//		return n + 1;
//	else
//		return Binary(nums, 0, n - 1);
//}
//
//int main(){
//	int n;
//	cin>>n;
//	vector<int> A(n);
//
//	for(int i = 0; i < n; i++) cin>>A[i];
//
//	cout << firstMissingPositive(A);
//}

int main() {
	int n;
	cout << "Ingresa el valor de n:";
	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			cout << " ";
		}
		for (int j = 0; j < n - i; j++) {
			if (i == n/2)
				cout << n/2 + 2;
			else
				cout << "*";
		}
		for (int k = 0; k < n - i - 1; k++) {
			if (i == n/2)
				cout << n/2 + 2;
			else
				cout << "*";
		}
		cout << endl;
	}
}

