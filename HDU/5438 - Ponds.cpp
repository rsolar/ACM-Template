#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define N 10005
#define M 100005

int n, m, deg[N];
vector<int> e[N];
struct Edge {
	int u, v;
} E[M];
int fa[N], rnk[N]; ll sum[N];

void init(int n) {
	memset(deg, 0, sizeof(deg));
	for (int i = 1; i <= n; i++) { fa[i] = i; rnk[i] = 1; e[i].clear(); }
}

int findfa(int n) {
	return n == fa[n] ? n : fa[n] = findfa(fa[n]);
}

inline void unite(int x, int y) {
	x = findfa(x); y = findfa(y);
	if (x != y) {
		fa[y] = x;
		rnk[x] += rnk[y];
		sum[x] += sum[y];
	}
}

int main() {
	int u, v;
	int C = 0, T;
	scanf("%d", &T);
	while (++C <= T) {
		scanf("%d %d", &n, &m);
		init(n);
		for (int i = 1; i <= n; i++) {
			scanf("%I64d", &sum[i]);
		}
		for (int i = 1; i <= m; i++) {
			scanf("%d %d", &u, &v);
			if (u > v) { swap(u, v); }
			E[i].u = u; E[i].v = v;
			e[u].push_back(v); e[v].push_back(u);
			deg[u]++; deg[v]++;
		}
		queue<int> que;
		for (int i = 1; i <= n; i++) {
			if (deg[i] == 1) {
				que.push(i);
				deg[i] = 0;
			}
		}
		while (!que.empty()) {
			int u = que.front(); que.pop();
			for (size_t i = 0; i < e[u].size(); i++) {
				int v = e[u][i];
				deg[v]--;
				if (deg[v] == 1) {
					que.push(v);
					deg[v] = 0;
				}
			}
		}
		for (int i = 1; i <= m; i++) {
			u = E[i].u; v = E[i].v;
			if (deg[u] > 0 && deg[v] > 0) {
				unite(u, v);
			}
		}
		ll ans = 0;
		for (int i = 1; i <= n; i++) {
			if (rnk[i] > 1 && fa[i] == i && (rnk[i] & 1)) {
				ans += sum[i];
			}
		}
		printf("%I64d\n", ans);
	}
}
