#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 1002

int fa[N], fx[N], fy[N];
bool fix[N];

void init(int n) {
	memset(fix, 0, sizeof(fix));
	for (int i = 1; i <= n; i++) {
		fa[i] = i;
	}
}

int findfa(int n) {
	return n == fa[n] ? n : fa[n] = findfa(fa[n]);
}

inline void unite(int a, int b) {
	a = findfa(a);
	b = findfa(b);
	if (a != b) {
		fa[b] = a;
	}
}

int main() {
	char c;
	int n, d, a, b, t1, t2;
	scanf("%d %d", &n, &d);
	d *= d;
	init(n);
	for (int i = 1; i <= n; i++) {
		while ((c = getchar()) < '0' || c > '9');
		fx[i] = c - '0';
		while ((c = getchar()) >= '0' && c <= '9') { fx[i] = fx[i] * 10 + c - '0'; }
		fy[i] = (c = getchar()) - '0';
		while ((c = getchar()) >= '0' && c <= '9') { fy[i] = fy[i] * 10 + c - '0'; }
	}
	while ((c = getchar()) != EOF) {
		if (c == 'O') {
			while ((c = getchar()) < '0' || c > '9');
			a = c - '0';
			while ((c = getchar()) >= '0' && c <= '9') { a = a * 10 + c - '0'; }
			if (!fix[a]) {
				fix[a] = 1;
				for (int i = 1; i <= n; i++) {
					if (a != i && fix[i] && (t1 = fx[a] - fx[i]) * t1 + (t2 = fy[a] - fy[i]) * t2 <= d) {
						unite(a, i);
					}
				}
			}
		} else if (c == 'S') {
			while ((c = getchar()) < '0' || c > '9');
			a = c - '0';
			while ((c = getchar()) >= '0' && c <= '9') { a = a * 10 + c - '0'; }
			b = (c = getchar()) - '0';
			while ((c = getchar()) >= '0' && c <= '9') { b = b * 10 + c - '0'; }
			puts(findfa(a) == findfa(b) ? "SUCCESS" : "FAIL");
		}
	}
}
