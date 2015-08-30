#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

#define N 1005
#define M 2000005

int n, ans[N];
char s[N][55], buf[M];

struct Trie {
	int Next[N * 50][95], Fail[N * 50], End[N * 50];
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
			int c = buf[i] - 32;
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
		for (int i = 0; i < 95; i++) {
			if (Next[root][i] == -1) {
				Next[root][i] = root;
			} else {
				Fail[Next[root][i]] = root;
				que.push(Next[root][i]);
			}
		}
		while (!que.empty()) {
			int now = que.front(); que.pop();
			for (int i = 0; i < 95; i++) {
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
			int c = buf[i] - 32;
			now = Next[now][c];
			int temp = now;
			while (temp != root) {
				ans[End[temp]]++;
				temp = Fail[temp];
			}
		}
	}
} ac;

int main() {
	while (~scanf("%d", &n)) {
		memset(ans, 0, sizeof(ans));
		ac.init();
		for (int i = 1; i <= n; i++) {
			scanf("%s", s[i]);
			ac.insert(s[i], i);
		}
		ac.build();
		getchar(); gets(buf);
		ac.query(buf);
		for (int i = 1; i <= n; i++) {
			if (ans[i]) {
				printf("%s: %d\n", s[i], ans[i]);
			}
		}
	}
}
