#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

#define N 100005
#define M 10005

int n;
char buf[M];
vector<int> ans;

struct Trie {
	int Next[N][95], Fail[N], End[N];
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
			if (End[now]) { ans.push_back(End[now]); }
		}
	}
} ac;

int main() {
	while (~scanf("%d", &n)) {
		int tot = 0;
		ac.init();
		for (int i = 1; i <= n; i++) {
			scanf("%s", buf);
			ac.insert(buf, i);
		}
		ac.build();
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%s", buf);
			ans.clear();
			ac.query(buf);
			if (!ans.empty()) {
				tot++;
				sort(ans.begin(), ans.end());
				printf("web %d:", i);
				for (size_t j = 0; j < min(3, int(ans.size())); j++) {
					printf(" %d", ans[j]);
				}
				putchar('\n');
			}
		}
		printf("total: %d\n", tot);
	}
}
