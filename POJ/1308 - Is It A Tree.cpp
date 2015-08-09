#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 1001

int fa[N], mx;
bool flag;

int findfa(int n) {
	if (fa[n] < 0) { fa[n] = n; }
	return n == fa[n] ? n : fa[n] = findfa(fa[n]);
}

void init() {
	memset(fa, -1, sizeof(fa));
	mx = 0;
	flag = false;
}

int main() {
	int C = 0, a, b;
	init();
	while (scanf("%d %d", &a, &b), a >= 0) {
		if (a > mx) { mx = a; }
		if (b > mx) { mx = b; }
		if (a + b != 0) {
			int x = findfa(a), y = findfa(b);
			if (a == b || (a != b && x == y) || (b != y && x != y)) { flag = true; }
			else { fa[y] = x; }
		} else {
			if (!flag) {
				for (int i = 1, j = 0; i <= mx; i++) {
					if (fa[i] == i) { j++; }
					if (j > 1) { flag = true; break; }
				}
			}
			printf("Case %d is %sa tree.\n", ++C, flag ? "not " : "");
			init();
		}
	}
}
