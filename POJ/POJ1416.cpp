#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 7

struct Node {
	int a[N], sum, len;
} t, ans;
int a, x, ansn;

void dfs(int num, int len) {
	if (num + t.sum < ans.sum) {
		return;
	}
	if (!num) {
		t.len = len;
		if (t.sum <= x && ans.sum < t.sum && t.len < x) {
			ans = t;
			ansn = 1;
		} else if (t.sum <= x && ans.sum == t.sum && t.len < x) {
			ansn++;
		}
		return;
	}
	for (int tmp, i = 10; i <= num * 10; i *= 10) {
		t.sum += (tmp = num % i);
		if (t.sum <= x) {
			t.a[len] = tmp;
			dfs(num / i, len + 1);
		}
		t.sum -= tmp;
	}
}

int main() {
	while (scanf("%d%d", &x, &a), a) {
		ansn = 0;
		memset(&t, 0, sizeof(t));
		memset(&ans, 0, sizeof(ans));
		dfs(a, 0);
		if (!ansn) {
			puts("error");
		} else if (ansn > 1) {
			puts("rejected");
		} else {
			printf("%d", ans.sum);
			for (int i = ans.len - 1; i >= 0; i--) {
				printf(" %d", ans.a[i]);
			}
			putchar('\n');
		}
	}
}
