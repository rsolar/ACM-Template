#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 2001

int fa[N], rnk[N];

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
	scanf("%d", &T);
	while (T--) {
		while ((c = getchar()) < '0' || c > '9');
		n = c - '0';
		while ((c = getchar()) >= '0' && c <= '9') { n = n * 10 + c - '0'; }
		while ((c = getchar()) < '0' || c > '9');
		m = c - '0';
		while ((c = getchar()) >= '0' && c <= '9') { m = m * 10 + c - '0'; }
		for (int i = 1; i <= n; i++) {
			fa[i] = i;
		}
		memset(rnk, 0, sizeof(rnk));
		flag = true;
		while (m--) {
			while ((c = getchar()) < '0' || c > '9');
			x = c - '0';
			while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
			while ((c = getchar()) < '0' || c > '9');
			y = c - '0';
			while ((c = getchar()) >= '0' && c <= '9') { y = y * 10 + c - '0'; }
			if (flag) {
				if (findfa(x) == findfa(y)) {
					if (rnk[x] == rnk[y]) {
						flag = false;
					}
				} else {
					unite(x, y);
				}
			}
		}
		printf("Scenario #%d:\n%suspicious bugs found!\n\n", ++C, (flag ? "No s" : "S"));
	}
}
