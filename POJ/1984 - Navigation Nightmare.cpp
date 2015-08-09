#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

#define N 40005

int fa[N], fx[N], fy[N], f1[N], f2[N], len[N];
char d[N];

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

void init(int n) {
	for (int i = 1; i <= n; i++) { fa[i] = i; }
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
		case 'N': fy[y] -= len[t]; break;
		case 'E': fx[y] += len[t]; break;
		case 'S': fy[y] += len[t]; break;
		case 'W': fx[y] -= len[t]; break;
	}
}

int main() {
	char c;
	int n, m, q, a, b, t;
	scanf("%d %d", &n, &m);
	init(n);
	for (int i = 0; i < m; i++) {
		getInt(f1[i]); getInt(f2[i]); getInt(len[i]);
		while ((d[i] = getchar()) < 'A' || d[i] > 'Z');
	}
	scanf("%d", &q);
	for (int i = 0, current = 0; i < q; i++) {
		getInt(a); getInt(b); getInt(t);
		for (int j = current; j < t; j++) { unite(j); }
		printf("%d\n", (findfa(a) != findfa(b) ? -1 : abs(fx[a] - fx[b]) + abs(fy[a] - fy[b])));
		current = t;
	}
}
