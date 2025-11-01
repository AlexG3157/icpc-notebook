#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef pair<int,int> pii;

// Find shortest paths from src (no negative weights). O((V+E)logV)
vi dijkstra(const vector<vector<pii>>& adj, int src) {
    vi dist(adj.size(), INT_MAX);
    priority_queue<pii, vector<pii>, greater<pii>> q; 
    dist[src] = 0; q.push({0, src});
    while (!q.empty()) {
        auto [d, u] = q.top(); q.pop();
        if (d != dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (d+w < dist[v]) {
                dist[v] = d+w;
                q.push({d+w, v});
            }
        }
    }
    return dist;
}

// $O(VE)$ Shortest Path+neg edges; BFS from nodes with dist $-\infty$ for all neg-cycle reachable.
vector<int> bellmanFord(int n, vector<vector<int>>& edges, int src) {
	vector<int> dist(n, INT_MAX);
	dist[src] = 0;
	for (int i = 0; i < n; i++) { 
		for (vector<int> edge : edges) {
			int u = edge[0];int v = edge[1];int wt = edge[2];
			if (dist[u] != INT_MAX && dist[u] + wt < dist[v]) {
                if(i == n - 1) return {-1};
                dist[v] = dist[u] + wt;
            }
		}
	}
    return dist;
}

// All-pairs shortest paths (neg edges ok, no neg cycles) $O(V^3)$ 
// $graph[i][i]=0$, $graph[i][j]=w$ if edge $i->j$ else $INT\_MAX$
vector<vi> floydWarshall(vector<vi> graph) {
    int V = graph.size();
    auto dist = graph; 
    for (int k = 0; k < V; ++k)
        for (int i = 0; i < V; ++i)
            for (int j = 0; j < V; ++j)
                if (dist[i][k] < INT_MAX && dist[k][j] < INT_MAX)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    return dist;
}



