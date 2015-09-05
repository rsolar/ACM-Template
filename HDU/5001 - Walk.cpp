#include <bits/stdc++.h>
using namespace std;

#define N 55
#define M 10005

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

int n, m, d;
double dp[N][M];
vector<int> e[N];

double solve(int st) {
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1.0;
	double ans = 0;
	for (int i = 0; i <= d; i++) {
		for (int u = 0; u <= n; u++) {
			if (u != st) {
				double p = 1.0 / e[u].size();
				for (size_t k = 0; k < e[u].size(); k++) {
					dp[e[u][k]][i + 1] += dp[u][i] * p;
				}
			}
		}
		ans += dp[st][i + 1];
	}
	return 1.0 - ans;
}

int main() {
	int C = 0, T, u, v;
	getInt(T);
	while (++C <= T) {
		getInt(n); getInt(m); getInt(d);
		for (int i = 0; i <= n; i++) { e[i].clear(); }
		for (int i = 1; i <= n; i++) { e[0].push_back(i); }
		while (m--) {
			getInt(u); getInt(v);
			e[u].push_back(v); e[v].push_back(u);
		}
		for (int i = 1; i <= n; i++) {
			printf("%.10f\n", solve(i));
		}
	}
}
