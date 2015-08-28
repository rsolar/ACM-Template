#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <climits>
#include <ctime>
#include <cctype>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <functional>
#include <numeric>
using namespace std;

typedef long long ll;
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define N 200005
#define M 1000000007
#define judge(x,y) ((x)>=0&&(x)<h&&(y)>=0&&(y)<w)

template<class T> inline bool getInt(T &x) {
	char c = 0; T sign = 1;
	if ((c = getchar()) == EOF) { return false; }
	while ((c < '0' || c > '9') && c != '-') { c = getchar(); };
	if (c == '-') { sign = -1; c = getchar(); }
	x = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
	x *= sign;
	return true;
}

ll ans;
char buf[N];

struct PalindromicTree {
	int Next[N][26], Fail[N], cnt[N], len[N];
	int tol, S[N];
	int root, L;
	int newnode(int l) {
		memset(Next[L], 0, sizeof(Next[L]));
		cnt[L] = 0; len[L] = l;
		return L++;
	}
	void init() {
		L = 0; tol = 0; S[tol] = -1;
		root = newnode(0); Fail[root] = newnode(-1);
	}
	int getFail(int x) {
		while (S[tol - len[x] - 1] != S[tol]) { x = Fail[x]; }
		return x;
	}
	void Insert(char buf[]) {
		int l = strlen(buf);
		int cur = root, now;
		for (int i = 0; i < l; i++) {
			int c = buf[i] - 'a';
			S[++tol] = c;
			cur = getFail(cur);
			if (Next[cur][c] == 0) {
				now = newnode(len[cur] + 2);
				Fail[now] = Next[getFail(Fail[cur])][c];
				Next[cur][c] = now;
			}
			cur = Next[cur][c];
			cnt[cur]++;
		}
		for (int i = L - 1; i >= 0; --i) { cnt[Fail[i]] += cnt[i]; }
	}
} pa, pb;

void query(int nowa, int nowb) {
	for (int i = 0; i < 26; i++) {
		if (pa.Next[nowa][i] && pb.Next[nowb][i]) {
			ans += (ll)pa.cnt[pa.Next[nowa][i]] * pb.cnt[pb.Next[nowb][i]];
			query(pa.Next[nowa][i], pb.Next[nowb][i]);
		}
	}
}

int main() {
	int C = 0, T;
	getInt(T);
	while (++C <= T) {
		ans = 0;
		pa.init(); pb.init();
		gets(buf); pa.Insert(buf);
		gets(buf); pb.Insert(buf);
		query(pa.root, pb.root);
		query(pa.Fail[pa.root], pb.Fail[pb.root]);
		printf("Case #%d: %I64d\n", C, ans);
	}
}
