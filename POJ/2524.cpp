#include <iostream>
#include <cstdio>
using namespace std;

#define N 50001

int fa[N];

int findfa(int n) {
	return n == fa[n] ? n : fa[n] = findfa(fa[n]);
}

int main() {
	char c;
	int C = 0, n, m, x, y;
	while (scanf("%d %d", &n, &m), n) {
		int ans = n;
		for (int i = 1; i <= n; i++) {
			fa[i] = i;
		}
		for (int i = 0; i < m; i++) {
			while ((c = getchar()) < '0' || c > '9');
			x = c - '0';
			while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
			while ((c = getchar()) < '0' || c > '9');
			y = c - '0';
			while ((c = getchar()) >= '0' && c <= '9') { y = y * 10 + c - '0'; }
			x = findfa(x);
			y = findfa(y);
			if (x != y) {
				ans--;
				fa[y] = x;
			}
		}
		printf("Case %d: %d\n", ++C, ans);
	}
}
