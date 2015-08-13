#include <iostream>
#include <cstdio>
#include <algorithm>
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

int minString(char s[], int m) {
	int i, j, k;
	char ss[m << 1];
	for (i = 0; i < m; i++) { ss[i] = ss[i + m] = s[i]; }
	for (i = k = 0, j = 1; k < m && i < m && j < m;) {
		for (k = 0; k < m && ss[i + k] == ss[j + k]; k++);
		if (k < m) {
			if (ss[i + k] > ss[j + k]) { i += k + 1; }
			else { j += k + 1; }
			if (i == j) { j++; }
		}
	}
	return min(i, j);
}

int maxString(char s[], int m) {
	int i, j, k;
	char ss[m << 1];
	for (i = 0; i < m; i++) { ss[i] = ss[i + m] = s[i]; }
	for (i = k = 0, j = 1; k < m && i < m && j < m;) {
		for (k = 0; k < m && ss[i + k] == ss[j + k]; k++);
		if (k < m) {
			if (ss[i + k] < ss[j + k]) { i += k + 1; }
			else { j += k + 1; }
			if (i == j) { j++; }
		}
	}
	return min(i, j);
}

int main() {
	while (~scanf("%s", x)) {
		int len = strlen(x);
		getNext(x, len);
		int l = len - Next[len], mn = minString(x, len), mx = maxString(x, len), cnt = (len % l == 0 ? len / l : 1);
		printf("%d %d %d %d\n", mn + 1, cnt, mx + 1, cnt);
	}
}
