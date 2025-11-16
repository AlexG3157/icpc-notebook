#$\ell_i$: LIS length ending at $i$. 
#DP formula : $\ell_i = 1 + \max_{\substack{1 \le j < i \\ a_j < a_i}}$ (or 1 if none). 
#Ans $=\max_i \ell_i$. Predecessor $p_i = \arg\max_{\substack{1 \le j < i \\ a_j < a_i}} \ell_j$.\\
#$O(n^2)$
def LIS(arr):
    n = len(arr) ; lis = [1] * n
    for i in range(1, n):
        for prev in range(0, i):
            if arr[i] > arr[prev]:
                lis[i] = max(lis[i], lis[prev] + 1)
    return max(lis)
#Note that $O(n \log n)$ is possible with BS
def LIS_BS(arr):
    n = len(arr) ; ans = [] ; ans.append(arr[0])
    for i in range(1, n):
        if arr[i] > ans[-1]:
            ans.append(arr[i])
        else:
            low = 0
            high = len(ans) - 1
            while low < high:
                mid = low + (high - low) // 2
                if ans[mid] < arr[i]:
                    low = mid + 1
                else:
                    high = mid
            ans[low] = arr[i]
    return len(ans)
