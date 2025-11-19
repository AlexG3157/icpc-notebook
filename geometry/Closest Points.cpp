#include <bits/stdc++.h>
#include "Points and Lines.cpp"
using namespace std;
// Minimum Euclidean distance between two distinct points. $O(n \log n)$
vector<point> p;
double cp(int l, int r) {
    if (l >= r) return DBL_MAX;
    int mid = (l + r) / 2;
    double d = min(cp(l, mid), cp(mid + 1, r));
    vector<point> strip;
    for (int i = l; i <= r; i++)
        if (fabs(p[i].x - p[mid].x) <= d)
            strip.push_back(p[i]);
    sort(strip.begin(), strip.end(), [](point a, point b){return a.y < b.y;});
    for (int i = 0; i < strip.size(); i++)
        for (int j = i+1; j < strip.size() && (strip[j].y - strip[i].y) <= d; j++)
            d = min(d, dist(strip[i], strip[j]));
    return d;
}