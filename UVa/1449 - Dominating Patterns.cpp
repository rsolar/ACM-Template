#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

#define N 155
#define M 1000005

int n;
char s[N][75], buf[M];
int cnt[N];

struct Trie {
	int Next[N * 70][26], Fail[N * 70], End[N * 70];
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
			int c = buf[i] - 'a';
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
			int c = buf[i] - 'a';
			now = Next[now][c];
			int temp = now;
			while (temp != root) {
				if (End[temp]) { cnt[End[temp]]++; }
				temp = Fail[temp];
			}
		}
	}
} ac;

int main() {
	while (scanf("%d", &n), n) {
		memset(cnt, 0, sizeof(cnt));
		ac.init();
		for (int i = 1; i <= n; i++) {
			scanf("%s", s[i]); ac.insert(s[i], i);
		}
		ac.build();
		scanf("%s", buf);
		ac.query(buf);
		int mx = *max_element(cnt + 1, cnt + n + 1);
		printf("%d\n", mx);
		for (int i = 1; i <= n; i++) {
			if (cnt[i] == mx) { puts(s[i]); }
		}
	}
}
