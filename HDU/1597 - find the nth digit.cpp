#include <iostream>
#include <cstdio>
using namespace std;

typedef long long ll;
#define N 65537

ll a[N];

int main() {
	ll k, n;
	for (int i = 1; i < N; i++) { a[i] = a[i - 1] + i; }
	scanf("%I64d", &k);
	while (k--) {
		scanf("%I64d", &n);
		ll mid, l = 1, r = N - 1;
		while (true) {
			mid = (l + r) >> 1;
			if (a[mid + 1] >= n && a[mid] < n) { break; }
			else if (a[mid] >= n) { r = mid - 1; }
			else { l = mid + 1; }
		}
		n -= a[mid]; n %= 9;
		printf("%I64d\n", n == 0 ? 9 : n);
	}
}
