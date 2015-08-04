#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 30

struct Edge {
	int u, v;
} e[N];
int n, m, ans, cnt[9], on[9], off[9];

void dfs(int p) {
	if (p == 0) { ans++; return; }
	if (on[e[p].u] && on[e[p].v]) {
		on[e[p].u]--; on[e[p].v]--;
		dfs(p - 1);
		on[e[p].u]++; on[e[p].v]++;
	}
	if (off[e[p].u] && off[e[p].v]) {
		off[e[p].u]--; off[e[p].v]--;
		dfs(p - 1);
		off[e[p].u]++; off[e[p].v]++;
	}
}

int main() {
	int T, x, y;
	bool flag;
	scanf("%d", &T);
	while (T--) {
		ans = 0;
		flag = false;
		memset(cnt, 0, sizeof(cnt));
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= m; i++) {
			scanf("%d %d", &x, &y);
			e[i].u = x; e[i].v = y;
			cnt[x]++; cnt[y]++;
		}
		for (int i = 1; i <= n; i++) {
			on[i] = off[i] = cnt[i] >> 1;
			if (cnt[i] & 1) { flag = true; }
		}
		if (!flag) { dfs(m); }
		printf("%d\n", ans);
	}
}
