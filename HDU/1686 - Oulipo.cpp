#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 1000005
#define M 10005

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

char x[M], y[N];
int Next[M];

void getNext(char x[], int m) {
	int i = 0, j = -1; Next[0] = -1;
	while (i < m) {
		while (j != -1 && x[i] != x[j]) { j = Next[j]; }
		Next[++i] = ++j;
	}
}

int KMP_Count(char x[], int m, char y[], int n) {
	getNext(x, m);
	int i = 0, j = 0, ans = 0;
	while (i < n) {
		while (j != -1 && y[i] != x[j]) { j = Next[j]; }
		i++; j++;
		if (j >= m) { j = Next[j]; ans++; }
	}
	return ans;
}

int main() {
	int T;
	getInt(T);
	while (T--) {
		gets(x); gets(y);
		printf("%d\n", KMP_Count(x, strlen(x), y, strlen(y)));
	}
}
