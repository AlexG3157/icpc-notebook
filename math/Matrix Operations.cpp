#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> matrix;

// Performs matrix multiplication in $O(n^3)$. Watch out for overflow.
matrix mult(const matrix &a, matrix &b) {
	int i, j, k, m = a.size(), n = a[0].size(), p = b[0].size();
	matrix res = matrix(m, vi(p, 0));
	for (i = 0; i < m; i++)	for (j = 0; j < p; j++)
		for (k = 0; k < n; k++)
			res[i][j] += a[i][k] * b[k][j];
	return res;
}
// Calculates $a^p$ in $O(n^3 \log p)$. Watch out for overflow. Modifies matrix.
matrix pow(matrix &a, int p) {
	int l = a.size(), i;
	matrix b(l, vi(l, 0));
	for (i = 0; i < l; i++) b[i][i] = 1;
	while (p) {
		if (p & 1) {b = mult(b, a); p--;}	
		a = mult(a, a);
		p >>= 1;
	}
	return b;
}
// Gauss-Jordan on an augmented matrix, returns determinant, modifies matrix. $O(n^3)$
double gaussJordan(matrix &a, int &rank, int &augRank) {
    int n = a.size(), m = a[0].size() - 1; // n eqs, m vars
    double det = 1.0; rank = 0;
    for (int j = 0; j <= m; j++) {
        int pivotRow = -1;
        double maxVal = 0;
        for (int i = rank; i < n; i++)
            if (pivotRow < 0 || abs(a[i][j]) > maxVal) {
                maxVal = abs(a[i][j]);
                pivotRow = i;
            }
        if (maxVal > 1e-7) {
            double c = a[pivotRow][j];
            if (pivotRow != rank) det = -det;
            det *= c;
            for (int k = j; k <= m; k++) {
                swap(a[pivotRow][k], a[rank][k]);
                a[rank][k] /= c;
            }
            for (int i = rank + 1; i < n; i++) {
                c = a[i][j];
                for (int k = j; k <= m; k++)
                    a[i][k] -= c * a[rank][k];
            }
            if (j < m) rank++;
        }
    }
    augRank = rank;
    for (int i = rank; i < n; i++)
        if (abs(a[i][m]) > 1e-6) { augRank++; break; }
    if (rank != n) det = 0;

    return det;
}
// Solve Ax=b. Input:[A|b] (augmented matrix) $O(n^3)$. Modifies Matrix.
void solve(matrix &a, vi &solution) {
    int n = a.size(), m = a[0].size() - 1;
    solution.assign(m, 0.0);
    for (int i = n - 1; i >= 0; i--) {
        double c = a[i][m];
        for (int j = i + 1; j < m; j++)
            c -= a[i][j] * solution[j];
        solution[i] = c;
    }
}
