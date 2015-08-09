#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

typedef long long ll;

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

int main() {
	int n, x, t;
	ll ans = 0;
	priority_queue<int, vector<int>, greater<int> > que;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		getInt(x);
		que.push(x);
	}
	while (que.size() > 1) {
		t = que.top(); que.pop();
		t += que.top(); que.pop();
		ans += t;
		que.push(t);
	}
	printf("%I64d\n", ans);
}
