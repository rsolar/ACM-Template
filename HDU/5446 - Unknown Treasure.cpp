#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define N 100005

ll fac[N], p[15], a[15];

void getFac(ll p) {
	fac[0] = 1;
	for (ll i = 1; i < p; i++) { fac[i] = (fac[i - 1] * i) % p; }
}

ll powMod(ll a, ll b, ll m) {
	ll r = 1; a %= m;
	while (b) {
		if (b & 1) { r = r * a % m; }
		a = a * a % m;
		b >>= 1;
	}
	return r;
}

ll inv(ll a, ll m) {
	return powMod(a, m - 2, m);
}

ll lucas(ll n, ll m, ll p) {
	if (m > n - m) { m = n - m; }
	ll res = 1;
	while (n && m) {
		ll a = n % p, b = m % p;
		if (a < b) { return 0; }
		res = res * fac[a] * inv(fac[b] * fac[a - b] % p, p) % p;
		n /= p; m /= p;
	}
	return res;
}

ll mulMod(ll a, ll b, ll m) {
	ll r = 0; a %= m; b %= m;
	while (b) {
		if (b & 1) { r = (r + a) % m; }
		a = (a << 1) % m;
		b >>= 1;
	}
	return r;
}

ll CRT(ll a[], ll m[], int k) {
	ll mm = 1, ans = 0;
	for (int i = 0; i < k; i++) { mm *= m[i]; }
	for (int i = 0; i < k; i++) {
		ll t = mm / m[i];
		ans = (ans + mulMod(mulMod(t, inv(t, m[i]), mm), a[i], mm)) % mm;
	}
	if (ans < 0) { ans += mm; }
	return ans;
}

int main() {
	ll n, m, k;
	int C = 0, T;
	scanf("%d", &T);
	while (++C <= T) {
		scanf("%I64d %I64d %I64d", &n, &m, &k);
		for (int i = 0; i < k; i++) {
			scanf("%I64d", &p[i]);
			getFac(p[i]);
			a[i] = lucas(n, m, p[i]);
		}
		printf("%I64d\n", CRT(a, p, k));
	}
}
