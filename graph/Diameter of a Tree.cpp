#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;


// Computes the length of the longest path between any two nodes in $O(n)$
pii dfs(int u, int p, vvi& adj) {
    pair<int,int> res = {0, u}; // {distance, node}
    for(int v : adj[u]) if(v != p) {
        auto t = dfs(v, u, adj);
        t.first++;
        res = max(res, t);
    }
    return res;
}
int diameter(vvi& adj)
{
    return dfs(dfs(0, -1,adj).second, -1, adj).first;
}
