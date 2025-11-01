#include <bits/stdc++.h>

using namespace std;

//$O(\log b)$: fast $a^b \bmod p$.
int modular_exp(int a, int b, int p){
    int res = 1;
    while(b > 0){
        if(b & 1) res = (1LL * a * res) % p;
        b = b >> 1;
        a = (1LL * a * a) % p;
    }
    return res;
}