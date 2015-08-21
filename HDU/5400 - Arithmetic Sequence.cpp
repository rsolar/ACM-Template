#include <iostream>
#include <cstdio>
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

ll a[N], dp1[N], dp2[N];

int main() {
	int n; ll d1, d2;
	while (~scanf("%d %I64d %I64d", &n, &d1, &d2)) {
		ll ans = 0;
		for (int i = 1; i <= n; i++) { getInt(a[i]); }
		dp1[1] = 1;
		for (int i = 2; i <= n; i++) {
			if (a[i] - a[i - 1] == d1) { dp1[i] = dp1[i - 1] + 1; }
			else { dp1[i] = 1; }
		}
		if (d1 != d2) {
			dp2[n] = 1;
			for (int i = n - 1; i >= 1; i--) {
				if (a[i + 1] - a[i] == d2) { dp2[i] = dp2[i + 1] + 1; }
				else { dp2[i] = 1; }
			}
			for (int i = 1; i <= n; i++) { ans += dp1[i] * dp2[i]; }
		} else {
			for (int i = 1; i <= n; i++) { ans += dp1[i]; }
		}
		printf("%I64d\n", ans);
	}
}
