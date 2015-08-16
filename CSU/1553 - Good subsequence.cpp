#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

#define N 10005

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

int n, k, a[N];

int main() {
	while (~scanf("%d %d", &n, &k)) {
		for (int i = 0; i < n; i++) { getInt(a[i]); }
		int ans = 1, mn, mx;
		for (int i = 0, j; i < n; i++) {
			mn = a[i]; mx = a[i];
			for (j = i + 1; j < n; j++) {
				mn = min(mn, a[j]);
				mx = max(mx, a[j]);
				if (mx - mn > k) { break; }
			}
			ans = max(ans, j - i);
		}
		printf("%d\n", ans);
	}
}
