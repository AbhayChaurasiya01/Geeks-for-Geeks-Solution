class Solution{
public:
    int minCost(vector<vector<int>> &costs) {
        int n = costs.size();
        if (n == 0) return 0;
        int k = costs[0].size();

        // If there's only one color and more than one wall, it's impossible.
        if (k == 1 && n > 1) return -1;

        // dp[i][j] stores the minimum cost to paint walls up to index i,
        // with wall i painted with color j.
        vector<vector<int>> dp(n, vector<int>(k));

        // Base case: For the first wall (index 0), the cost is just the cost
        // of painting it with each respective color.
        for (int j = 0; j < k; ++j) {
            dp[0][j] = costs[0][j];
        }

        // Iterate through the walls starting from the second wall.
        for (int i = 1; i < n; ++i) {
            // Find the two minimum costs from the previous row (i-1)
            // to optimize finding the minimum cost for the current wall.
            int min1 = INT_MAX, min2 = INT_MAX;
            int min1_idx = -1;

            for (int prev_color = 0; prev_color < k; ++prev_color) {
                if (dp[i-1][prev_color] < min1) {
                    min2 = min1;
                    min1 = dp[i-1][prev_color];
                    min1_idx = prev_color;
                } else if (dp[i-1][prev_color] < min2) {
                    min2 = dp[i-1][prev_color];
                }
            }

            // For each color of the current wall.
            for (int j = 0; j < k; ++j) {
                // If the current color is the same as the color that resulted
                // in min1 from the previous wall, we must use min2.
                if (j == min1_idx) {
                    dp[i][j] = costs[i][j] + min2;
                } else {
                    // Otherwise, we can use min1.
                    dp[i][j] = costs[i][j] + min1;
                }
            }
        }

        // The minimum total cost is the minimum value in the last row of dp.
        int min_total_cost = INT_MAX;
        for (int j = 0; j < k; ++j) {
            min_total_cost = min(min_total_cost, dp[n-1][j]);
        }

        return min_total_cost;
    }
};