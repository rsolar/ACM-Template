#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

#define N 3005
#define M 35

int n, ans;
char buf[M];

struct Trie {
	int Next[N][10], End[N];
	int root, L;
	int newnode() {
		for (int i = 0; i < 10; i++) { Next[L][i] = -1; }
		End[L++] = 0;
		return L - 1;
	}
	void init() {
		L = 0;
		root = newnode();
	}
	void insert(char buf[]) {
		int now = root;
		for (int i = 0; buf[i]; i++) {
			int c = buf[i] - '0';
			if (Next[now][c] == -1) {
				Next[now][c] = newnode();
			}
			now = Next[now][c];
		}
		ans = max(ans, ++End[now]);
	}
} ac;

int main() {
	while (~scanf("%d", &n)) {
		ans = 0;
		ac.init();
		getchar();
		while (n--) {
			gets(buf);
			int i = 0;
			while (buf[i] == '0') { i++; }
			ac.insert(buf + i);
		}
		printf("%d\n", ans);
	}
}
