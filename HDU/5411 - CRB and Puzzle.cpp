#include <iostream>
#include <cstdio>
using namespace std;

#define N 55
#define M 2015

template<class T> inline bool getInt(T &x) {
	char c = 0; T sign = 1;
	if ((c = getchar()) == EOF) { return false; }
	while ((c < '0' || c > '9') && c != '-') { c = getchar(); };
	if (c == '-') { sign = -1; c = getchar(); }
	x = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
	x *= sign;
	return true;
}

#define fabs(x) ((x)>=0?(x):-(x))
#define isZero(x) (fabs(x)<1e-10)
#define type_m int

struct Matrix {
	int r, c;
	type_m m[N][N];
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
						rt.m[i][j] = (rt.m[i][j] + m[i][k] * mat.m[k][j]) % M;
					}
				}
			}
		}
		return rt;
	}
	Matrix operator^(int n) {
		Matrix rt(r, c), base(r, c); rt.e(); base = *this;
		while (n) {
			if (n & 1) { rt = rt * base; }
			base = base * base;
			n >>= 1;
		}
		return rt;
	}
};

int main() {
	int T, n, m, k, x;
	getInt(T);
	while (T--) {
		Matrix a;
		getInt(n); getInt(m);
		for (int i = 0; i < n; i++) {
			getInt(k);
			while (k--) { getInt(x); a.m[i][--x] = 1; }
		}
		for (int i = 0; i <= n; i++) { a.m[n][i] = 1; }
		a = a ^ m;
		int ans = 0;
		for (int i = 0; i <= n; i++) { ans += a.m[n][i]; }
		printf("%d\n", ans % M);
	}
}
