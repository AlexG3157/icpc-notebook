class Fenwick:
    def __init__(self, t):
        self.s = [0] * (len(t) + 1) # create internal storage
        for a, v in enumerate(t):
            self.add(a, v) # initialize
    def prefixSum(self, a):
        i = a + 1 # internal index starts at 1
        total = 0
        while i > 0: # loops over neighbors
            total += self.s[i] # cumulative sum
            i -= (i & -i) # left neighbor
        return total
    def intervalSum(self, a, b):
        return self.prefixSum(b) - self.prefixSum(a-1)
    def add(self, a, val):
        i = a + 1 # internal index starts at 1
        while i < len(self.s): # loops over parents
            self.s[i] += val # update node
            i += (i & -i) # parent