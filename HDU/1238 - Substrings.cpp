#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

typedef long long ll;
#define ___ ios_base::sync_with_stdio(0);cin.tie(0);
#define N 105
#define M 10007
#define judge(x,y) ((x)>=0&&(x)<h&&(y)>=0&&(y)<w)

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
int Next1[N], Next2[N], len[N];

void getNext(char x[], int m, int Next[]) {
	int i = 0, j = -1; Next[0] = -1;
	while (i < m) {
		while (j != -1 && x[i] != x[j]) { j = Next[j]; }
		Next[++i] = ++j;
	}
}

bool KMP_Count(char x[], int m, char y[], int n, int Next[]) {
	int i = 0, j = 0;
	while (i < n) {
		while (j != -1 && y[i] != x[j]) { j = Next[j]; }
		i++; j++;
		if (j >= m) { return true; }
	}
	return false;
}

int main() {
	int T;
	getInt(T);
	while (T--) {
		int n, ans = 0;
		getInt(n);
		for (int i = 0; i < n; i++) { gets(x[i]); len[i] = strlen(x[i]); }
		for (int i = 0; i < len[0]; i++) {
			for (int j = len[0] - i; j > ans; j--) {
				char tmp[N];
				bool flag = true;
				strncpy(tmp, x[0] + i, j); tmp[j] = 0;
				reverse(tmp, tmp + j);
				getNext(x[0] + i, j, Next1);
				getNext(tmp, j, Next2);
				for (int k = 1; k < n; k++) {
					if (!KMP_Count(x[0] + i, j, x[k], len[k], Next1) && !KMP_Count(tmp, j, x[k], len[k], Next2)) {
						flag = false; break;
					}
				}
				if (flag) { ans = j; }
			}
		}
		printf("%d\n", ans);
	}
}
