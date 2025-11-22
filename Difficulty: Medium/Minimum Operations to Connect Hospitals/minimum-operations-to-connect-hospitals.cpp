class Solution {
  public:
    int minConnect(int V, vector<vector<int>>& edges) {
        // DSU initialization
        vector<int> parent(V), rankv(V, 0);
        for(int i = 0; i < V; i++) parent[i] = i;
        
        function<int(int)> find = [&](int x) {
            if(parent[x] != x) parent[x] = find(parent[x]);
            return parent[x];
        };
        
        auto unionSet = [&](int a, int b) {
            int pa = find(a), pb = find(b);
            if(pa == pb) return false; // already connected → redundant
            if(rankv[pa] < rankv[pb]) parent[pa] = pb;
            else if(rankv[pb] < rankv[pa]) parent[pb] = pa;
            else {
                parent[pb] = pa;
                rankv[pa]++;
            }
            return true;
        };
        
        int extra = 0;
        
        // Process all edges
        for(auto &e : edges) {
            int u = e[0], v = e[1];
            if(!unionSet(u, v)) {
                extra++;  // redundant edge
            }
        }
        
        // Count components
        int comp = 0;
        for(int i = 0; i < V; i++) {
            if(find(i) == i) comp++;
        }
        
        int needed = comp - 1; // edges needed to connect all components
        
        if(extra >= needed) return needed;
        return -1;
    }
};
