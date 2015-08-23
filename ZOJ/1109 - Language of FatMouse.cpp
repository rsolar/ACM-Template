#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 120005
#define M 25

int n;
char dic[N][15], buf[M], t[M];

struct Trie {
	int Next[N][26], End[N];
	int root, L;
	int newnode() {
		for (int i = 0; i < 26; i++) { Next[L][i] = -1; }
		End[L++] = -1;
		return L - 1;
	}
	void init() {
		L = 0;
		root = newnode();
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
	int query(char buf[]) {
		int len = strlen(buf);
		int now = root;
		for (int i = 0; i < len; i++) {
			int c = buf[i] - 'a';
			if (Next[now][c] == -1) { return -1; }
			now = Next[now][c];
		}
		return End[now];
	}
} ac;

int main() {
	ac.init();
	while (gets(buf)) {
		if (buf[0] == 0) { break; }
		sscanf(buf, "%s %s", dic[n], t);
		ac.insert(t, n++);
	}
	while (~scanf("%s", buf)) {
		int index = ac.query(buf);
		puts(index >= 0 ? dic[index] : "eh");
	}
}
