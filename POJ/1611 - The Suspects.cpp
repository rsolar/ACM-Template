#include <iostream>
#include <cstdio>
using namespace std;

#define N 30005

int fa[N];

int findfa(int n) {
	return n == fa[n] ? n : fa[n] = findfa(fa[n]);
}

int main() {
	char c;
	int n, m, k, x, y;
	while (scanf("%d %d", &n, &m), n) {
		if (m == 0) { puts("1"); }
		else {
			for (int i = 0; i < n; i++) { fa[i] = i; }
			for (int i = 0; i < m; i++) {
				while ((c = getchar()) < '0' || c > '9');
				k = c - '0';
				while ((c = getchar()) >= '0' && c <= '9') { k = k * 10 + c - '0'; }
				while ((c = getchar()) < '0' || c > '9');
				x = c - '0';
				while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
				for (int j = 1; j < k; j++) {
					while ((c = getchar()) < '0' || c > '9');
					y = c - '0';
					while ((c = getchar()) >= '0' && c <= '9') { y = y * 10 + c - '0'; }
					x = findfa(x);
					y = findfa(y);
					if (x != y) { fa[y] = x; }
				}
			}
			k = 1;
			for (int i = 1, t = findfa(0); i < n; i++) {
				if (t == findfa(i)) { k++; }
			}
			printf("%d\n", k);
		}
	}
}
