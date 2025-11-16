#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef long long ll;

// \textbf{Sieve of Eratosthenes}: $O(n \log \log n)$ sieve[i] = 0 if i prime, spf otherwise for fast fact
vi sieve(int n){
    vi sieve(n,0);
    for(int i = 2; i*i < n ; i++)
        if(!sieve[i])
            for(int j = i*i ; j <n ; j += i)
                if(!sieve[j]) sieve[j] = i;
    return sieve;
}
// \textbf{Fast exponentiation} $O(\log b)$: fast $a^b \bmod p$.
int modular_exp(int a, int b, int p){
    int res = 1;
    while(b > 0){
        if(b & 1) res = (1LL * a * res) % p;
        b = b >> 1;
        a = (1LL * a * a) % p;
    }
    return res;
}
// \textbf{Euler's $\varphi$}: Number of ints $\leq$ n coprime to n.
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
// \textbf{Extended Euclidean Algorithm} Solves  $ax + by = gcd(a,b)$.
ll eea(ll a, ll b, ll& x, ll& y) {
    ll xx = y = 0, yy = x = 1;
    while (b) {
        ll q = a / b, t = b; b = a%b; a = t;
        t = xx; xx = x - q*xx; x = t;
        t = yy; yy = y - q*yy; y = t;
    }
    return a; // Returns gcd(a,b)
}