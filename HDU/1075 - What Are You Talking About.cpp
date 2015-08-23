#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 500005
#define M 3005

int n;
char dic[N][15], buf[M], t[15];

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
	scanf("%s", dic[n]);
	while (scanf("%s", dic[n]), strcmp(dic[n], "END") != 0) {
		scanf("%s", buf);
		ac.insert(buf, n); n++;
	}
	scanf("%s", buf); getchar();
	while (gets(buf), strcmp(buf, "END") != 0) {
		for (int i = 0, l = 0; buf[i]; i++) {
			if (islower(buf[i])) {
				t[l++] = buf[i];
			} else {
				if (l > 0) {
					t[l] = 0;
					int index = ac.query(t);
					printf("%s", index >= 0 ? dic[index] : t);
					memset(t, 0, sizeof(t)); l = 0;
				}
				putchar(buf[i]);
			}
		}
		putchar('\n');
	}
}
