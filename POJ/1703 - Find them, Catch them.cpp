#include <iostream>
#include <cstdio>
using namespace std;

#define N 200005

int fa[N];

int findfa(int n) {
	return n == fa[n] ? n : fa[n] = findfa(fa[n]);
}

void unite(int a, int b) {
	a = findfa(a);
	b = findfa(b);
	if (a != b) { fa[b] = a; }
}

int main() {
	char c, cc;
	int T, n, m, x, y, nn;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		nn = n << 1;
		for (int i = 1; i <= nn; i++) { fa[i] = i; }
		while (m--) {
			while ((cc = getchar()) != 'A' && cc != 'D');
			while ((c = getchar()) < '0' || c > '9');
			x = c - '0';
			while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
			while ((c = getchar()) < '0' || c > '9');
			y = c - '0';
			while ((c = getchar()) >= '0' && c <= '9') { y = y * 10 + c - '0'; }
			if (cc == 'D') {
				unite(x, y + n); unite(y, x + n);
			} else {
				if (findfa(x) == findfa(y)) { puts("In the same gang."); }
				else if (findfa(x) == findfa(y + n)) { puts("In different gangs."); }
				else { puts("Not sure yet."); }
			}
		}
	}
}
