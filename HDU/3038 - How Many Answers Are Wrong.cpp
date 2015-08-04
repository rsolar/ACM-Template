#include <iostream>
#include <cstdio>
using namespace std;

#define N 200005

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

int fa[N], sum[N], ans;

void init(int n) {
	ans = 0;
	for (int i = 0; i <= n; i++) { fa[i] = i; sum[i] = 0; }
}

int findfa(int n) {
	if (n == fa[n]) { return n; }
	int t = findfa(fa[n]);
	sum[n] += sum[fa[n]];
	return fa[n] = t;
}

bool unite(int l, int r, int s) {
	int x = findfa(l), y = findfa(r);
	if (x == y) { return (sum[l] - sum[r] != s); }
	fa[x] = y;
	sum[x] = sum[r] - sum[l] + s;
	return false;
}

int main() {
	int n, q, l, r, s;
	while (getInt(n)) {
		getInt(q);
		init(n);
		for (int i = 0; i < q; i++) {
			getInt(l); getInt(r); getInt(s);
			ans += unite(l - 1, r, s);
		}
		printf("%d\n", ans);
	}
}
