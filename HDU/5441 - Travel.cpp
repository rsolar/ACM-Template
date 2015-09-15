#include <bits/stdc++.h>
using namespace std;

#define N 20005
#define M 100005
#define Q 5005

struct Node {
	int u, v, cost;
	bool operator<(const Node obj) const { return cost < obj.cost; }
} e[M];

int n, m, q, crt, fa[N], cnt[N], query1[Q], query2[Q], ans[M];

inline int calc(int n) {
	return (n - 1) * n;
}

void init(int n) {
	for (int i = 1; i <= n; i++) { fa[i] = i; cnt[i] = 1; }
}

int findfa(int n) {
	return n == fa[n] ? n : fa[n] = findfa(fa[n]);
}

inline void unite(int x, int y) {
	x = findfa(x); y = findfa(y);
	if (x != y) {
		fa[y] = x;
		crt -= calc(cnt[x]) + calc(cnt[y]);
		cnt[x] += cnt[y];
		crt += calc(cnt[x]);
	}
}

int main() {
	int C = 0, T;
	scanf("%d", &T);
	while (++C <= T) {
		scanf("%d %d %d", &n, &m, &q);
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &e[i].u, &e[i].v, &e[i].cost);
		}
		sort(e, e + m);
		for (int i = 0; i < q; i++) {
			scanf("%d", &query1[i]); query2[i] = query1[i];
		}
		sort(query1, query1 + q);
		init(n);
		crt = 0;
		for (int i = 0, pos = 0; i < q; i++) {
			while (pos < m && e[pos].cost <= query1[i]) {
				unite(e[pos].u, e[pos].v); pos++;
			}
			ans[query1[i]] = crt;
		}
		for (int i = 0; i < q; i++) {
			printf("%d\n", ans[query2[i]]);
		}
	}
}
