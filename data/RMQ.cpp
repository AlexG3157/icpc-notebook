#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;

//Preprocess an array in $O(n \log n)$ to answer range minimum queries in $O(1)$
struct RMQ {
    vvi jmp;
    RMQ(const vi& V) {     // Python: depth = N.bit_length() 
        int N = V.size(), depth = 32 - __builtin_clz(N); 
        jmp.assign(depth, V);
        for(int i = 0; i < depth-1; ++i)
            for(int j = 0; j < N; ++j)
                jmp[i+1][j] = min(jmp[i][j],
                                   jmp[i][min(N-1, j + (1<<i))]);
    }// Returns min{V[a], V[a+1], ..., V[b-1]}
    int query(int a, int b) {
        if(b <= a) return INT_MAX;
        int dep = 31 - __builtin_clz(b - a); // python: (b-a).bit_length() - 1
        return min(jmp[dep][a], jmp[dep][b - (1<<dep)]);
    }
};
