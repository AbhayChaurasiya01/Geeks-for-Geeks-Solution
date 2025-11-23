class Solution {
  public:

    // DSU helper
    int find(int x, vector<int>& parent) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x], parent);
    }

    void unite(int a, int b, vector<int>& parent, vector<int>& rank) {
        a = find(a, parent);
        b = find(b, parent);
        if (a == b) return;
        
        if (rank[a] < rank[b]) parent[a] = b;
        else if (rank[b] < rank[a]) parent[b] = a;
        else {
            parent[b] = a;
            rank[a]++;
        }
    }

    int maxRemove(vector<vector<int>>& stones) {
        int n = stones.size();
        
        // Each stone is a node: index 0..n-1
        vector<int> parent(n), rank(n, 0);

        for (int i = 0; i < n; i++) parent[i] = i;

        // Connect stones that share row or column
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (stones[i][0] == stones[j][0] || stones[i][1] == stones[j][1]) {
                    unite(i, j, parent, rank);
                }
            }
        }

        // Count number of connected components
        int components = 0;
        for (int i = 0; i < n; i++) {
            if (find(i, parent) == i)
                components++;
        }

        // Answer = total stones − connected components
        return n - components;
    }
};
