#include <bits/stdc++.h>
using namespace std;

int matrixMultiplication(vector<int> &arr) {
  
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int len = 2; len < n; len++) {
        for (int i = 0; i < n - len; i++) {
            int j = i + len;
            dp[i][j] = INT_MAX;

            for (int k = i + 1; k < j; k++) {
                int cost = dp[i][k] + dp[k][j] + arr[i] * arr[k] * arr[j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }
    
    return dp[0][n - 1];
}

int main() {
  
    vector<int> arr = {5, 4, 3, 2};
    cout << matrixMultiplication(arr);
    return 0;
}