#include <iostream>
#include <cstdio>
using namespace std;

typedef long long ll;
#define N 1000005
#define M 1000000007

template <class T>
inline bool getInt(T &x) {
	char c = 0; T sign = 1;
	if ((c = getchar()) == EOF) { return false; }
	while ((c < '0' || c > '9') && c != '-') { c = getchar(); };
	if (c == '-') { sign = -1; c = getchar(); }
	x = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
	x *= sign;
	return true;
}

int prime[N];
ll ans[N];

void init() {
	for (int i = 2; i <= N; i++) {
		if (!prime[i]) { prime[++prime[0]] = i; }
		for (int j = 1; j <= prime[0] && prime[j] <= N / i; j++) {
			prime[prime[j] * i] = 1;
			if (i % prime[j] == 0) { break; }
		}
	}
	for (int i = 1; i < N; i++) { ans[i] = 1LL; }
	for (int i = 1; i <= prime[0]; i++) {
		for (ll t = prime[i]; t < N; t *= prime[i]) { ans[t] = prime[i]; }
	}
	for (int i = 2; i < N; i++) { ans[i] = ans[i - 1] * ans[i] % M; }
}

ll fastPowMod(ll a, ll b, ll m = M) {
	ll r = 1LL;
	while (b) {
		if (b & 1) { r = r * a % m; }
		a = a * a % m;
		b >>= 1;
	}
	return r;
}

int main() {
	init();
	int T; ll n;
	getInt(T);
	while (T--) {
		getInt(n); n++;
		printf("%I64d\n", ans[n] * fastPowMod(n, M - 2) % M);
	}
}
