#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 1000005

char x[N];
int Next[N];

void getNext(char x[], int m) {
	int i = 0, j = -1; Next[0] = -1;
	while (i < m) {
		while (j != -1 && x[i] != x[j]) { j = Next[j]; }
		Next[++i] = ++j;
	}
}

int main() {
	while (~scanf("%s", x)) {
		int len = strlen(x);
		getNext(x, len);
		printf("%d\n", len - Next[len]);
	}
}
