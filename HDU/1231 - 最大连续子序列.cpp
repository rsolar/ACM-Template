#include <iostream>
#include <cstdio>
#include <climits>
using namespace std;

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
	int n, x;
	while (getInt(n), n) {
		int ans = INT_MIN, ansl, st, ansr, sum = INT_MIN, f, l;
		bool neg = true;
		for (int i = 0; i < n; i++) {
			getInt(x);
			if (x >= 0) { neg = false; }
			if (i == 0) { f = x; } else { l = x; }
			if (sum < 0) { sum = x; st = x; }
			else { sum += x; }
			if (sum > ans) { ans = sum; ansl = st; ansr = x; }
		}
		if (neg) { printf("0 %d %d\n", f, l); }
		else { printf("%d %d %d\n", ans, ansl, ansr);}
	}
}
