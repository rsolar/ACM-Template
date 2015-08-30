#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 1005
#define M 105

template<class T> inline bool getInt(T &x) {
	char c = 0; T sign = 1;
	if ((c = getchar()) == EOF) { return false; }
	while ((c < '0' || c > '9') && c != '-') { c = getchar(); };
	if (c == '-') { sign = -1; c = getchar(); }
	x = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
	x *= sign;
	return true;
}

int n, p, mx;
char buf[M], s[M], t[M], ans[M];
int mp[] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9};

struct Trie {
	int Next[N][26], End[N];
	int root, L;
	int newnode() {
		memset(Next[L], -1, sizeof(Next[L]));
		End[L] = 0;
		return L++;
	}
	void init() {
		L = 0; root = newnode();
	}
	void insert(char buf[], int p) {
		int len = strlen(buf);
		int now = root;
		for (int i = 0; i < len; i++) {
			int c = buf[i] - 'a';
			if (Next[now][c] == -1) {
				Next[now][c] = newnode();
			}
			now = Next[now][c];
			End[now] += p;
		}
	}
	void dfs(int now, int pos, int len) {
		if (pos == len) {
			if (End[now] > mx || (End[now] == mx && strcmp(ans, t) > 0)) {
				mx = End[now]; strcpy(ans, t);
			}
			return;
		}
		for (int i = 0; i < 26; i++) {
			if (Next[now][i] != -1 && s[pos] == mp[i] + '0') {
				t[pos] = i + 'a'; t[pos + 1] = 0;
				dfs(Next[now][i], pos + 1, len);
				t[pos] = 0;
			}
		}
	}
} tr;

int main() {
	int C = 0, T;
	getInt(T);
	while (++C <= T) {
		tr.init();
		getInt(n);
		while (n--) {
			scanf("%s %d", buf, &p);
			tr.insert(buf, p);
		}
		getInt(n);
		printf("Scenario #%d:\n", C);
		while (n--) {
			scanf("%s", buf);
			for (int i = 1; buf[i]; i++) {
				strcpy(s, buf); s[i] = 0;
				strcpy(ans, "MANUALLY");
				mx = 0;
				tr.dfs(tr.root, 0, i);
				puts(ans);
			}
			putchar('\n');
		}
		putchar('\n');
	}
}
