#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Function to calculate the minimum expected search cost for OBST
int optimalSearchTree(vector<int>& keys, vector<int>& prob, int n) {
    vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
    vector<vector<int>> sum(n+1, vector<int>(n+1, 0));
    
    // Calculate the cumulative sum of probabilities
    for (int i = 1; i <= n; i++) {
        sum[i][i] = prob[i-1];
        for (int j = i + 1; j <= n; j++) {
            sum[i][j] = sum[i][j-1] + prob[j-1];
        }
    }
    
    // Fill the dp table
    for (int len = 1; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            // Try each key as the root
            for (int r = i; r <= j; r++) {
                int left = (r > i) ? dp[i][r-1] : 0;
                int right = (r < j) ? dp[r+1][j] : 0;
                dp[i][j] = min(dp[i][j], left + right + sum[i][j]);
            }
        }
    }

    return dp[1][n];
}

int main() {
    int n;
    cout << "Enter number of keys: ";
    cin >> n;
    
    vector<int> keys(n);
    vector<int> prob(n);
    
    cout << "Enter the keys (sorted): ";
    for (int i = 0; i < n; i++) {
        cin >> keys[i];
    }
    
    cout << "Enter the probabilities: ";
    for (int i = 0; i < n; i++) {
        cin >> prob[i];
    }

    int result = optimalSearchTree(keys, prob, n);
    cout << "The minimum expected search cost is: " << result << endl;
    
    return 0;
}
