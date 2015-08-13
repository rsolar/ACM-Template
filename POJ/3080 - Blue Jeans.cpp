#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 65

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

char x[N][N];
int Next[N];

void getNext(char x[], int m) {
	int i = 0, j = -1; Next[0] = -1;
	while (i < m) {
		while (j != -1 && x[i] != x[j]) { j = Next[j]; }
		Next[++i] = ++j;
	}
}

bool KMP_Count(char x[], int m, char y[], int n) {
	int i = 0, j = 0;
	while (i < n) {
		while (j != -1 && y[i] != x[j]) { j = Next[j]; }
		i++; j++;
		if (j >= m) { return true; }
	}
	return false;
}


int main() {
	int T, n;
	getInt(T);
	while (T--) {
		char ans[N]; int ansl = 2;
		getInt(n);
		for (int i = 0; i < n; i++) { gets(x[i]); }
		for (int i = 0; i < 60; i++) {
			for (int j = 60 - i; j >= ansl; j--) {
				getNext(x[0] + i, j);
				bool flag = true;
				for (int k = 1; k < n; k++) {
					if (!KMP_Count(x[0] + i, j, x[k], 60)) {
						flag = false; break;
					}
				}
				if (flag && (ansl < j || (ansl == j && strncmp(ans, x[0] + i, j) > 0))) {
					strncpy(ans, x[0] + i, j); ans[j] = 0;
					ansl = j;
				}
			}
		}
		puts(ansl == 2 ? "no significant commonalities" : ans);
	}
}
