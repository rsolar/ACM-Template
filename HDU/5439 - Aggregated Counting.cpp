#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define N 500005
#define M 1000000007

ll n, g[N], pre[N], sum[N];

int main() {
	g[1] = 1; g[2] = 2;
	pre[1] = 1; pre[2] = 3;
	for (ll i = 3; i < N; i++) {
		g[i] = lower_bound(pre + 1, pre + i, i) - pre;
		pre[i] = pre[i - 1] + g[i];
	}
	sum[1] = 1;
	for (ll i = 2; i < N; i++) {
		sum[i] = sum[i - 1] + ((pre[i - 1] + pre[i] + 1) * (pre[i] - pre[i - 1]) >> 1) % M * i % M;
	}
	int C = 0, T;
	scanf("%d", &T);
	while (++C <= T) {
		scanf("%I64d", &n);
		ll pos = lower_bound(pre + 1, pre + N, n) - pre, ans = sum[pos - 1];
		for (ll i = pre[pos - 1] + 1; i <= n; i++) {
			ans = (ans + pos * i) % M;
		}
		printf("%I64d\n", ans);
	}
}
