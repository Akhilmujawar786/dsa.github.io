#include <iostream>
#include <vector>
using namespace std;

// Function to implement the Hungarian algorithm for load assignment
vector<int> hungarianAlgorithm(vector<vector<int>>& costMatrix) {
    int n = costMatrix.size();
    vector<int> assignment(n, -1);
    vector<int> u(n + 1), v(n + 1), p(n + 1), way(n + 1);
    
    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        int j0 = 0;
        vector<int> minv(n + 1, INT_MAX);
        vector<bool> used(n + 1, false);
        
        do {
            used[j0] = true;
            int i0 = p[j0], delta = INT_MAX, j1;
            
            for (int j = 1; j <= n; ++j) {
                if (!used[j]) {
                    int cur = costMatrix[i0 - 1][j - 1] - u[i0] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta) {
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }
            
            for (int j = 0; j <= n; ++j) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }
            
            j0 = j1;
        } while (p[j0] != 0);
        
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }
    
    for (int j = 1; j <= n; ++j) {
        assignment[p[j] - 1] = j - 1;
    }
    
    return assignment;
}

int main() {
    // Example cost matrix (replace with actual data)
    vector<vector<int>> costMatrix = {
        {10, 19, 8},
        {12, 15, 7},
        {8, 9, 10}
    };
    
    vector<int> assignment = hungarianAlgorithm(costMatrix);
    
    // Output the assigned machine for each load
    for (int i = 0; i < assignment.size(); ++i) {
        cout << "Load " << i + 1 << " assigned to Machine " << assignment[i] + 1 << endl;
    }
    
    return 0;
