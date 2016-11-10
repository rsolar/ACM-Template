//莫队算法 O(n^1.5)
//莫队算法是离线处理一类区间不修改查询类问题的算法
//如果你知道了[L,R]的答案, 你可以在O(1)的时间下得到[L,R-1]和[L,R+1]和[L-1,R]和[L+1,R]的答案的话, 就可以使用莫队算法
//lydsy 2038: [2009国家集训队]小Z的袜子(hose)
int n, m;
int c[N], pos[N];
ll ans, ansup[N], ansdn[N], cnt[N];
struct Node {
  int l, r, id;
  bool operator<(const Node &b)const { return pos[l] < pos[b.l] || (pos[l] == pos[b.l] && r < b.r); }
} q[N];
inline void add(int x) {
  ans -= cnt[c[x]] * cnt[c[x]];
  cnt[c[x]]++;
  ans += cnt[c[x]] * cnt[c[x]];
}
inline void del(int x) {
  ans -= cnt[c[x]] * cnt[c[x]];
  cnt[c[x]]--;
  ans += cnt[c[x]] * cnt[c[x]];
}
int main() {
  while (~scanf("%d%d", &n, &m)) {
    memset(cnt, 0, sizeof(cnt)); ans = 0;
    for (int i = 1, nn = ceil(sqrt(n)); i <= n; i++) { scanf("%d", &c[i]); pos[i] = (i - 1) / nn; }
    for (int i = 0; i < m; i++) { scanf("%d%d", &q[i].l, &q[i].r); q[i].id = i; }
    sort(q, q + m);
    for (int i = 0, l = 1, r = 0; i < m; i++) {
      while (l > q[i].l) { add(--l); }
      while (l < q[i].l) { del(l++); }
      while (r < q[i].r) { add(++r); }
      while (r > q[i].r) { del(r--); }
      ll up = ans - q[i].r + q[i].l - 1, dn = (q[i].r - q[i].l + 1ll) * (q[i].r - q[i].l), gcd = __gcd(up, dn);
      ansup[q[i].id] = up / gcd; ansdn[q[i].id] = dn / gcd;
    }
    for (int i = 0; i < m; i++) { printf("%lld/%lld\n", ansup[i], ansdn[i]); }
  }
}
