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
#define N 100005
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

char *ans[] = {"Unique", "Ambiguous", "Impossible"};

int main() {
	freopen("black.in", "r", stdin);
	freopen("black.out", "w", stdout);
	int h, w, p, k;
	char s[N];
	while (~scanf("%d %d %d %d%s", &h, &w, &p, &k, s)) {
		int flag = 2, cnt = 0, time = 0, mx = 0;
		for (int i = 0; s[i]; i++) {
			if (s[i] == '*') {
				if (cnt == 0) { time++; if (time > 1) { break; } }
				cnt++;
				mx = max(mx, cnt);
			} else {
				cnt = 0;
			}
		}
		if (time > 1) { flag = 2; }
		else {
			if (mx == 0) {
				if (k - 1 < p && h - k < p) { flag = 2; }
				else if (p == w && ((k - 1 == p && h - k < p) || (k - 1 < p && h - k == p))) { flag = 0; }
				else { flag = 1; }
			} else if (mx != p) { flag = 2; }
			else {
				if (p == 1 || h == p || k == 1 || k == h) { flag = 0; }
				else { flag = 1; }
			}
		}
		puts(ans[flag]);
	}
}
