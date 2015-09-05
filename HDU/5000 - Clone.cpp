#include <bits/stdc++.h>
using namespace std;

#define N 2005
#define M 1000000007

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

int n, a[N], dp[N][N];

int main() {
	int C = 0, T;
	getInt(T);
	while (++C <= T) {
		int sum = 0;
		getInt(n);
		for (int i = 1; i <= n; i++) {
			getInt(a[i]); sum += a[i];
		}
		memset(dp, 0, sizeof(dp));
		dp[0][0] = 1;
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j <= sum; j++) {
				for (int k = 0; k <= a[i]; k++) {
					dp[i][j + k] += dp[i - 1][j];
					if (dp[i][j + k] >= M) { dp[i][j + k] -= M; }
				}
			}
		}
		printf("%d\n", dp[n][sum / 2]);
	}
}
