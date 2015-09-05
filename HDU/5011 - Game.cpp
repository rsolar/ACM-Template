#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
	int n;
	while (~scanf("%d", &n)) {
		ll x, ans = 0;
		while (n--) {
			scanf("%I64d", &x); ans ^= x;
		}
		puts(ans ? "Win" : "Lose");
	}
}
