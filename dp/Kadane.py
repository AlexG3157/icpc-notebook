# Given an array $a_1,\ldots,a_n$, find $\max_{\substack{1 \leq i \leq j \leq n}} \sum_{k+i}^j a_i$ \\
# DP formula: $\mathrm{dp}_i$: max sum of subarray ending at $i$, $\mathrm{dp}_i = \max(a_i, \mathrm{dp}_{i-1}+a_i)$, 
# Ans $=\max_i \mathrm{dp}_i$.\\
# Kadane 1D $O(n)$
def kadane1D(arr):
    maxSum = arr[0] ; DP = arr[0]
    for i in range(1, len(arr)):
        DP = max(DP + arr[i], arr[i])
        maxSum = max(maxSum, DP)
    return maxSum

#2D-version :  For $r_1\le r_2$: $\text{colSum}[c]=\sum_{r=r_1}^{r_2}A_{r,c}$, 
# $\text{maxSum} = \max(\text{maxSum}, \text{Kadane1D}(\text{colSum}))$.\\
# Kadane 2D $O(n^3)$
def kadane2D(mat):
    rows = len(mat) ; cols = len(mat[0]) ; maxSum = float('-inf') ; temp = [0] * rows
    for left in range(cols):
        temp = [0] * rows
        for right in range(left, cols):
            for row in range(rows):
                temp[row] += mat[row][right]
            sumValue = kadane1D(temp)
            maxSum = max(maxSum, sumValue)
    return maxSum
