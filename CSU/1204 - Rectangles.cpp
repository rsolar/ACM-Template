#include <iostream>
#include <cstdio>
using namespace std;

typedef unsigned long long ull;

template <class T>
inline bool getInt(T &x) {
	char c; T sign = 1;
	if ((c = getchar()) == EOF) { return false; }
	while ((c < '0' || c > '9') && c != '-') { c = getchar(); };
	if (c == '-') { sign = -1; c = getchar(); }
	x = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
	x *= sign;
	return true;
}

int main() {
	int T;
	getInt(T);
	while (T--) {
		ull L, A, B;
		getInt(L); getInt(A); getInt(B);
		if (L & 1) { puts("0"); continue; }
		L >>= 1;
		ull LL = L >> 1, ans = LL, l, r, mid;
		if (L - 1 > B || LL * (LL + (L & 1)) < A) { puts("0"); continue; }
		l = 0; r = LL;
		while (l + 1 < r) {
			mid = (l + r) >> 1;
			if (mid * (L - mid) >= A) { r = mid; }
			else { l = mid; }
		}
		ans -= l;
		l = 1; r = LL + 1;
		while (l + 1 < r) {
			mid = (l + r) >> 1;
			if (mid * (L - mid) <= B) { l = mid; }
			else { r = mid; }
		}
		ans -= (r > LL ? 0 : LL - r + 1);
		printf("%llu\n", ans);
	}
}
