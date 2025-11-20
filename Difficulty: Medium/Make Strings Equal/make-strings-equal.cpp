class Solution {
  public:
    int minCost(string &s, string &t, vector<vector<char>> &transform,
                vector<int> &cost) {
        
        int n = s.size();
        const long long INF = 1e18;

        // 26 x 26 distance matrix
        vector<vector<long long>> dist(26, vector<long long>(26, INF));

        // cost of same → same is 0
        for (int i = 0; i < 26; i++) dist[i][i] = 0;

        // load given transformations
        for (int i = 0; i < transform.size(); i++) {
            int u = transform[i][0] - 'a';
            int v = transform[i][1] - 'a';
            dist[u][v] = min(dist[u][v], (long long)cost[i]);
        }

        // Floyd–Warshall on 26 nodes
        for (int k = 0; k < 26; k++) {
            for (int i = 0; i < 26; i++) {
                for (int j = 0; j < 26; j++) {
                    if (dist[i][k] < INF && dist[k][j] < INF) {
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }

        long long ans = 0;

        // compute answer for each index
        for (int i = 0; i < n; i++) {
            int a = s[i] - 'a';
            int b = t[i] - 'a';

            long long best = INF;

            // try making both s[i] and t[i] into some character x
            for (int x = 0; x < 26; x++) {
                if (dist[a][x] < INF && dist[b][x] < INF) {
                    best = min(best, dist[a][x] + dist[b][x]);
                }
            }

            if (best == INF) return -1; // impossible
            ans += best;
        }

        return (int)ans;
    }
};
