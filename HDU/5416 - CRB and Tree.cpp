#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

typedef long long ll;
#define N 100005

template<class T> inline bool getInt(T &x) {
	char c = 0; T sign = 1;
	if ((c = getchar()) == EOF) { return false; }
	while ((c < '0' || c > '9') && c != '-') { c = getchar(); };
	if (c == '-') { sign = -1; c = getchar(); }
	x = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
	x *= sign;
	return true;
}

struct Edge {
	int v, w;
	Edge(int _v, int _w): v(_v), w(_w) {}
};
int n, q, a[N], cnt[N + (N >> 1)];
vector<Edge> e[N];

void dfs(int u, int pre) {
	for (size_t i = 0; i < e[u].size(); i++) {
		int v = e[u][i].v, w = e[u][i].w;
		if (pre != v) {
			a[v] = a[u] ^ w;
			dfs(v, u);
		}
	}
}

int main() {
	int T, u, v, w;
	getInt(T);
	while (T--) {
		memset(cnt, 0, sizeof(cnt));
		getInt(n);
		for (int i = 1; i <= n; i++) { e[i].clear(); }
		for (int i = 1; i < n; i++) {
			getInt(u); getInt(v); getInt(w);
			e[u].push_back(Edge(v, w)); e[v].push_back(Edge(u, w));
		}
		a[1] = 0;
		dfs(1, -1);
		for (int i = 1; i <= n; i++) { cnt[a[i]]++; }
		getInt(q);
		while (q--) {
			getInt(u);
			ll ans = 0;
			for (int i = 1; i <= n; i++) { ans += cnt[a[i] ^ u]; }
			if (u == 0) { ans = ((ans - n) >> 1) + n; }
			else { ans >>= 1; }
			printf("%I64d\n", ans);
		}
	}
}
