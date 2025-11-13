#include<bits/stdc++.h>
#include "Strongly Connected Components.cpp"

using namespace std;

// Check if $n$ variables satisfy $(x_i \vee x_j) \wedge (\neg x_k \vee x_l) \wedge \dots$
struct TwoSAT {
    int n; SCC g; // c.f. strongly connected components
    TwoSAT(int vars): n(vars), g(2*vars) {}
    int var(int i){ return i; }
    int neg(int i){ return i+n; }

    void add_clause(int a, bool a_val, int b, bool b_val){
        int u = a_val ? var(a) : neg(a);
        int v = b_val ? var(b) : neg(b);
        g.add_edge(u^1, v); // ¬a -> b. ^ bitwise XOR, same in python
        g.add_edge(v^1, u); // ¬b -> a
    }
    bool satisfiable(vi& ans){
        g.kosaraju();
        ans.assign(n,0);
        for(int i=0;i<n;i++){
            if(g.scc[var(i)] == g.scc[neg(i)]) return false;
            ans[i] = g.scc[var(i)] > g.scc[neg(i)]; 
        }
        return true;
    }
};
