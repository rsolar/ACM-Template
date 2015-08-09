#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define N 200001
#define M 1000000007LL
#define judge(x,y) ((x)>=0&&(x)<h&&(y)>=0&&(y)<w)
typedef long long ll;

struct A {
	ll l, r;
	int id;
	bool operator <(const A &cmp) const {
		return l < cmp.l;
	}
} a[N];
struct B {
	ll length;
	int id;
	bool operator <(const B &cmp) const {
		return (length < cmp.length || (length == cmp.length && id < cmp.id));
	}
} b[N];
int ans[N];

int main() {
	int n, m;
	ll l, r, tl, tr;
	scanf("%d %d", &n, &m);
	scanf("%I64d %I64d", &tl, &tr);
	int nn = n - 1;
	for (int i = 0; i < nn; i++) {
		scanf("%I64d %I64d", &l, &r);
		a[i].l = l - tr;
		a[i].r = r - tl;
		a[i].id = i;
		tl = l;
		tr = r;
	}
	for (int i = 0; i < m; i++) {
		scanf("%I64d", &b[i].length);
		b[i].id = i;
	}
	sort(a, a + nn);
	sort(b, b + m);
	set<B> st;
	for (int i = 0, j = 0; i < m; i++) {
		while (!st.empty() && st.begin()->length < b[i].length) {
			st.erase(st.begin());
		}
		while (j < nn && a[j].l <= b[i].length && a[j].r >= b[i].length) {
			st.insert((B) {a[j].r, a[j].id});
			j++;
		}
		if (st.empty()) { continue; }
		ans[st.begin()->id] = b[i].id + 1;
		st.erase(st.begin());
	}
	for (int i = 0; i < nn; i++) {
		if (ans[i] == 0) {
			puts("No");
			return 0;
		}
	}
	puts("Yes");
	for (int i = 0; i < nn; i++) {
		printf("%d ", ans[i]);
	}
	putchar('\n');
}
