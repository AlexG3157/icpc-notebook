# Sieve of Gries-Misra $O(n)$. Produces prime list and SPF array
def gries_misra(n):
    primes = []
    factor = [0] * n
    for x in range(2, n):
        if not factor[x]:      # no factor found
            factor[x] = x      # meaning x is prime
            primes.append(x)
        for p in primes:       # loop over primes found so far
            if p > factor[x] or p * x >= n:
                break
            factor[p * x] = p  # p is the smallest factor of p * x
    return primes, factor
# Returns (u,v) s.t. $au +bv = gcd(a,b)$ in $O(\log a + \log b)$
def bezout(a, b):
    if b == 0:
        return (1, 0)
    u, v = bezout(b, a % b)
    return (v, u - (a // b) * v)
# Inverse of a in $\mathbb{Z}_p$ in $O(\log a + \log p)$
def inv(a, p):
    return bezout(a, p)[0] % p
#$\binom{n}{k} \mod p$ in $O(k)$
def binom_modulo(n, k, p):
    prod = 1
    for i in range(k):
        prod = (prod * (n - i) * inv(i + 1, p)) % p
    return prod
# Constructs an arithmetic expression tree. Input: tokens e.g. ["1", "+", "2"]
def arithm_expr_parse(tokens):
    vals, ops = [], []
    PRIO = {'+':1, '-':1, '*':2, '/':2, '(':0}
    for t in tokens:
        if t in PRIO:
            while ops and PRIO[ops[-1]] >= PRIO[t] and t != '(':
                vals.append((vals.pop(-2), ops.pop(), vals.pop()))
            ops.append(t)
        elif t == ')':
            while ops[-1] != '(':
                vals.append((vals.pop(-2), ops.pop(), vals.pop()))
            ops.pop()
        else:
            vals.append(int(t) if t.isdigit() else t)
    while ops:
        vals.append((vals.pop(-2), ops.pop(), vals.pop()))
    return vals[0]