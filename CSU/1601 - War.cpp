#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 100005

template <class T>
inline bool getInt(T &x) {
	char c = 0;
	while (c < '0' || c > '9') { c = getchar(); };
	x = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
	return true;
}

struct Edge {
	int u, v;
} e[N];
int n, m, q, fa[N], d[N], ans[N];
bool des[N];

void init() {
	for (int i = 1; i <= n; i++) { fa[i] = i; }
	memset(des, 0, sizeof(des));
}

int findfa(int n) {
	return n == fa[n] ? n : fa[n] = findfa(fa[n]);
}

int main() {
	while (~scanf("%d%d", &n, &m)) {
		init();
		for (int i = 1; i <= m; i++) { getInt(e[i].u); getInt(e[i].v); }
		getInt(q);
		for (int i = 1; i <= q; i++) { getInt(d[i]); des[d[i]] = true; }
		int cur = n;
		for (int i = 1; i <= m; i++) {
			if (!des[i]) {
				int x = findfa(e[d[i]].u), y = findfa(e[d[i]].v);
				if (x != y) { fa[y] = x; cur--; }
			}
		}
		for (int i = q; i > 0; i--) {
			ans[i] = cur;
			int x = findfa(e[d[i]].u), y = findfa(e[d[i]].v);
			if (x != y) { fa[y] = x; cur--; }
		}
		for (int i = 1; i <= q; i++) {
			if (i != 1) { putchar(' '); }
			printf("%d", ans[i]);
		}
		putchar('\n');
	}
}
