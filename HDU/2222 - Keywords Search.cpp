#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

#define N 10005
#define M 1000005

template <class T>
inline bool getInt(T &x) {
	char c = 0; T sign = 1;
	if ((c = getchar()) == EOF) { return false; }
	while ((c < '0' || c > '9') && c != '-') { c = getchar(); };
	if (c == '-') { sign = -1; c = getchar(); }
	x = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
	x *= sign;
	return true;
}

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
		}
		End[now]++;
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
			int now = que.front();
			que.pop();
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
	int query(char buf[]) {
		int len = strlen(buf);
		int now = root;
		int res = 0;
		for (int i = 0; i < len; i++) {
			now = Next[now][buf[i] - 'a'];
			int temp = now;
			while (temp != root) {
				res += End[temp];
				End[temp] = 0; //每串只数一次
				temp = Fail[temp];
			}
		}
		return res;
	}
} ac;

int main() {
	int T, n;
	getInt(T);
	while (T--) {
		ac.init();
		getInt(n);
		for (int i = 0; i < n; i++) {
			gets(buf); ac.insert(buf);
		}
		ac.build();
		gets(buf);
		printf("%d\n", ac.query(buf));
	}
}
