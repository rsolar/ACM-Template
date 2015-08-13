#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 1005

char x[N], y[N];
int Next[N];

void getNext(char x[], int m) {
	int i = 0, j = -1; Next[0] = -1;
	while (i < m) {
		while (j != -1 && x[i] != x[j]) { j = Next[j]; }
		Next[++i] = ++j;
	}
}

int KMP_Count(char x[], int m, char y[], int n) {
	int i = 0, j = 0, ans = 0;
	while (i < n) {
		while (j != -1 && y[i] != x[j]) { j = Next[j]; }
		i++; j++;
		if (j >= m) { j = 0; ans++; }
	}
	return ans;
}

int main() {
	while (~scanf("%s", y)) {
		if (y[0] == '#') { break; }
		scanf("%s", x);
		int xlen = strlen(x), ylen = strlen(y);
		getNext(x, xlen);
		printf("%d\n", KMP_Count(x, xlen, y, ylen));
	}
}
