#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

#define N 100005

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
	int a, b;
	init();
	while (scanf("%d %d", &a, &b), a >= 0) {
		mx = max(mx, max(a, b));
		if (a + b != 0) {
			int x = findfa(a), y = findfa(b);
			if (a == b || (a != b && x == y) || (b != y && x != y)) { flag = true; }
			else { fa[y] = x; }
		} else {
			if (!flag) {
				for (int i = 1, cnt = 0; i <= mx; i++) {
					if (fa[i] == i) { cnt++; }
					if (cnt > 1) { flag = true; break; }
				}
			}
			puts(flag ? "No" : "Yes");
			init();
		}
	}
}
