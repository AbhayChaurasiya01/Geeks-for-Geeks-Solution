class Solution {
  public:

    vector<long long> dijkstra(int V, vector<vector<pair<int,int>>> &adj, int src) {
        const long long INF = 1e18;
        vector<long long> dist(V, INF);
        priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;

        dist[src] = 0;
        pq.push({0, src});

        while(!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if(d != dist[u]) continue;

            for(auto &p : adj[u]) {
                int v = p.first;
                long long w = p.second;

                if(dist[v] > d + w) {
                    dist[v] = d + w;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    }

    int shortestPath(int V, int a, int b, vector<vector<int>> &edges) {
        const long long INF = 1e18;

        // adjacency list for straight edges only
        vector<vector<pair<int,int>>> adj(V);

        // store curved edges
        vector<array<int,4>> curved;

        for(auto &e : edges) {
            int u = e[0], v = e[1], w1 = e[2], w2 = e[3];

            adj[u].push_back({v, w1});
            adj[v].push_back({u, w1});

            curved.push_back({u, v, w1, w2});
        }

        // Dijkstra from a (only straight edges)
        vector<long long> distA = dijkstra(V, adj, a);

        // Dijkstra from b (only straight edges)
        vector<long long> distB = dijkstra(V, adj, b);

        long long ans = distA[b]; // straight-only path

        // Try each curved edge once
        for(auto &e : curved) {
            int u = e[0], v = e[1], w1 = e[2], w2 = e[3];

            if(distA[u] != INF && distB[v] != INF)
                ans = min(ans, distA[u] + w2 + distB[v]);

            if(distA[v] != INF && distB[u] != INF)
                ans = min(ans, distA[v] + w2 + distB[u]);
        }

        return (ans >= INF ? -1 : (int)ans);
    }
};
