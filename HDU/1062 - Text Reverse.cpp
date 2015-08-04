#include <iostream>
#include <cstdio>
using namespace std;

#define N 1001

int main() {
	int T;
	char c, a[N];
	scanf("%d", &T);
	getchar();
	while (T--) {
		int i = 0;
		while ((c = getchar()) != '\n') {
			if (c == ' ') {
				while (i--) { putchar(a[i]); }
				putchar(' ');
				i = 0;
			} else {
				a[i++] = c;
			}
		}
		while (i--) { putchar(a[i]); }
		putchar('\n');
	}
}
