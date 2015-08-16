#include <iostream>
#include <cstdio>
#include <set>
using namespace std;

#define N 200005

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

int n, q, fa[N];
set<int> st;

int findfa(int n) {
	return n == fa[n] ? n : fa[n] = findfa(fa[n]);
}

int main() {
	int o, x, y, xx;
	getInt(n); getInt(q);
	for (int i = 1; i <= n; i++) { fa[i] = i; st.insert(i); }
	for (int i = 0; i < q; i++) {
		getInt(o); getInt(x); getInt(y);
		switch (o) {
			case 1:
				fa[findfa(y)] = findfa(x);
				break;
			case 2:
				xx = findfa(x);
				for (auto p = st.upper_bound(x); p != st.end() && *p <= y;) {
					fa[findfa(*p)] = xx;
					p = st.erase(p);
				}
				break;
			case 3:
				puts(findfa(x) == findfa(y) ? "YES" : "NO");
				break;
		}
	}
}
