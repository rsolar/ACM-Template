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

struct Node {
	int a, b;
} a[N];
ll cnt;

bool cmp(Node a, Node b) {
	return a.a < b.a || (a.a == b.a && a.b < b.b);
}

void mergesort(int l, int r) {
	if (l >= r) { return; }
	int mid = (l + r) >> 1;
	mergesort(l, mid);
	mergesort(mid + 1, r);
	vector<int> res;
	int i = l, j = mid + 1;
	while (i <= mid && j <= r) {
		if (a[i].b > a[j].b) {
			res.push_back(a[j++].b);
			cnt += mid + 1 - i;
		} else {
			res.push_back(a[i++].b);
		}
	}
	if (i > mid) { for (; j <= r; j++) { res.push_back(a[j].b); } }
	else { for (; i <= mid; i++) { res.push_back(a[i].b); } }
	for (int k = l; k <= r; k++) { a[k].b = res[k - l]; }
}

int main() {
	freopen("john.in", "r", stdin);
	freopen("john.out", "w", stdout);
	int n;
	while (~scanf("%d", &n)) {
		cnt = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &a[i].a, &a[i].b);
		}
		sort(a, a + n, cmp);
		mergesort(0, n - 1);
		printf("%I64d\n", cnt);
	}
}
