#include <iostream>
#include <cstdio>
using namespace std;

#define N 1005

int fa[N];

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
	return n == fa[n] ? n : fa[n] = findfa(fa[n]);
}

inline void unite(int x, int y) {
	x = findfa(x); y = findfa(y);
	if (x != y) { fa[y] = x; }
}

int main() {
	int T, n, m, x, y;
	getInt(T);
	while (T--) {
		getInt(n); getInt(m);
		init(n);
		while (m--) {
			getInt(x); getInt(y);
			unite(x, y);
		}
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			if (fa[i] == i) { ans++; }
		}
		printf("%d\n", ans);
	}
}
