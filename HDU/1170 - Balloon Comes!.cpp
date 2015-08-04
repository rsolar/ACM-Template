#include <iostream>
#include <cstdio>
using namespace std;

int main() {
	int T;
	double a, b;
	char c;
	scanf("%d", &T);
	while (T--) {
		getchar();
		scanf("%c %lf %lf", &c, &a, &b);
		if (c == '+') { a += b; }
		else if (c == '-') { a -= b; }
		else if (c == '*') { a *= b; }
		else if (c == '/') { a /= b; }
		if (a - (int)a > 1e-6) { printf("%.2f\n", a); }
		else { printf("%d\n", (int)a); }
	}
}
