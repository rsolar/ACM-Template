#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 25

template<class T> inline bool getInt(T &x) {
	char c = 0; T sign = 1;
	if ((c = getchar()) == EOF) { return false; }
	while ((c < '0' || c > '9') && c != '-') { c = getchar(); };
	if (c == '-') { sign = -1; c = getchar(); }
	x = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
	x *= sign;
	return true;
}

char s[N];

int main() {
	int T;
	getInt(T);
	while (T--) {
		int a = 0, b = 0, a10 = 1, b10 = 1;
		scanf("%s", s);
		int i = 2, lens = strlen(s) - 2;
		while (i < lens + 2 && s[i] != '(') {
			a = a * 10 + s[i] - '0';
			a10 *= 10;
			i++;
		}
		int pos = i++;
		while (i < lens + 2 && s[i] != ')') {
			b = b * 10 + s[i] - '0';
			b10 *= 10;
			i++;
		}
		if (a == 0 && b == 0) { puts("0"); }
		else {
			int m, n, lenend = strlen(s + pos);
			if (*(s + pos) == '(') { lens -= 2; lenend -= 2; }
			if (b == 0) { m = a; n = a10; }
			else { m = a * b10 + b - a; n = (b10 - 1) * a10; }
			int gcdn = __gcd(n, m);
			printf("%d/%d\n", m / gcdn, n / gcdn);
		}
	}
}
