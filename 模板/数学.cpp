//¿ìËÙÃİ
ll fastPowMod(ll a, ll b, ll m = M) {
	ll r = 1LL;
	while (b) {
		if (b & 1) { r = r * a % m; }
		a = a * a % m;
		b >>= 1;
	}
	return r;
}
