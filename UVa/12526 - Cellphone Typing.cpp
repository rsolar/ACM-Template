#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 100005
#define M 105

int n, ans;
char buf[M];

struct Trie {
	int Next[N * 10][26], cnt[N * 10]; bool End[N * 10];
	int root, L;
	int newnode() {
		memset(Next[L], -1, sizeof(Next[L]));
		cnt[L] = 0; End[L] = false;
		return L++;
	}
	void init() {
		L = 0; root = newnode();
	}
	void insert(char buf[]) {
		int len = strlen(buf);
		int now = root;
		for (int i = 0; i < len; i++) {
			int c = buf[i] - 'a';
			if (Next[now][c] == -1) {
				Next[now][c] = newnode();
			}
			now = Next[now][c];
			cnt[now]++;
		}
		End[now] = true;
	}
	void query(int now) {
		int t = 0;
		for (int i = 0; i < 26; i++) {
			if (Next[now][i] != -1) {
				query(Next[now][i]);
				t++;
			}
		}
		if (t > 1) {
			ans += cnt[now] - End[now];
		} else if (End[now]) {
			ans += cnt[now] - 1;
		}
	}
} tr;

int main() {
	while (~scanf("%d", &n)) {
		tr.init(); ans = 0;
		for (int i = 0; i < n; i++) {
			scanf("%s", buf);
			tr.insert(buf);
		}
		tr.query(tr.root);
		printf("%.2f\n", double(ans + n) / n);
	}
}
