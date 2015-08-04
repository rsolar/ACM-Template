#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;

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

map<int, int> mp;
int n, nn, a[N], b[N], c[N << 1], fa[N], rnk[N], ans;

void init() {
	ans = 1;
	mp.clear();
	for (int i = 0; i <= n; i++) {
		fa[i] = i; rnk[i] = 1;
	}
}

inline int findfa(int n) {
	return n == fa[n] ? n : fa[n] = findfa(fa[n]);
}

void unite(int a, int b) {
	a = findfa(a); b = findfa(b);
	if (a != b) {
		fa[b] = a; rnk[a] += rnk[b];
		ans = max(ans, rnk[a]);
	}
}

int main() {
	while (getInt(n)) {
		init();
		for (int i = 0; i < n; i++) {
			getInt(a[i]); getInt(b[i]);
			c[i << 1] = a[i];
			c[(i << 1) + 1] = b[i];
		}
		sort(c, c + (n << 1));
		nn = unique(c, c + (n << 1)) - c;
		for (int i = 0; i < nn; i++) { mp[c[i]] = i; }
		for (int i = 0; i < n; i++) {
			unite(mp[a[i]], mp[b[i]]);
		}
		printf("%d\n", ans);
	}
}
