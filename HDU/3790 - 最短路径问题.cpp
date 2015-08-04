#include <iostream>
#include <cstdio>
using namespace std;

#define N 1005
const int INF = 0x3f3f3f3f;
int n, m, dis[N][N], lowdis[N], cost[N][N], lowcost[N], pre[N];
bool vis[N];

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

void init(int n) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			dis[i][j] = cost[i][j] = INF;
		}
	}
}

void Dijkstra(int beg) {
	for (int i = 1; i <= n; i++) {
		lowdis[i] = lowcost[i] = INF;
		vis[i] = false;
		pre[i] = -1;
	}
	lowdis[beg] = lowcost[beg] = 0;
	for (int j = 1; j <= n; j++) {
		int k = -1, mind = INF, minc = INF;
		for (int i = 1; i <= n; i++) {
			if (!vis[i] && (lowdis[i] < mind || (lowdis[i] == mind && lowcost[i] < minc))) {
				mind = lowdis[i]; minc = lowcost[i];
				k = i;
			}
		}
		if (k == -1) { break; }
		vis[k] = true;
		for (int i = 1; i <= n; i++) {
			if (!vis[i] && (lowdis[k] + dis[k][i] < lowdis[i] || (lowdis[k] + dis[k][i] == lowdis[i] && lowcost[k] + cost[k][i] < lowcost[i]))) {
				lowdis[i] = lowdis[k] + dis[k][i]; lowcost[i] = lowcost[k] + cost[k][i];
				pre[i] = k;
			}
		}
	}
}

int main() {
	int x, y, d, p;
	while (getInt(n), getInt(m), n) {
		init(n);
		while (m--) {
			getInt(x); getInt(y); getInt(d); getInt(p);
			if ((dis[x][y] == INF && cost[x][y] == INF) || d < dis[x][y] || (d == dis[x][y] && p < cost[x][y])) {
				dis[x][y] = dis[y][x] = d; cost[x][y] = cost[y][x] = p;
			}
		}
		getInt(x); getInt(y);
		Dijkstra(x);
		printf("%d %d\n", lowdis[y], lowcost[y]);
	}
}
