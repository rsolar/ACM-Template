#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
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

char s[N];
int Next[N];

void getNext(char x[], int m) {
	int i = 0, j = -1; Next[0] = -1;
	while (i < m) {
		while (j != -1 && x[i] != x[j]) { j = Next[j]; }
		Next[++i] = ++j;
	}
}

int main() {
	int C = 0, T;
	getInt(T);
	while (++C <= T) {
		vector<int> ans;
		gets(s);
		int len = strlen(s);
		getNext(s, len);
		int i = len;
		do {
			i = Next[i];
			ans.push_back(len - i);
		} while (i);
		printf("Case #%d: %d\n", C, ans.size());
		for (size_t i = 0 ; i < ans.size(); i++) {
			if (i) { putchar(' '); }
			printf("%d", ans[i]);
		}
		putchar('\n');
	}
}
