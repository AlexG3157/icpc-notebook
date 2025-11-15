# SuffixArray i.e. starting positions of suffixes in lexicographic order. $O(n\log ^2 n)$
def build_sa(s):
    n = len(s)
    sa = list(range(n))
    rank = [ord(ch) for ch in s]    # initial ranks by 1 char
    k = 1
    while k < n: # sort by first k chars 
        sa.sort(key=lambda x: (rank[x], rank[x+k] if x+k < n else -1))
        temp = [0]*n
        temp[sa[0]] = 0
        for i in range(1, n):
            prev = sa[i-1]
            cur  = sa[i]
            prev_key = (rank[prev], rank[prev+k] if prev+k < n else -1)
            cur_key  = (rank[cur],  rank[cur+k]  if cur+k < n else -1)
            temp[cur] = temp[prev] + (cur_key > prev_key)
        rank = temp
        if rank[sa[-1]] == n-1: break  # all ranks distinct
        k <<= 1
    return sa 
# Longest Common Prefix between suffixes sa[i] and sa[i+1] $O(n)$
def build_lcp(s, sa):
    n = len(s)
    rank = [0]*n
    for i in range(n): rank[sa[i]] = i
    lcp = [0]*n
    k = 0
    for i in range(n):
        if rank[i] == n-1: k = 0; continue
        j = sa[rank[i] + 1]
        while i+k < n and j+k < n and s[i+k] == s[j+k]:
            k += 1
        lcp[rank[i]] = k
        if k: k -= 1
    return lcp 

# Longest Repeated Substring = max LCP over all adjacent suffixes.
def lrs(s):
    sa = build_sa(s)
    lcp = build_lcp(s, sa)
    idx = lcp.index(max(lcp))
    return (lcp[idx], idx)  # (length, position in SA)
# Finds all occurrences of pat in s via binary search on the SA.
# Returns [L, R]: all SA positions where suffix starts with pat.
def search(s, pat, sa):
    n, m = len(s), len(pat)
    l, r = 0, n-1
    while l <= r:
        mid = (l+r)//2
        if s[sa[mid]:sa[mid]+m] < pat: l = mid+1
        else: r = mid-1
    start = l
    l, r = 0, n-1
    while l <= r:
        mid = (l+r)//2
        if s[sa[mid]:sa[mid]+m] <= pat: l = mid+1
        else: r = mid-1
    return (start, r) if start <= r else (-1, -1)
# Longest Common Substring between two strings.
# Build SA/LCP on s1\#s2\$, then the LCS occurs between adjacent
# suffixes coming from different strings.
def lcs(s1, s2):
    s = s1 + '#' + s2 + '$'
    sa = build_sa(s)
    lcp = build_lcp(s, sa)
    idx, max_len = 0, 0
    for i in range(1, len(s)):
        a = sa[i] < len(s1)
        b = sa[i-1] < len(s1)
        if a != b and lcp[i] > max_len:
            max_len, idx = lcp[i], i
    return (max_len, idx)
