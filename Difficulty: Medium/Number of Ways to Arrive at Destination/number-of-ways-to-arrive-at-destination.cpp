class Solution {
  public:
    int countPaths(int V, vector<vector<int>>& edges) {
        const long long MOD = 1000000007;

        // Adjacency list: {node, weight}
        vector<pair<int,int>> adj[V];

        for(auto &e : edges) {
            int u = e[0], v = e[1], t = e[2];
            adj[u].push_back({v, t});
            adj[v].push_back({u, t});
        }

        // Distance + ways arrays
        vector<long long> dist(V, LLONG_MAX);
        vector<long long> ways(V, 0);

        // Min-heap {dist, node}
        priority_queue<pair<long long,int>,
                       vector<pair<long long,int>>,
                       greater<pair<long long,int>>> pq;

        dist[0] = 0;
        ways[0] = 1;
        pq.push({0, 0});

        while(!pq.empty()) {
            auto [time, node] = pq.top();
            pq.pop();

            if(time > dist[node]) continue;

            for(auto &nbr : adj[node]) {
                int next = nbr.first;
                long long wt = nbr.second;

                // Case 1: Found smaller distance → update
                if(dist[next] > time + wt) {
                    dist[next] = time + wt;
                    ways[next] = ways[node];  // Inherit ways
                    pq.push({dist[next], next});
                }
                // Case 2: Another shortest path found → add ways
                else if(dist[next] == time + wt) {
                    ways[next] = (ways[next] + ways[node]) % MOD;
                }
            }
        }

        return ways[V - 1] % MOD;
    }
};
