#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll powMod(ll a, ll b, ll m) {
  ll r = 1; a %= m;
  while (b) {
    if (b & 1) { r = r * a % m; }
    a = a * a % m;
    b >>= 1;
  }
  return r;
}

int main() {
  int C = 0;
  ll p, k1, b1, k2;
  while (~scanf("%I64d %I64d %I64d %I64d", &p, &k1, &b1, &k2)) {
    bool flag = false;
    printf("Case #%d:\n", ++C);
    for (ll i = 1; i < p; i++) {
      ll a = i, b = p - powMod(a, b1 + k1, p);
      if (powMod(a, k1, p) == powMod(b, k2, p)) {
        printf("%I64d %I64d\n", a, b);
        flag = true;
      }
    }
    if (!flag) { puts("-1"); }
  }
}
