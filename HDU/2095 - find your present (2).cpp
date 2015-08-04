#include <iostream>
#include <cstdio>
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
	int n;
	while (getInt(n), n) {
		int t, ans = 0;
		while (n--) { getInt(t); ans ^= t; }
		printf("%d\n", ans);
	}
}
