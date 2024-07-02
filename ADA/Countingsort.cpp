#include <iostream>
#include <vector>

using namespace std;

#define vi vector<int>

void counting_sort(vi &A, vi &B, int k) {
  vi C(k, 0);

  for (int j = 0; j < A.size(); j++) {
    C[A[j]] = C[A[j]] + 1;
  }

  for (int i = 1; i < k; i++) {
    C[i] = C[i] + C[i - 1];
  }

  cout << "C (inicial): ";

  for (int i = 0; i < k; i++) {
    cout << C[i] << " ";
  }

  cout << endl;

  for (int j = A.size() - 1; j >= 0; j--) {
    B[C[A[j]] - 1] = A[j];
    C[A[j]] = C[A[j]] - 1;
  }

  cout << "C (final): ";
  for (int i = 0; i < k; i++) {
    cout << C[i] << " ";
  }
  cout << endl;
}

int main() {
  vi A = {6, 0, 2, 0, 1, 3, 4, 6, 1, 3, 2};
  vi B(A.size(), 0);

  cout << "A: ";
  for (int i = 0; i < A.size(); i++) {
    cout << A[i] << " ";
  }

  cout << endl;

  counting_sort(A, B, 7);

  cout << "B: ";
  for (int i = 0; i < B.size(); i++) {
    cout << B[i] << " ";
  }
}