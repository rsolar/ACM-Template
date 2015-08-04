#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		char s[25];
		int a = 0, b = 0, a10 = 1, b10 = 1;
		scanf("%s", s);
		int i = 2, lens = strlen(s) - 2;
		while (s[i] != '(' && i < lens + 2) {
			a = a * 10 + s[i] - '0';
			i++;
			a10 *= 10;
		}
		int pos = i++;
		while (s[i] != ')' && i < lens + 2) {
			b = b * 10 + s[i] - '0';
			i++;
			b10 *= 10;
		}
		if (!a && !b) { printf("0\n"); }
		else {
			int m, n, lenend = strlen(s + pos);
			if (*(s + pos) == '(') { lens -= 2; lenend -= 2; }
			if (!b) { m = a; n = a10; }
			else { m = a * b10 + b - a; n = (b10 - 1) * a10; }
			int gcdn = __gcd(n, m);
			printf("%d/%d\n", m / gcdn, n / gcdn);
		}
	}
}
