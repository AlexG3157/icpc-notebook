# Solve Ax = b using Gaussian elimination $O(n^3)$
def solve_gauss(a, b):
    n = len(a)
    a = [row[:] + [b[i]] for i, row in enumerate(a)]
    for i in range(n):
        pivot_row = max(range(i, n), key=lambda r: abs(a[r][i]))
        if abs(a[pivot_row][i]) < 1e-12:
            return None 
        a[i], a[pivot_row] = a[pivot_row], a[i]
        pivot = a[i][i]
        for j in range(i, n + 1):
            a[i][j] /= pivot
        for r in range(i + 1, n):
            factor = a[r][i]
            for c in range(i, n + 1):
                a[r][c] -= factor * a[i][c]
    x = [0] * n
    for i in range(n - 1, -1, -1):
        x[i] = a[i][n]
        for j in range(i + 1, n):
            x[i] -= a[i][j] * x[j]
    return x
# Maximizes $c^T x$ s.t. $Ax \leq b, x \geq 0$
def simplex(A, b, c):
    m, n = len(A), len(c)
    tableau = []
    for i in range(m):
        tableau.append(A[i][:] + [1 if j == i else 0 for j in range(m)] + [b[i]])
    tableau.append([-c_j for c_j in c] + [0] * (m + 1))
    basic = list(range(n, n + m))
    while True:
        entering = -1
        for j in range(n + m):
            if tableau[-1][j] < -1e-12:
                if entering == -1 or tableau[-1][j] < tableau[-1][entering]:
                    entering = j
        if entering == -1:  # Optimal solution found
            break
        leaving = -1
        min_ratio = float('inf')
        for i in range(m):
            if tableau[i][entering] > 1e-12:
                ratio = tableau[i][-1] / tableau[i][entering]
                if ratio < min_ratio - 1e-12:
                    min_ratio = ratio
                    leaving = i
        if leaving == -1:  # Unbounded problm
            return None, float('inf')
        pivot = tableau[leaving][entering]
        for j in range(n + m + 1):
            tableau[leaving][j] /= pivot
        for i in range(m + 1):
            if i != leaving:
                factor = tableau[i][entering]
                for j in range(n + m + 1):
                    tableau[i][j] -= factor * tableau[leaving][j]
        basic[leaving] = entering
    x = [0] * n
    for i in range(m):
        if basic[i] < n:
            x[basic[i]] = tableau[i][-1]
    return x, tableau[-1][-1]