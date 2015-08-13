#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 100005

template <class T>
inline bool getInt(T &x) {
	char c; T sign = 1;
	if ((c = getchar()) == EOF) { return false; }
	while ((c < '0' || c > '9') && c != '-') { c = getchar(); };
	if (c == '-') { sign = -1; c = getchar(); }
	x = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
	x *= sign;
	return true;
}

char x[N], y[N], de[27];
int Next[N];

void getNext(char x[], int m) {
	int i = 0, j = -1; Next[0] = -1;
	while (i < m) {
		while (j != -1 && x[i] != x[j]) { j = Next[j]; }
		Next[++i] = ++j;
	}
}

int main() {
	int T;
	getInt(T);
	while (T--) {
		gets(de); gets(x);
		int len = strlen(x);
		for (int i = 0; i < len; i++) {
			if (i >= (len + 1) / 2) { y[i] = de[x[i] - 'a']; }
			else { y[i] = x[i]; }
		}
		getNext(y, len);
		if (Next[len] > len - (len + 1) / 2) { Next[len] = len - (len + 1) / 2; }
		int l = len - Next[len];
		printf("%s", x);
		for (int i = Next[len]; i < l; i++) {
			for (int j = 0; j < 26; j++) {
				if (x[i] == de[j]) { putchar(j + 'a'); break; }
			}
		}
		putchar('\n');
	}
}
