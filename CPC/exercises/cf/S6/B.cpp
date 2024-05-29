#include <iostream>

using namespace std;

int main(){
  int t, sx, sy, ex, ey;
  cin >> t >> sx >> sy >> ex >> ey;
  string s;

  cin >> s;

  for (char c : s){
    if (c == 'E' && ex > sx) sx++;
    if (c == 'W' && ex < sx) sx--;
    if (c == 'N' && ey > sy) sy++;
    if (c == 'S' && ey < sy) sy--;
    if (sx == ex && sy == ey){
      cout << t - s.size() << endl;
      return 0;
    }
  }

  return -1;
}