# Longest palindromic substring $O(n)$. Max of P corresponds to len(LPS)
def manacher(s):
    T = '#' + '#'.join(s) + '#' # handle even-length, remember to remove after
    n = len(T)
    P = [0]*n          # P[i] = radius of palindrome centered at i
    C = R = 0          # current center, right boundary
    for i in range(n):
        mirr = 2*C - i
        if i < R: P[i] = min(R-i, P[mirr])  # use symmetry
        while i+P[i]+1 < n and i-P[i]-1 >= 0 and T[i+P[i]+1] == T[i-P[i]-1]:
            P[i] += 1 # attempt to expand palindrome at i
        if i + P[i] > R: # update center and right boundary
            C, R = i, i + P[i]
