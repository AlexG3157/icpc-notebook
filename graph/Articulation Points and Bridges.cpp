#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;

//$O(V+E)$\\
//AP = vertices whose removal increases \# of connected components.\\
//Bridge = edges whose removal increases \# of connected components.
void tarjan(int u, vvi &adj, vi &vis, vi &disc, vi &low, 
            int &time, int p, vi &isAP, set<pii> &bridges) {
    vis[u] = 1;
    disc[u] = low[u] = ++time;
    int children = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (!vis[v]) {
            children++;
            tarjan(v, adj, vis, disc, low, time, u, isAP, bridges);
            low[u] = min(low[u], low[v]);
            if (low[v] > disc[u]) // Bridge
                bridges.insert({min(u, v), max(u, v)});
            if (p != -1 && low[v] >= disc[u])
                isAP[u] = 1; // Articulation Point
        } 
        else low[u] = min(low[u], disc[v]);
    }
    if (p == -1 && children > 1)
        isAP[u] = 1;
}

pair<vi,set<pii>> findAPandBridges(int V, vvi &adj) {
    vi disc(V), low(V), vis(V), isAP(V); // Initialize with 0s
    set<pii> bridges; 
    int time = 0;
    for (int i = 0; i < V; i++) 
        if (!vis[i]) 
            tarjan(i, adj, vis, disc, low, time, -1, isAP, bridges);
    return {isAP, bridges};
}


