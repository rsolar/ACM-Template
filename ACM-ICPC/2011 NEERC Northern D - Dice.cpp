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
#define N 1005
#define M 105
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
	int id, face, a[M];
} a[N];
int sum, s[N *M];

bool cmp1(Node a, Node b) {
	return a.face > b.face;
}

bool cmp2(Node a, Node b) {
	return a.id < b.id;
}

int main() {
	freopen("dice.in", "r+", stdin);
	freopen("dice.out", "w", stdout);
	for (int i = 1; i < M * N; i++) { s[i] = s[i - 1] + i; }
	int n;
	while (~scanf("%d", &n)) {
		sum = 0;
		double ans = 0;
		for (int i = 0; i < n; i++) {
			getInt(a[i].face); a[i].id = i;
			sum += a[i].face;
		}
		sort(a, a + n, cmp1);
		for (int i = 0, cur = 0, pre = 0; i < n; i++) {
			for (int j = 0; j < a[i].face; j++) {
				a[i].a[j] = ++cur;
			}
			int tmp = s[cur] - s[pre];
			ans += (double)(tmp) / a[i].face;
			pre = cur;
		}
		sort(a, a + n, cmp2);
		printf("%.5f\n", ans);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < a[i].face; j++) {
				if (j) { putchar(' '); }
				printf("%d", a[i].a[j]);
			}
			putchar('\n');
		}
	}
}
