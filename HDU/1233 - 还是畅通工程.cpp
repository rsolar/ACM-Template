#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 105

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

const int INF = 0x3f3f3f3f;
int mp[N][N], lowc[N];
bool vis[N];

int Prim(int cost[][N], int n) {
	int ans = 0;
	memset(vis, 0, sizeof(vis));
	vis[0] = true;
	for (int i = 1; i < n; i++) { lowc[i] = cost[0][i]; }
	for (int i = 1; i < n; i++) {
		int minc = INF, p = -1;
		for (int j = 0; j < n; j++) {
			if (!vis[j] && minc > lowc[j]) {
				minc = lowc[j];
				p = j;
			}
		}
		ans += minc;
		vis[p] = true;
		for (int j = 0; j < n; j++) {
			if (!vis[j] && lowc[j] > cost[p][j]) {
				lowc[j] = cost[p][j];
			}
		}
	}
	return ans;
}

int main() {
	int n, m, x, y, d;
	while (getInt(n), n) {
		m = (n * (n - 1)) >> 1;
		while (m--) {
			getInt(x); getInt(y); getInt(d);
			mp[x - 1][y - 1] = mp[y - 1][x - 1] = d;
		}
		printf("%d\n", Prim(mp, n));
	}
}
