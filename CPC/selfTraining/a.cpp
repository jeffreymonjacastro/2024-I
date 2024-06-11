#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int left(int i){
        return 2*i;
    }

    int right(int i){
        return 2*i + 1;
    }

    void max_heapify(vector<pair<int,int>>& A, int i){
        int l = left(i);
        int r = right(i);
        int largest = i;

        if(l <= A.size() && A[l].first > A[i].first){
            largest = l;
        } else if(r <= A.size() && A[r].first > A[largest].first){
            largest = r;
        }

        if (largest != i){
            swap(A[i], A[largest]);
            max_heapify(A, largest);
        }
    }

    void build_max_heap(vector<pair<int,int>>& A){
        int n = A.size();
        for (int i = n/2; i > 0; i--){
            max_heapify(A, i);
        }
    }

    pair<int,int> extract_max(vector<pair<int,int>>& A){
        pair<int,int> max = A[1];
        A[1] = A[A.size()];
        A.pop_back();
        max_heapify(A, 1);
        return max;
    }

    vector<string> findRelativeRanks(vector<int>& score) {
        int n = score.size();

        // Vector (score, index)
        vector<pair<int,int>> heap(n+1);

        for (int i = 1; i <= n; i++){
            heap[i] = make_pair(score[i-1], i);
        }

        build_max_heap(heap);

        for (int i = 1; i <= n; i++){
            pair<int,int> max = extract_max(heap);
            cout << max.first << " " << max.second << endl;
        }


        return vector<string>();
    }
};

int main(){
    Solution s;
    vector<int> score = {10, 3, 8, 9, 4};
    s.findRelativeRanks(score);
    return 0;
}