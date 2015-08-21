#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 10005

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

char buf[N];

struct Trie {
	int Next[N * 50][10], End[N * 50];
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
	bool insert(char buf[]) {
		int len = strlen(buf);
		int now = root;
		bool flag = false;
		for (int i = 0; i < len; i++) {
			if (Next[now][buf[i] - '0'] == -1) {
				Next[now][buf[i] - '0'] = newnode();
				flag = true;
			}
			now = Next[now][buf[i] - '0'];
			if (End[now] != 0) { return false; }
		}
		End[now]++;
		return flag;
	}
} ac;

int main() {
	int T, n;
	getInt(T);
	while (T--) {
		bool flag = true;
		getInt(n);
		ac.init();
		for (int i = 0; i < n; i++) {
			gets(buf);
			if (flag) { flag = ac.insert(buf); }
		}
		puts(flag ? "YES" : "NO");
	}
}
