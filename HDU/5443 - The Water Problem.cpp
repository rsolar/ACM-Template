#include <bits/stdc++.h>
using namespace std;

#define N 1005

int n;

template<typename T = int> struct BIT {
	T A[N];
	int lowbit(int x) { return x & (-x); }
	void init() {
		memset(A, 0, sizeof(A));
	}
	T num[N];
	void modify(int x, T v) {
		num[x] = v;
		for (int i = x; i <= n; i += lowbit(i)) {
			A[i] = max(A[i], v);
			for (int j = 1; j < lowbit(i); j <<= 1) {
				A[i] = max(A[i], A[i - j]);
			}
		}
	}
	T query(int l, int r) {
		int ret = num[r];
		while (true) {
			ret = max(ret, num[r]);
			if (l == r) { break; }
			for (r -= 1; r - l >= lowbit(r); r -= lowbit(r)) { ret = max(ret, A[r]); }
		}
		return ret;
	}
};
BIT<int> bit;

int main() {
	int C = 0, T, q, x, y;
	scanf("%d", &T);
	while (++C <= T) {
		bit.init();
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &x);
			bit.modify(i, x);
		}
		scanf("%d", &q);
		while (q--) {
			scanf("%d %d", &x, &y);
			printf("%d\n", bit.query(x, y));
		}
	}
}
