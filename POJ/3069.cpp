#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

#define N 1001

int a[N];

inline void getInt(int &x) {
	char c;
	while ((c = getchar()) < '0' || c > '9');
	x = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
}

int main() {
	int r, n, ans;
	while (scanf("%d %d", &r, &n), r != -1) {
		ans = 0;
		for (int i = 0; i < n; i++) {
			getInt(a[i]);
		}
		sort(a, a + n);
		for (int i = 0; i < n;) {
			int p = a[i++];
			while (i < n && p + r >= a[i]) { i++; }
			p = a[i - 1];
			while (i < n && p + r >= a[i]) { i++; }
			ans++;
		}
		printf("%d\n", ans);
	}
}
