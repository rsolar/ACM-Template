#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 1005

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

char s1[N], s2[N], s[N];
bool dp[N][N];

int main() {
	int C = 0, T;
	getInt(T);
	while (++C <= T) {
		memset(dp, 0, sizeof(dp));
		scanf("%s %s %s", s1, s2, s);
		int l1 = strlen(s1), l2 = strlen(s2);
		dp[0][0] = true;
		for (int i = 0; i <= l1; i++) {
			for (int j = 0; j <= l2; j++) {
				if ((i > 0 && dp[i - 1][j] && s1[i - 1] == s[i + j - 1]) || (j > 0 && dp[i][j - 1] && s2[j - 1] == s[i + j - 1])) { dp[i][j] = true; }
			}
		}
		printf("Data set %d: %s\n", C, dp[l1][l2] ? "yes" : "no");
	}

}
