#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

#define N 10001

struct Node {
	int a, b;
} p[N];
int fa[N];

bool cmp(Node a, Node b) {
	return a.a > b.a;
}

int findfa(int n) {
	return n == fa[n] ? n : fa[n] = findfa(fa[n]);
}

int main() {
	char c;
	int n, ans, t;
	while (~scanf("%d", &n)) {
		for (int i = 0; i < N; i++) {
			fa[i] = i;
		}
		ans = 0;
		for (int i = 0; i < n; i++) {
			while ((c = getchar()) < '0' || c > '9');
			p[i].a = c - '0';
			while ((c = getchar()) >= '0' && c <= '9') { p[i].a = p[i].a * 10 + c - '0'; }
			while ((c = getchar()) < '0' || c > '9');
			p[i].b = c - '0';
			while ((c = getchar()) >= '0' && c <= '9') { p[i].b = p[i].b * 10 + c - '0'; }
		}
		sort(p, p + n, cmp);
		for (int i = 0; i < n; i++) {
			t = findfa(p[i].b);
			if (t > 0) {
				ans += p[i].a;
				fa[t] = t - 1;
			}
		}
		printf("%d\n", ans);
	}
}
