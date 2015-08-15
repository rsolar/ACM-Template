#include <iostream>
#include <cstdio>
using namespace std;

#define N 100005
#define M 258280327

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

int n, A, B, a[N], dp[N][10];

int main() {
	int T;
	getInt(T);
	while (T--) {
		int sum = 0;
		getInt(n); getInt(A); getInt(B);
		for (int i = 1; i <= n; i++) { getInt(a[i]); sum += a[i]; }
		A %= 9; B %= 9; sum %= 9;
		dp[0][0] = 1;
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < 9; j++) {
				dp[i][j] = (dp[i - 1][j] + dp[i - 1][(j - a[i] + 9) % 9]) % M;
			}
		}
		int ans = (sum == A && B != 0) + (sum == B && A != 0) + (sum == (A + B) % 9 ? dp[n][A] : 0);
		printf("%d\n", ans % M);
	}
}
