#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 2005

int fa[N], rnk[N];

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

int findfa(int n) {
	int t = fa[n];
	if (fa[n] != n) {
		fa[n] = findfa(fa[n]);
		rnk[n] = (rnk[n] + rnk[t]) & 1;
	}
	return fa[n];
}

void unite(int a, int b) {
	int x = findfa(a), y = findfa(b);
	if (x != y) {
		fa[x] = y;
		rnk[x] = (rnk[a] + rnk[b] + 1) & 1;
	}
}

int main() {
	char c;
	int T, C = 0, n, m, x, y;
	bool flag;
	getInt(T);
	while (++C <= T) {
		getInt(n); getInt(m);
		for (int i = 1; i <= n; i++) { fa[i] = i; }
		memset(rnk, 0, sizeof(rnk));
		flag = true;
		while (m--) {
			getInt(x); getInt(y);
			if (flag) {
				if (findfa(x) == findfa(y)) {
					if (rnk[x] == rnk[y]) { flag = false; }
				} else { unite(x, y); }
			}
		}
		printf("Scenario #%d:\n%suspicious bugs found!\n\n", C, (flag ? "No s" : "S"));
	}
}
