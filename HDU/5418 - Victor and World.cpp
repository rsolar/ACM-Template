#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 20

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

#define INF 0x3f3f3f3f
int n, m, dis[N][N];
int dp[1 << 16][N];

int main() {
	int T, u, v, w;
	getInt(T);
	while (T--) {
		getInt(n); getInt(m);
		memset(dis, 0x3f, sizeof(dis));
		memset(dp, 0x3f, sizeof(dp));
		for (int i = 0; i < n; i++) { dis[i][i] = 0; }
		for (int i = 0; i < m; i++) {
			getInt(u); getInt(v); getInt(w);
			if (dis[--u][--v] > w) { dis[u][v] = dis[v][u] = w; }
		}
		for (int k = 0; k < n; k++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (dis[i][k] + dis[k][j] < dis[i][j]) {
						dis[i][j] = dis[i][k] + dis[k][j];
					}
				}
			}
		}
		dp[1][0] = 0;
		for (int i = 0; i < (1 << n); i++) {
			for (int j = 0; j < n; j++) {
				if (dp[i][j] == INF) { continue; }
				for (int k = 0; k < n; k++) {
					if (((i >> k) & 1) == 0) { dp[i | (1 << k)][k] = min(dp[i | (1 << k)][k], dp[i][j] + dis[j][k]); }
				}
			}
		}
		int ans = INF;
		for (int i = 0; i < n; i++) {
			ans = min(ans, dp[(1 << n) - 1][i] + dis[i][0]);
		}
		printf("%d\n", ans);
	}
}
