#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
// Number of ints $\leq$ n coprime to n (c.f. sieve for primes).
int phi(int n, vi& primes) {
    int res = n;
    for (int p : primes) {
        if (1LL * p * p > n) break;
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            res -= res / p;
        }
    }
    if (n > 1) res -= res / n;
    return res;
}