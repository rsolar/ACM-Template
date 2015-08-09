#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 1005

int fa[N], fx[N], fy[N];
bool fix[N];

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
	memset(fix, 0, sizeof(fix));
	for (int i = 1; i <= n; i++) { fa[i] = i; }
}

int findfa(int n) {
	return n == fa[n] ? n : fa[n] = findfa(fa[n]);
}

inline void unite(int a, int b) {
	a = findfa(a);
	b = findfa(b);
	if (a != b) { fa[b] = a; }
}

int main() {
	char c;
	int n, d, a, b, t1, t2;
	scanf("%d %d", &n, &d);
	d *= d;
	init(n);
	for (int i = 1; i <= n; i++) {
		getInt(fx[i]); getInt(fy[i]);
	}
	while ((c = getchar()) != EOF) {
		if (c == 'O') {
			getInt(a);
			if (!fix[a]) {
				fix[a] = true;
				for (int i = 1; i <= n; i++) {
					if (a != i && fix[i] && (t1 = fx[a] - fx[i]) * t1 + (t2 = fy[a] - fy[i]) * t2 <= d) {
						unite(a, i);
					}
				}
			}
		} else if (c == 'S') {
			getInt(a); getInt(b);
			puts(findfa(a) == findfa(b) ? "SUCCESS" : "FAIL");
		}
	}
}
