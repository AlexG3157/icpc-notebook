# Search for a pattern within a text in $O(n+m)$, where n is the size of the text and m the length of the pattern.
# Length of the longest proper prefix which is also a suffix of the substring ending at that position.
def constructLps(pat, lps):
    len_ = 0 ; m = len(pat) ; lps[0] = 0 ; i = 1
    while i < m:
        if pat[i] == pat[len_]:
            len_ += 1
            lps[i] = len_
            i += 1
        else:
            if len_ != 0:
                len_ = lps[len_ - 1]
            else:
                lps[i] = 0
                i += 1
def search(pat, txt):
    n = len(txt) ; m = len(pat) ; lps = [0] * m ; res = []
    constructLps(pat, lps)
    i = 0 ; j = 0
    while i < n:
        
        if txt[i] == pat[j]:
            i += 1# If characters match, move both pointers forward
            j += 1
            if j == m: #found
                res.append(i - j)
                j = lps[j - 1] # Use LPS to skip unnecessary comparisons
        else: # mismatch
            if j != 0:
                j = lps[j - 1] # Use LPS to skip unnecessary comparisons
            else:
                i += 1
    return res 
