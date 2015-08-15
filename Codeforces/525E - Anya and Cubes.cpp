#include <iostream>
#include <cstdio>
#include <map>
using namespace std;

typedef long long ll;
#define N 30

template <class T>
inline bool getInt(T &x) {
	char c; T sign = 1;
	if ((c = getchar()) == EOF) { return false; }
	while ((c < '0' || c > '9') && c != '-') { c = getchar(); };
	if (c == '-') { sign = -1; c = getchar(); }
	x = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
	x *= sign;
	return true;
}

int n, k, mid;
ll s, a[N], fac[20], ans;
map<ll, ll> mp[N];

void getFac() {
	fac[0] = 1;
	for (int i = 1; i <= 18; i++) { fac[i] = fac[i - 1] * i; }
}

void dfs1(int pos, int kk, ll sum) {
	if (kk > k || sum > s) { return; }
	if (pos == mid + 1) {
		mp[kk][sum]++;
		return;
	}
	dfs1(pos + 1, kk, sum);
	dfs1(pos + 1, kk, sum + a[pos]);
	if (a[pos] <= 18) { dfs1(pos + 1, kk + 1, sum + fac[a[pos]]); }
}

void dfs2(int pos, int kk, ll sum) {
	if (kk > k || sum > s) { return; }
	if (pos == n) {
		for (int i = k - kk; i >= 0; i--) { ans += mp[i][s - sum]; }
		return;
	}
	dfs2(pos + 1, kk, sum);
	dfs2(pos + 1, kk, sum + a[pos]);
	if (a[pos] <= 18) { dfs2(pos + 1, kk + 1, sum + fac[a[pos]]); }
}

int main() {
	getFac();
	getInt(n); getInt(k); getInt(s); mid = n >> 1;
	for (int i = 0; i < n; i++) { getInt(a[i]); }
	dfs1(0, 0, 0);
	dfs2(mid + 1, 0, 0);
	printf("%I64d\n", ans);
}
