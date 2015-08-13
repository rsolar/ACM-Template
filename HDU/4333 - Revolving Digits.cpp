#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

#define N 200005

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
int Next[N], Extend[N];

void getNext(char x[], int m) {
	int i = 0, j = -1; Next[0] = -1;
	while (i < m) {
		while (j != -1 && x[i] != x[j]) { j = Next[j]; }
		Next[++i] = ++j;
	}
}

void preExtend(char x[], int m) {
	int j = 0, k = 1;
	while (j + 1 < m && x[j] == x[j + 1]) { j++; }
	Next[0] = m; Next[1] = j;
	for (int i = 2; i < m; i++) {
		int p = Next[k] + k - 1, l = Next[i - k];
		if (i + l < p + 1) { Next[i] = l; }
		else {
			j = max(0, p - i + 1);
			while (i + j < m && x[i + j] == x[j]) { j++; }
			Next[i] = j;
			k = i;
		}
	}
}

void getExtend(char x[], int m, char y[], int n) {
	preExtend(x, m);
	int j = 0, k = 0;
	while (j < n && j < m && x[j] == y[j]) { j++; }
	Extend[0] = j;
	for (int i = 1; i < n; i++) {
		int p = Extend[k] + k - 1, l = Next[i - k];
		if (i + l < p + 1) { Extend[i] = l; }
		else {
			j = max(0, p - i + 1);
			while (i + j < n && j < m && y[i + j] == x[j]) { j++; }
			Extend[i] = j;
			k = i;
		}
	}
}

int main() {
	int C = 0, T;
	getInt(T);
	while (++C <= T) {
		gets(x);
		int l = strlen(x), ll = l << 1;
		for (int i = 0; i < l; i++) { x[i + l] = x[i]; } x[ll] = 0;
		getExtend(x, l, x, ll);
		int ans1 = 0, ans2 = 0, ans3 = 0;
		for (int i = 0; i < l; i++) {
			if (Extend[i] >= l) { ans2++; }
			else if (x[Extend[i] + i] < x[Extend[i]]) { ans1++; }
			else { ans3++; }
		}
		getNext(x, l);
		int rep = l % (l - Next[l]) == 0 ? l / (l - Next[l]) : 1;
		printf("Case %d: %d %d %d\n", C, ans1 / rep, ans2 / rep, ans3 / rep);
	}
}
