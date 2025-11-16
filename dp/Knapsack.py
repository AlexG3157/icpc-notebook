# n items, each with value $v_i$ and weight $w_i$. Max total weight $W$.
# DP formula: dp[i][j] max value using i items, where max total weight is j.
# $\mathrm{dp}[i][w]=\max(\mathrm{dp}[i-1][w],\mathrm{dp}[i-1][w-w_i]+v_i)$.\\

#Space optimized version $O(n \times W)$
def knapsack(W, val, wt):
    dp = [0] * (W + 1)
    for i in range(1, len(wt) + 1):
        for j in range(W, wt[i - 1] - 1, -1):
            dp[j] = max(dp[j], dp[j - wt[i - 1]] + val[i - 1])
    return dp[W]