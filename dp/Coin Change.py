# Given coins $c_1,\ldots,c_k$ and a sum $S$:\\
# \textbf{Min coins to make $S$:} 
# DP Formula: $\mathrm{dp}[x]$: min coins to make $x$, $\mathrm{dp}[0]=0$.
# $\mathrm{dp}[x]=\min_{c_i\le x}(\mathrm{dp}[x-c_i]+1)$.
# Ans $=\mathrm{dp}[S]$.\\

# \textbf{Number of ways to make $S$:} 
# DP formula: $\mathrm{dp}[x]$: \#ways to make $x$, $\mathrm{dp}[0]=1$.
# $\mathrm{dp}[x]=\sum_{c_i\le x}\mathrm{dp}[x-c_i]$.
# Ans $=\mathrm{dp}[S]$.\\

# Number of ways to make $S$, $O(n \times \mathrm{sum})$
def count(coins, s):
    n = len(coins) ; dp = [0] * (s + 1) ; dp[0] = 1
    for i in range(n):
        for j in range(coins[i], s + 1):
            dp[j] += dp[j - coins[i]]
    return dp[s]