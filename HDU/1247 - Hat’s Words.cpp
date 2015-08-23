#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 50005
#define M 105

char s[N][M], buf[M];

struct Trie {
	int Next[N][26]; bool End[N];
	int root, L;
	inline int newnode() {
		memset(Next[L], -1, sizeof(Next[L]));
		End[L] = false;
		return L++;
	}
	void init() {
		L = 0;
		root = newnode();
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
		}
		End[now] = true;
	}
	bool query(char buf[]) {
		int len = strlen(buf);
		int now = root;
		for (int i = 0; i < len; i++) {
			int c = buf[i] - 'a';
			now = Next[now][c];
			if (now == -1) { return false; }
		}
		return End[now];
	}
} ac;

int main() {
	int n = 0;
	ac.init();
	while (~scanf("%s", s[n])) {
		ac.insert(s[n++]);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 1; s[i][j]; j++) {
			strncpy(buf, s[i], j); buf[j] = 0;
			if (ac.query(buf) && ac.query(s[i] + j)) {
				puts(s[i]); break;
			}
		}
	}
}
