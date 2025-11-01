#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

// $O(n \log \log n)$ sieve[i] = 0 if i prime, spf otherwise for fast fact
vi sieve(int n){
    vi sieve(n,0);
    for(int i = 2; i*i < n ; i++)
        if(!sieve[i])
            for(int j = i*i ; j <n ; j += i)
                if(!sieve[j]) sieve[j] = i;
    return sieve;
}