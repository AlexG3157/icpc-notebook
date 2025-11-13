#include <bits/stdc++.h>
#include "../data/RMQ.cpp"

using namespace std;

struct LCA {
    int n; vvi adj;
    vi depth, first, euler;
    RMQ rmq; // c.f. RMQ structure. 
    LCA(int _n) : n(_n), adj(n), depth(n), first(n), rmq(vi()) {}
    void add_edge(int u,int v){ adj[u].push_back(v); adj[v].push_back(u); }
    void dfs(int v, int p, int d) {
        first[v] = euler.size();
        depth[v] = d;
        euler.push_back(v);
        for(int u: adj[v]) if(u != p) {
            dfs(u, v, d+1);
            euler.push_back(v); 
        }
    }
    void build(int root=0) {
        euler.clear();
        dfs(root,-1,0);
        vi D(euler.size());
        for(int i=0;i<euler.size();i++) D[i]=depth[euler[i]];
        rmq = RMQ(D);
    } // dist(a,b) = depth[a] + depth[b] - 2 * depth[lca];
    int query(int a,int b){
        int l = first[a], r = first[b];
        if(l>r) swap(l,r);
        return euler[rmq.query(l,r+1)];
    }
};
