#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 5005
#define M 15

char buf[M];
struct Trie {
	int Next[N * 50][26], Fail[N * 50], End[N * 50];
	int root, L;
	int newnode() {
		for (int i = 0; i < 26; i++) { Next[L][i] = -1; }
		End[L++] = 0;
		return L - 1;
	}
	void init() {
		L = 0;
		root = newnode();
	}
	void insert(char buf[]) {
		int len = strlen(buf);
		int now = root;
		for (int i = 0; i < len; i++) {
			if (Next[now][buf[i] - 'a'] == -1) {
				Next[now][buf[i] - 'a'] = newnode();
			}
			now = Next[now][buf[i] - 'a'];
			End[now]++;
		}
	}
	int query(char buf[]) {
		int len = strlen(buf);
		int now = root;
		for (int i = 0; i < len; i++) {
			if (Next[now][buf[i] - 'a'] == -1) { return 0; }
			now = Next[now][buf[i] - 'a'];
		}
		return End[now];
	}
} ac;

int main() {
	ac.init();
	while (gets(buf)) {
		if (buf[0] == 0) { break; }
		ac.insert(buf);
	}
	while (~scanf("%s", buf)) {
		printf("%d\n", ac.query(buf));
	}
}
