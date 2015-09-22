#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define N 5

ll x, p;

#define fabs(x) ((x)>=0?(x):-(x))
#define isZero(x) (fabs(x)<1e-10)

template <class T> struct Matrix {
  int r, c;
  T m[N][N];
  void init() {
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        m[i][j] = 0;
      }
    }
  }
  Matrix(int _r = N, int _c = N): r(_r), c(_c) { init(); }
  void e() {
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        m[i][j] = !(i ^ j);
      }
    }
  }
  Matrix &operator=(const Matrix &mat) {
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        m[i][j] = mat.m[i][j];
      }
    }
    return *this;
  }
  Matrix operator*(const Matrix &mat) {
    Matrix rt(r, mat.c);
    for (int i = 0; i < r; i++) {
      for (int k = 0; k < c; k++) {
        if (!isZero(m[i][k])) {
          for (int j = 0; j < mat.c; j++) {
            rt.m[i][j] = (rt.m[i][j] + m[i][k] * mat.m[k][j]) % p;
          }
        }
      }
    }
    return rt;
  }
  Matrix operator^(ll n) {
    Matrix rt(r, c), base(r, c); rt.e(); base = *this;
    while (n) {
      if (n & 1) { rt = rt * base; }
      base = base * base;
      n >>= 1;
    }
    return rt;
  }
  void print() {
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        printf("%I64d ", m[i][j]);
      }
      putchar('\n');
    }
  }
};

ll powMod(ll a, ll b, ll m) {
  ll r = 1; a %= m;
  while (b) {
    if (b & 1) { r = r * a % m; }
    a = a * a % m;
    b >>= 1;
  }
  return r;
}

int main() {
  Matrix<ll> t(2, 2);
  int C = 0, T;
  scanf("%d", &T);
  while (++C <= T) {
    scanf("%I64d %I64d", &x, &p);
    t.m[0][0] = 5; t.m[0][1] = 12; t.m[1][0] = 2; t.m[1][1] = 5;
    t = t ^ powMod(2, x, (p - 1) * (p + 1));
    ll ans = ((t.m[0][0] * 5 + t.m[0][1] * 2) * 2 - 1) % p;
    printf("Case #%d: %I64d\n", C, ans);
  }
}
