#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

#define N 1005

int a[N];

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

int main() {
	int r, n, ans;
	while (getInt(r), getInt(n), r != -1) {
		ans = 0;
		for (int i = 0; i < n; i++) {
			getInt(a[i]);
		}
		sort(a, a + n);
		for (int i = 0; i < n;) {
			int p = a[i++];
			while (i < n && p + r >= a[i]) { i++; }
			p = a[i - 1];
			while (i < n && p + r >= a[i]) { i++; }
			ans++;
		}
		printf("%d\n", ans);
	}
}
