#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

#define N 40001

int fa[N], fx[N], fy[N], f1[N], f2[N], len[N];
char d[N];

void init(int n) {
	memset(fx, 0, sizeof(fx));
	memset(fy, 0, sizeof(fy));
	for (int i = 1; i <= n; i++) {
		fa[i] = i;
	}
}

int findfa(int n) {
	if (fa[n] != n) {
		int t = fa[n];
		fa[n] = findfa(fa[n]);
		fx[n] += fx[t];
		fy[n] += fy[t];
	}
	return fa[n];
}

void unite(int t) {
	int x = findfa(f1[t]), y = findfa(f2[t]);
	fa[y] = x;
	fx[y] = fx[x] + fx[f1[t]] - fx[f2[t]];
	fy[y] = fy[x] + fy[f1[t]] - fy[f2[t]];
	switch (d[t]) {
		case 'N':
			fy[y] -= len[t]; break;
		case 'E':
			fx[y] += len[t]; break;
		case 'S':
			fy[y] += len[t]; break;
		case 'W':
			fx[y] -= len[t]; break;
	}
}

int main() {
	char c;
	int n, m, q, a, b, t;
	scanf("%d %d", &n, &m);
	init(n);
	for (int i = 0; i < m; i++) {
		while ((c = getchar()) < '0' || c > '9');
		f1[i] = c - '0';
		while ((c = getchar()) >= '0' && c <= '9') { f1[i] = f1[i] * 10 + c - '0'; }

		while ((c = getchar()) < '0' || c > '9');
		f2[i] = c - '0';
		while ((c = getchar()) >= '0' && c <= '9') { f2[i] = f2[i] * 10 + c - '0'; }

		while ((c = getchar()) < '0' || c > '9');
		len[i] = c - '0';
		while ((c = getchar()) >= '0' && c <= '9') { len[i] = len[i] * 10 + c - '0'; }

		while ((d[i] = getchar()) < 'A' || d[i] > 'Z');
	}
	scanf("%d", &q);
	for (int i = 0, current = 0; i < q; i++) {
		while ((c = getchar()) < '0' || c > '9');
		a = c - '0';
		while ((c = getchar()) >= '0' && c <= '9') { a = a * 10 + c - '0'; }

		while ((c = getchar()) < '0' || c > '9');
		b = c - '0';
		while ((c = getchar()) >= '0' && c <= '9') { b = b * 10 + c - '0'; }

		while ((c = getchar()) < '0' || c > '9');
		t = c - '0';
		while ((c = getchar()) >= '0' && c <= '9') { t = t * 10 + c - '0'; }
		for (int j = current; j < t; j++) {
			unite(j);
		}
		printf("%d\n", (findfa(a) != findfa(b) ? -1 : abs(fx[a] - fx[b]) + abs(fy[a] - fy[b])));
		current = t;
	}
}
