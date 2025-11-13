#include<bits/stdc++.h>
#include "../data/Union find.cpp"

typedef vector<int> vi;
typedef vector<vector<int>>vvi;
typedef pair<int,int>pii;
typedef vector<pii> vpi;

// Kruskal $O(E \log E)$ edges list of \{u,v,weight\}
int kruskal(int V, vvi &edges) {
    sort(edges.begin(), edges.end(),[](auto a, auto b){return a[2]<b[2];});
    union_find uf(V);
    int cost = 0, count = 0;
    for (auto &e : edges) {
        if (uf.find(e[0]) != uf.find(e[1])) {
            uf.unite(e[0], e[1]);
            cost += e[2];
            if (++count == V - 1) break;
        }
    }
    return cost;
}
// Prim's $O((E+V) \log V)$ adj[u] list of (v,weight) adjacent to u.
int prim(int V, vector<vpi> &adj) {
    priority_queue<pii, vector<pii>, greater<pii>> q;
    vector<bool> vis(V, false);
    q.push({0, 0});
    int res = 0;
    while(!q.empty()){
        auto [w,u] = q.top();q.pop();
        if(vis[u])continue; 
        res += w;  
        vis[u] = true; 
        for(auto v : adj[u]){
            if(!vis[v.first]){
                q.push({v.second, v.first}); 
            }          //weight, vertex
        }
    }
    return res;  
}