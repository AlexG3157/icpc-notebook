#include <bits/stdc++.h>
#include "../data/Fenwick Tree.cpp"

using namespace std;
typedef vector<int> vi;

// Count pairs where order flips between arrays. $O(n log n)$
ll inversions(vi& a, vi& b) {
    int n = a.size();
    unordered_map<int,int> pos;
    for (int i = 0; i < n; i++) pos[b[i]] = i + 1;
    Fenwick t(n); // C.f. Fenwick tree
    ll inv = 0;
    for (int i = 0; i < n; i++) {
        inv += i - t.sum(pos[a[i]]);
        t.add(pos[a[i]], 1);
    }
    return inv;
}