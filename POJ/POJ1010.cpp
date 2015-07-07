#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 26

struct Node {
	int type, num, mx, a[N];
} ans, t;
int a[N], x, n, ansn, cnt[N];

void dfs(int num, int val, int crt) {
	if (val == x) {
		t.type = t.mx = 0;
		t.num = num;
		for (int i = 0; i < n; i++) {
			if (t.a[i] != 0) {
				t.type++;
				if (t.mx < a[i]) {
					t.mx = a[i];
				}
			}
		}
		if (t.type > ans.type || t.type == ans.type && t.num < ans.num || t.type == ans.type && t.num == ans.num && t.mx > ans.mx) {
			ans = t;
			ansn = 1;
		} else if (t.type == ans.type && t.num == ans.num && t.mx == ans.mx) {
			ansn++;
		}
		return;
	}
	for (int i = 0; i < 5; i++) {
		if (crt < n && num + i <= 4 && val + i * a[crt] <= x) {
			t.a[crt] += i;
			dfs(num + i, val + i * a[crt], crt + 1);
			t.a[crt] -= i;
		}
	}
}

int main() {
	while (~scanf("%d", &x)) {
		memset(cnt, 0, sizeof(cnt));
		for (a[n = 0] = x, n++;;) {
			scanf("%d", &x);
			if (x == 0) { break; }
			if (++cnt[x] < 5) {
				a[n++] = x;
			}
		}
		sort(a, a + n);
		while (scanf("%d", &x), x) {
			ansn = 0;
			memset(&t, 0, sizeof(t));
			memset(&ans, 0, sizeof(ans));
			dfs(0, 0, 0);
			printf("%d ", x);
			if (ansn == 0) {
				printf("---- none\n");
			} else if (ansn > 1) {
				printf("(%d): tie\n", ans.type);
			} else {
				printf("(%d):", ans.type);
				for (int i = 0; i < n; i++) {
					if (ans.a[i]) {
						for (int j = 0; j < ans.a[i]; j++) {
							printf(" %d", a[i]);
						}
					}
				}
				putchar('\n');
			}
		}
	}
}
