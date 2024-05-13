#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class NextGuess {
public:
	int guess(vector<int> guesses, string answers){
    int low = -1000047;
    int high = 1000047;
    int n = guesses.size();

		for (int i = 0; i < n; i++){
      if (answers[i] == '<')
        high = min(guesses[i], high);
      
      else 
        low = max(guesses[i], low);
      
		}

    return (low + high) / 2;
	}
};

int main(){
  NextGuess ng;
  vector<int> guesses = {100, 2000, 1, 20};
  string answers = "><><";

  cout << ng.guess(guesses, answers) << endl;

  return 0;
}