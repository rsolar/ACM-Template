#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

#define N 100005
#define M 10005

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

struct Trie {
	int next[M * 50][26], fail[M * 50], end[M * 50];
	int L, root;
	inline int newnode() {
		for (int i = 0; i < 26; ++i) { next[L][i] = -1; }
		end[L++] = 0;
		return L - 1;
	}
	inline void init() { L = 0; root = newnode(); }
	inline void insert(char *buf) {
		int len = strlen(buf) , now = root;
		for (int i = 0; i < len; ++i) {
			if (next[now][buf[i] - 'a'] == -1) { next[now][buf[i] - 'a'] = newnode(); }
			now = next[now][buf[i] - 'a'];
		}
		end[now]++;
	}
	inline void build() {
		queue<int> Q;
		fail[root] = root;
		for (int i = 0; i < 26; ++i) {
			if (next[root][i] == -1) { next[root][i] = root; }
			else {
				fail[next[root][i]] = root;
				Q.push(next[root][i]);
			}
		}
		while (!Q.empty()) {
			int now = Q.front(); Q.pop();
			for (int i = 0; i < 26; ++i) {
				if (next[now][i] == -1) { next[now][i] = next[fail[now]][i]; }
				else {
					fail[next[now][i]] = next[fail[now]][i];
					Q.push(next[now][i]);
				}
			}
		}
	}
	inline int query(char *buf) {
		int len = strlen(buf) , now = root, res = 0;
		for (int i = 0; i < len; ++i) {
			now = next[now][buf[i] - 'a'];
			int temp = now;
			while (temp != root) {
				res += end[temp];
				temp = fail[temp];
			}
		}
		return res;
	}
} ac;

char y[N][M], buf[M];
int n, m;

int main() {
	int T;
	getInt(T);
	while (T--) {
		getInt(n); getInt(m);
		ac.init();
		for (int i = 0; i < n; i++) { gets(y[i]); }
		for (int i = 0; i < m; i++) { gets(buf); ac.insert(buf); }
		ac.build();
		for (int i = 0; i < n; i++) {
			printf("%d\n", ac.query(y[i]));
		}
	}
}
