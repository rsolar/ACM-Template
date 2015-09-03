#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

#define N 255
#define M 5100005

int n;
char s[M], buf[M];
bool vis[N];

struct Trie {
	int Next[N * 1000][26], Fail[N * 1000], End[N * 1000];
	int root, L;
	int newnode() {
		memset(Next[L], -1, sizeof(Next[L]));
		End[L] = 0;
		return L++;
	}
	void init() {
		L = 0; root = newnode();
	}
	void insert(char buf[], int index) {
		int len = strlen(buf);
		int now = root;
		for (int i = 0; i < len; i++) {
			int c = buf[i] - 'A';
			if (Next[now][c] == -1) {
				Next[now][c] = newnode();
			}
			now = Next[now][c];
		}
		End[now] = index;
	}
	void build() {
		queue<int> que;
		Fail[root] = root;
		for (int i = 0; i < 26; i++) {
			if (Next[root][i] == -1) {
				Next[root][i] = root;
			} else {
				Fail[Next[root][i]] = root;
				que.push(Next[root][i]);
			}
		}
		while (!que.empty()) {
			int now = que.front(); que.pop();
			for (int i = 0; i < 26; i++) {
				if (Next[now][i] == -1) {
					Next[now][i] = Next[Fail[now]][i];
				} else {
					Fail[Next[now][i]] = Next[Fail[now]][i];
					que.push(Next[now][i]);
				}
			}
		}
	}
	void query(char buf[]) {
		int len = strlen(buf);
		int now = root;
		for (int i = 0; i < len; i++) {
			int c = buf[i] - 'A';
			now = Next[now][c];
			vis[End[now]] = true;
		}
	}
} ac;

int main() {
	int C = 0, T;
	scanf("%d", &T);
	while (++C <= T) {
		memset(vis, 0, sizeof(vis));
		ac.init();
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%s", buf);
			ac.insert(buf, i);
		}
		ac.build();
		scanf("%s", buf);
		int l = 0;
		for (int i = 0; buf[i]; i++) {
			if (buf[i] != '[') {
				s[l++] = buf[i];
			} else {
				int t = 0;
				while (isdigit(buf[++i])) { t = t * 10 + buf[i] - '0'; }
				for (int k = 0; k < t; k++) { s[l++] = buf[i]; }
				i++;
			}
		}
		s[l] = 0;
		ac.query(s);
		reverse(s, s + l);
		ac.query(s);
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			if (vis[i]) { ans++; }
		}
		printf("%d\n", ans);
	}
}
