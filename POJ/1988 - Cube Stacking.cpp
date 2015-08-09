#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 30005

int fa[N], rnk[N], dep[N];

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

void init() {
	memset(rnk, 0, sizeof(rnk));
	for (int i = 1; i < N; i++) {
		fa[i] = i; dep[i] = 1;
	}
}

int findfa(int n) {
	if (fa[n] != n) {
		int t = fa[n];
		fa[n] = findfa(fa[n]);
		rnk[n] += rnk[t];
	}
	return fa[n];
}

inline void unite(int a, int b) {
	a = findfa(a);
	b = findfa(b);
	fa[b] = a;
	rnk[b] = dep[a];
	dep[a] += dep[b];
}

int main() {
	char c;
	int p, a, b;
	init();
	scanf("%d", &p);
	while (p--) {
		while ((c = getchar()) < 'C' || c > 'M');
		if (c == 'M') {
			getInt(a); getInt(b);
			unite(a, b);
		} else {
			getInt(a);
			printf("%d\n", dep[findfa(a)] - rnk[a] - 1);
		}
	}
}
