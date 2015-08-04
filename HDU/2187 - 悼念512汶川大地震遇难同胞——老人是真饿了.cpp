#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

#define N 1005

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

struct Node {
	int p, w;
} a[N];

bool cmp(Node a, Node b) {
	return a.p < b.p;
}

int main() {
	int T, n, m;
	getInt(T);
	while (T--) {
		getInt(n); getInt(m);
		for (int i = 0; i < m; i++) {
			getInt(a[i].p); getInt(a[i].w);
		}
		sort(a, a + m, cmp);
		double ans = 0;
		for (int i = 0; i < m; i++) {
			if (n > a[i].p * a[i].w) {
				ans += a[i].w;
				n -= a[i].p * a[i].w;
			} else {
				ans += (double)n / a[i].p;
				break;
			}
		}
		printf("%.2f\n", ans);
	}
}
