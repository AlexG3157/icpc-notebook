#include<bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int,int> pii;
typedef vector<pii> vpi;


// Euler Path/Circuits:\\
// Undirected:\\
// - Circuit: all vertices even degree and connected.\\
// - Path: exactly 2 odd-degree vertices and connected; start at one of them.\\
// - Trick: to use circuit function for path, add dummy edge between odd vertices, find circuit, remove dummy.\\
// Directed:\\
// - Circuit: strongly connected, indegree[v] == outdegree[v] $\forall$v.\\
// - Path: one vertex with out-in=1(start), one with in-out=1 (end), rest balanced.\\
// - Trick: add dummy edge end->start, find circuit, rotate to remove dummy.\\



// Find Euler path in directed graph. $O(E)$ MODIFIES THE GRAPH!!!
vi euler_directed(vvi &adj, int start=0) {
    vi path; stack<int> st; st.push(start);
    while(!st.empty()) {
        int v = st.top();
        if(!adj[v].empty()) {
            int u = adj[v].back(); adj[v].pop_back();
            st.push(u);
        } else {
            path.push_back(v);
            st.pop();
        }
    }
    reverse(path.begin(), path.end());
    return path; // size = E+1 if valid Euler tour
}
// Input: adj[u][i] = {v,id}, adj[v][j] = {u,id} if u and v adjacent (same id for both edges).
vi euler_undirected(int n, vector<vpi>& adj) {
    vi used, path; stack<int> st; st.push(0);
    int m=0; for (auto &v:adj) m += v.size(); used.assign(m/2,0);
    while(!st.empty()){
        int v=st.top();
        while(!adj[v].empty() && used[adj[v].back().second]) 
            adj[v].pop_back();
        if(adj[v].empty()){
            path.push_back(v);
            st.pop();
        } else {
            auto e=adj[v].back(); adj[v].pop_back();
            used[e.second]=1;
            st.push(e.first);
        }
    }
    reverse(path.begin(), path.end());
    return path;
}
