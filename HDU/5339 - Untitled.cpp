#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

#define N 25

int a[N], n, ans;

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

bool cmp(int a, int b) { return a > b; }

void solve(int pos, int cnt, int r) {
	if (pos == n) {
		if (r == 0 && cnt < ans) { ans = cnt; }
		return;
	}
	solve(pos + 1, cnt, r);
	solve(pos + 1, cnt + 1, r % a[pos]);
}

int main() {
	int T, x;
	getInt(T);
	while (T--) {
		getInt(n); getInt(x);
		for (int i = 0; i < n; i++) { getInt(a[i]); }
		sort(a, a + n, cmp);
		ans = n + 1;
		solve(0, 0, x);
		printf("%d\n", ans > n ? -1 : ans);
	}
}
