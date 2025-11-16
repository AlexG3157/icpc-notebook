#include<bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

// FFT: in-place, invert=false for forward, true for inverse
// Input size must be power of two $O(n \log n)$
void fft(vector<complex<double>> &a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * M_PI / len * (invert ? -1 : 1);
        complex<double> wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            complex<double> w(1);
            for (int j = 0; j < len / 2; j++) {
                complex<double> u = a[i + j];
                complex<double> v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert) {
        for (auto &x : a) x /= n;
    }
}
// Multiply two polynomials, where a[i] is the coefficient of $x^i$
vi multiply(vi &a, vi &b) {
    vector<complex<double>> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1; while (n < a.size() + b.size()) n <<= 1;// next power of 2
    fa.resize(n); fb.resize(n);
    fft(fa, false); fft(fb, false);       // forward FFT
    for (int i = 0; i < n; i++) fa[i] *= fb[i]; // pointwise multiply
    fft(fa, true);                         // inverse FFT
    vi res(n);
    for (int i = 0; i < n; i++) res[i] = round(fa[i].real());
    return res;
}