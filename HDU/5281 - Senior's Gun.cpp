#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;
#define N 100005

template <class T>
inline bool getInt(T &x) {
	char c = 0; T sign = 1;
	if ((c = getchar()) == EOF) { return false; }
	while ((c < '0' || c > '9') && c != '-') { c = getchar(); };
	if (c == '-') { sign = -1; c = getchar(); }
	x = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
	x *= sign;
	return true;
}

int a[N], b[N];

bool cmp(int a, int b) {
	return a > b;
}

int main() {
	int T, n, m;
	getInt(T);
	while (T--) {
		ll ans = 0;
		getInt(n); getInt(m);
		for (int i = 0; i < n; i++) { getInt(a[i]); }
		for (int i = 0; i < m; i++) { getInt(b[i]); }
		sort(a, a + n, cmp);
		sort(b, b + m);
		for (int i = 0; i < n && i < m && a[i] > b[i]; i++) {
			ans += a[i] - b[i];
		}
		printf("%I64d\n", ans);
	}
}
