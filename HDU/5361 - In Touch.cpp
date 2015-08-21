#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

typedef long long ll;
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

const ll INF = 0x3f3f3f3f3f3f;
int n, l[N], r[N], fa[N];
ll c[N], dis[N];
struct qnode {
	int v; ll c;
	qnode(int _v = 0, ll _c = 0): v(_v), c(_c) {}
	bool operator <(const qnode &r) const { return c > r.c; }
};

int findfa(int n) {
	return n == fa[n] ? n : fa[n] = findfa(fa[n]);
}

void unite(int x, int y) {
	x = findfa(x); y = findfa(y);
	if (x != y) { fa[x] = y; }
}

void Dijkstra(int start) {
	for (int i = 1; i <= n + 1; i++) { fa[i] = i; dis[i] = INF; }
	priority_queue<qnode> que;
	dis[start] = c[start];
	qnode p = {start, c[start]};
	que.push(p);
	while (!que.empty()) {
		p = que.top(); que.pop();
		int u = p.v;
		for (int v = max(u - r[u], 1), rr = u - l[u]; v <= rr; v++) {
			v = findfa(v);
			if (v > rr) { break; }
			if (dis[v] > dis[u] + c[v]) {
				dis[v] = dis[u] + c[v];
				que.push(qnode(v, dis[v]));
			}
			unite(v, v + 1);
		}
		for (int v = u + l[u], rr = min(u + r[u], n); v <= rr; v++) {
			v = findfa(v);
			if (v > rr) { break; }
			if (dis[v] > dis[u] + c[v]) {
				dis[v] = dis[u] + c[v];
				que.push(qnode(v, dis[v]));
			}
			unite(v, v + 1);
		}
	}
}

int main() {
	int T;
	getInt(T);
	while (T--) {
		getInt(n);
		for (int i = 1; i <= n; i++) { getInt(l[i]); }
		for (int i = 1; i <= n; i++) { getInt(r[i]); }
		for (int i = 1; i <= n; i++) { getInt(c[i]); }
		Dijkstra(1);
		for (int i = 1; i <= n; i++) {
			if (i != 1) { putchar(' '); }
			printf("%I64d", dis[i] == INF ? -1 : dis[i] - c[i]);
		}
		putchar('\n');
	}
}
