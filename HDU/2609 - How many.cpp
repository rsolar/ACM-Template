#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <set>
using namespace std;

#define N 105

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
set<string> st;

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

int main() {
	int n;
	while (getInt(n)) {
		st.clear();
		for (int i = 0; i < n; i++) {
			gets(s);
			int len = strlen(s), j = minString(s, len);
			strncat(s + j, s, j); s[len + j] = 0;
			st.insert(s + j);
		}
		printf("%d\n", st.size());
	}
}
