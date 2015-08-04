#include <iostream>
#include <cstdio>
using namespace std;

int main() {
	char m[21], f[21];
	while (scanf("%s%s", m, f) != EOF) {
		int i = 0, j = 0;
		while (m[i++] != '_');
		while (f[j++] != '_');
		printf("%s_small_%s\n", m + i, f + j);
	}
}
