#include <iostream>
#include <cstdio>
#include <algorithm>
#include <climits>
using namespace std;

#define N 100005

int n, m, a[N];

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

bool judge(int x) {
	for (int i = 1, last = 0, current; i < m; i++) {
		current = last + 1;
		while (current < n && a[current] - a[last] < x) { current++; }
		if (current == n) { return false; }
		last = current;
	}
	return true;
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		getInt(a[i]);
	}
	sort(a, a + n);
	int mid, l = 0, r = INT_MAX >> 1;
	while (r - l > 1) {
		mid = (l + r) >> 1;
		if (judge(mid)) { l = mid; }
		else { r = mid; }
	}
	printf("%d\n", l);
}
