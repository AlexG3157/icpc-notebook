#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef pair<int,int> pii;
// \textbf{Complexity:} O(E+VlogV)\\
// \textbf{Use:} Finds the shortest path in an graph with no negative edges.\\

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
// \textbf{Complexity:} O(V*E)\\
// \textbf{Use:} Finds the shortest path in a graph. Detects negative cycles.\\

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


