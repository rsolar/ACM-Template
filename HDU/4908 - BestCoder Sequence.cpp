#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 40001

int a[N], cnt[N << 1];

int main() {
	int n, m, p;
	while (~scanf("%d %d", &n, &m)) {
		if (m == 1 || m == n) { printf("1\n"); continue; }
		for (int i = 0; i < n; i++) {
			scanf("%d", &a[i]);
			if (a[i] == m) { p = i; }
		}
		memset(cnt, 0, sizeof(cnt));
		int ans = 0;
		for (int i = p, t = 0; i >= 0; i--) {
			if (a[i] > m) { t++; }
			else if (a[i] < m) { t--; }
			cnt[N - 1 + t]++;
		}
		for (int i = p, t = 0; i < n; i++) {
			if (a[i] > m) { t--; }
			else if (a[i] < m) { t++; }
			ans += cnt[N - 1 + t];
		}
		printf("%d\n", ans);
	}
}
