#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

#define N 1005

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

int n;
bool vis[N];
int rnk[N];
bool flag;
vector<int> e[N];

void dfs(int u, int cnt) {
	if (cnt == n) { flag = true; return; }
	for (size_t i = 0; i < e[u].size() && !flag; i++) {
		int v = e[u][i];
		if (!vis[v]) {
			vis[v] = true;
			dfs(v, cnt + 1);
			vis[v] = false;
		}
	}
}

int main() {
	int u, v;
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; i++) { e[i].clear(); }
		memset(rnk, 0, sizeof(rnk));
		for (int i = 1; i <= n; i++) {
			getInt(u); getInt(v);
			if (u != v) {
				e[u].push_back(v); e[v].push_back(u);
				rnk[u]++; rnk[v]++;
			}
		}
		int u = 1, cnt = 0;
		for (int i = 1; i <= n; i++) {
			if (rnk[i] == 1) { cnt++; u = i; }
		}
		if (cnt > 2) { puts("NO"); continue; }
		flag = false;
		memset(vis, 0, sizeof(vis));
		vis[u] = true;
		dfs(u, 1);
		puts(flag ? "YES" : "NO");
	}
}
