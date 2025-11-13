#include <bits/stdc++.h>
#include "../data/Union find.cpp"

typedef vector<int> vi;
typedef vector<vi> vvi;

// Returns a cycle in a directed graph, or empty if none exists. $O(n+m)$
vi dfs_cycle(const vvi &adj) {
    int n = adj.size();
    vi color(n, 0), path;
    vi cycle;
    function<bool(int)> dfs = [&](int v) {
        color[v] = 1; path.push_back(v);
        for (int u : adj[v]) {
            if (color[u] == 0 && dfs(u)) return true;
            else if (color[u] == 1) {
                auto it = find(path.begin(), path.end(), u);
                cycle.assign(it, path.end());
                return true;
            }
        }
        path.pop_back(); color[v] = 2;
        return false;
    };
    for (int i = 0; i < n; i++)
        if (color[i] == 0 && dfs(i)) break;
    return cycle;
}
// Check the undirected graph contains a cycle in ~$O(m)$.
bool dsu_cycle(int n, vvi &edges) {
    union_find uf(n); //c.f. union find
    for (auto &e : edges) { 
        if (uf.find(e[0])==uf.find(e[1])) return true;
        uf.unite(e[0],e[1]);
    }
    return false;
}

// Tortoise \& Hare: finds start of cycle in a functional graph (-1 if none). $O(n)$ 
int floyd_cycle(int start, vi& nxt){
    int tort=start, hare=start;
    do {
        if(hare==-1 || nxt[hare]==-1) return -1;
        tort = nxt[tort];
        hare = nxt[nxt[hare]];
    } while(tort!=hare);
    tort=start;
    while(tort!=hare){
        tort=nxt[tort]; hare=nxt[hare];
    }
    return tort;
}



