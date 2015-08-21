#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 100005

template <class T>
inline bool getInt(T &x) {
	char c = 0; T sign = 1;
	if ((c = getchar()) == EOF) { return false; }
	while ((c < '0' || c > '9') && c != '-') { c = getchar(); };
	if (c == '-') { sign = -1; c = getchar(); }
	x = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
	x *= sign;
	return true;
}

char s[N], t[N];

bool judge(char s[], char t[]) {
	int i = 0, j = 1, ls = strlen(s), lt = strlen(t);
	if (ls > lt) { return false; }
	if (ls == lt) { return (strcmp(s, t) == 0);}
	while (i < ls && s[i] == t[0]) { i++; }
	while (j < lt && t[j] == t[0]) { j++; }
	if (i < j) { return false; }
	while (i < ls && j < lt) {
		if (s[i] == t[j]) { i++; }
		j++;
	}
	return i == ls;
}

int main() {
	int T;
	getInt(T);
	while (T--) {
		gets(s); gets(t);
		puts(judge(s, t) ? "Yes" : "No");
	}
}
