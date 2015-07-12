#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 30001

int fa[N], rnk[N], dep[N];

void init() {
	memset(rnk, 0, sizeof(rnk));
	for (int i = 1; i < N; i++) {
		fa[i] = i;
		dep[i] = 1;
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
		getchar();
		if (c == 'M') {
			a = (c = getchar()) - '0';
			while ((c = getchar()) >= '0' && c <= '9') { a = a * 10 + c - '0'; }
			b = (c = getchar()) - '0';
			while ((c = getchar()) >= '0' && c <= '9') { b = b * 10 + c - '0'; }
			unite(a, b);
		} else {
			a = (c = getchar()) - '0';
			while ((c = getchar()) >= '0' && c <= '9') { a = a * 10 + c - '0'; }
			printf("%d\n", dep[findfa(a)] - rnk[a] - 1);
		}
	}
}
