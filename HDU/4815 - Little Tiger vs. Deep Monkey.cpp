#include <iostream>
#include <cstdio>
using namespace std;

#define N 40005

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

int a[45];
double dp[N];

int main() {
	int T, n;
	double p;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %lf", &n, &p);
		dp[0] = 1;
		for (int i = 1; i < N; i++) { dp[i] = 0; }
		int tot = 0;
		for (int i = 0; i < n; i++) {
			getInt(a[i]);
			tot += a[i];
		}
		for (int i = 0; i < n; i++) {
			for (int j = tot; j >= 0; j--) {
				if (a[i] > j) { dp[j] *= 0.5; }
				else { dp[j] = (dp[j] + dp[j - a[i]]) * 0.5; }
			}
		}
		for (int i = 0; i <= tot; i++) {
			p -= dp[i];
			if (p <= 1e-6) { printf("%d\n", i); break; }
		}
	}
}
