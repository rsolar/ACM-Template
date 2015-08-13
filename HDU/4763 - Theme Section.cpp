#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 1000005

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

char x[N];
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
		if (j == m) { j = Next[j]; ans++; }
	}
	return ans;
}

int main() {
	int T;
	getInt(T);
	while (T--) {
		gets(x);
		int len = strlen(x);
		getNext(x, len);
		int ans = Next[len];
		while (ans > len / 3) { ans = Next[ans]; }
		while (ans > 0) {
			if (KMP_Count(x, ans, x + ans, len - ans - ans) != 0) { break; }
			ans = Next[ans];
		}
		printf("%d\n", ans);
	}
}
