#include <iostream>
#include <cstdio>
using namespace std;

typedef long long ll;
#define N 500005

inline void getInt(int &x) {
	char c = 0; int sign = 1;
	while ((c < '0' || c > '9') && c != '-') { c = getchar(); };
	if (c == '-') { sign = -1; c = getchar(); }
	x = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
	x *= sign;
}

ll a[N];

int main() {
	int T, n, m, z, l;
	getInt(T);
	while (T--) {
		getInt(n); getInt(m); getInt(z); getInt(l);
		for (int i = 2; i <= n; i++) { a[i] = (a[i - 1] * m + z) % l; }
		ll ans = 0;
		for (int i = 2; i <= n; i++) { ans ^= (a[i] << 1LL); }
		printf("%I64d\n", ans);
	}
}
