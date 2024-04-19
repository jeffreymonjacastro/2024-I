#include <iostream>

using namespace std;
 struct record{
	 int key;
	 int left;
	 int right;

	 record(int key, int left, int right) : key(key), left(left), right(right) {}
 };


void foo( int old , int n  ){

	if(n>=0){

		cout<<"OLD :"<<old<<endl;
		cout<<"current :"<<n<<endl;
		foo(n , n-1);
	}else {
		cout<<"OLD :"<<old<<endl;
		cout<<"current :"<<n<<endl;
		return;
	}
	cout<<"RECURSION SURGING..."<<endl;
	cout<<"OLD :"<<old<<endl;
	cout<<"current :"<<n<<endl;
}

int main(){

	foo(-1 , 5);
	return 0;
}