#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define N 65
#define M 60005

int n, m, id;
char s[M], buf[N];
vector<int> ans;

struct Trie {
	int Next[M * 10][10], Fail[M * 10], End[M * 10];
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
			int c = buf[i] - '0';
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
		for (int i = 0; i < 10; i++) {
			if (Next[root][i] == -1) {
				Next[root][i] = root;
			} else {
				Fail[Next[root][i]] = root;
				que.push(Next[root][i]);
			}
		}
		while (!que.empty()) {
			int now = que.front(); que.pop();
			for (int i = 0; i < 10; i++) {
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
			int c = buf[i] - '0';
			now = Next[now][c];
			if (End[now]) { ans.push_back(End[now]); }
		}
	}
} ac;

int main() {
	while (~scanf("%d %d", &n, &m)) {
		memset(s, 0, sizeof(s));
		ans.clear();
		ac.init();
		for (int i = 1; i <= n; i++) {
			scanf("%s", s + strlen(s));
		}
		while (m--) {
			scanf("%s", buf); scanf("%s", buf); scanf("%d", &id); scanf("%s", buf); scanf("%s", buf);
			ac.insert(buf, id);
		}
		ac.build();
		ac.query(s);
		if (ans.empty()) {
			puts("No key can be found !");
		} else {
			printf("Found key:");
			for (size_t i = 0; i < ans.size(); i++) {
				printf(" [Key No. %d]", ans[i]);
			}
			putchar('\n');
		}
	}
}
