#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;
#define N 1000005

int a[N], dp[N];

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

int main() {
	int T, n, m;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) { getInt(a[i]); }
		if (n == 1) { puts("1"); continue; }
		int ans = 2;
		dp[1] = 2;
		for (int i = 2; i < n; i++) {
			if (a[i] - a[i - 1] == a[i - 1] - a[i - 2]) { dp[i] = dp[i - 1] + 1; }
			else { dp[i] = 2; ans = max(ans, dp[i - 1]); }
		}
		ans = max(ans, dp[n - 1]);
		dp[1] = 2;
		for (int i = 2; i < n; i++) {
			if ((ll)a[i] * a[i - 2] == (ll)a[i - 1] * a[i - 1]) { dp[i] = dp[i - 1] + 1; }
			else { dp[i] = 2; ans = max(ans, dp[i - 1]); }
		}
		ans = max(ans, dp[n - 1]);
		printf("%d\n", ans);
	}
}
