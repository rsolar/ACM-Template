#include <cstdio>
#include <cstring>
using namespace std;

#define N 40005
#define M 10005

struct Node {
	int v, l, next;
} e[N << 1], q[M << 1];
int fa[N], he[N], hq[N], ecnt, qcnt, dis[N], ans[N];
bool vis[N];

template <class T> inline bool getInt(T &x) {
	char c = 0; T sign = 1;
	if ((c = getchar()) == EOF) { return false; }
	while ((c < '0' || c > '9') && c != '-') { c = getchar(); };
	if (c == '-') { sign = -1; c = getchar(); }
	x = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
	x *= sign;
	return true;
}

void init(int n) {
	ecnt = qcnt = 0;
	memset(vis, 0, sizeof(vis));
	memset(he, -1, sizeof(he));
	memset(hq, -1, sizeof(hq));
	for (int i = 1; i <= n; i++) { fa[i] = i; }
}

int findfa(int n) {
	return n == fa[n] ? n : fa[n] = findfa(fa[n]);
}

void addedge(int u, int v, int l) {
	e[ecnt].v = v; e[ecnt].l = l; e[ecnt].next = he[u]; he[u] = ecnt++;
	e[ecnt].v = u; e[ecnt].l = l; e[ecnt].next = he[v]; he[v] = ecnt++;
}

void addquery(int u, int v, int l) {
	q[qcnt].v = v; q[qcnt].l = l; q[qcnt].next = hq[u]; hq[u] = qcnt++;
	q[qcnt].v = u; q[qcnt].l = l; q[qcnt].next = hq[v]; hq[v] = qcnt++;
}

void tarjan(int u, int l) {
	dis[u] = l; vis[u] = true;
	for (int i = he[u]; ~i; i = e[i].next) {
		if (!vis[e[i].v]) {
			tarjan(e[i].v, l + e[i].l);
			fa[e[i].v] = u;
		}
	}
	for (int i = hq[u]; ~i; i = q[i].next) {
		if (vis[q[i].v]) {
			ans[q[i].l] = dis[u] + dis[q[i].v] - (dis[findfa(q[i].v)] << 1);
		}
	}
}

int main() {
	int n, k, u, v, l;
	getInt(n); getInt(k);
	init(n);
	while (k--) {
		getInt(u); getInt(v); getInt(l);
		addedge(u, v, l);
	}
	getInt(k);
	for (int i = 1; i <= k; i++) {
		getInt(u); getInt(v);
		addquery(u, v, i);
	}
	tarjan(1, 0);
	for (int i = 1; i <= k; i++) {
		printf("%d\n", ans[i]);
	}
}
