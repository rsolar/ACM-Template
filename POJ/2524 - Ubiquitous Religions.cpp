#include <iostream>
#include <cstdio>
using namespace std;

#define N 50005

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

int findfa(int n) {
	return n == fa[n] ? n : fa[n] = findfa(fa[n]);
}

int main() {
	char c;
	int C = 0, n, m, x, y;
	while (getInt(n), getInt(m), n) {
		int ans = n;
		for (int i = 1; i <= n; i++) { fa[i] = i; }
		for (int i = 0; i < m; i++) {
			getInt(x); getInt(y);
			x = findfa(x); y = findfa(y);
			if (x != y) { fa[y] = x; ans--; }
		}
		printf("Case %d: %d\n", ++C, ans);
	}
}
