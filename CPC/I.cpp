#include <bits/stdc++.h>

#define ll long long

using namespace std;

int main() {
  double m, n;
  ll k, p;

  while (true) {
    cin >> m >> n;

    if (m == -1 || n == -1)
      break;

    k = round(m * 20 / n);
    p = round(m / n * 100);

    if (m == n) {
      for (int i = 0; i < 8; i++)
        cout << "*";
      cout << "100%";
      for (int i = 0; i < 8; i++)
        cout << "*";
      cout << "\n";
      continue;
    }

    for (int i = 0; i < 20; i++) {
      if (i == 9) {
        if (p < 10) {
          cout << p << "%";
          i++;
        } else {
          cout << p << "%";
          i += 2;
        }
      } else if (i < k)
        cout << "*";
      else {
        cout << "-";
      }
    }

    cout << "\n";
  }

  return 0;
}
