//并查集基本函数
int fa[N];
void init(int n) {
  for (int i = 0; i <= n; i++) { fa[i] = i; }
}
int findfa(int n) {
  return n == fa[n] ? n : fa[n] = findfa(fa[n]);
}
inline void unite(int x, int y) {
  x = findfa(x); y = findfa(y);
  if (x != y) { fa[y] = x; }
}

int fa[N], rnk[N];
void init(int n) {
  for (int i = 0; i <= n; i++) { fa[i] = i; rnk[i] = 1; }
}
int findfa(int n) {
  return n == fa[n] ? n : fa[n] = findfa(fa[n]);
}
inline void unite(int x, int y) {
  x = findfa(x); y = findfa(y);
  if (x != y) {
    if (rnk[x] >= rnk[y]) { fa[y] = x; rnk[x] += rnk[y]; }
    else { fa[x] = y; rnk[y] += rnk[x]; }
  }
}
//种类并查集 ans = 假话数量
int ta = findfa(a), ta1 = findfa(a + n), ta2 = findfa(a + n + n),
    tb = findfa(b), tb1 = findfa(b + n), tb2 = findfa(b + n + n);
if (d == 1) {
  if (ta == tb1 || ta == tb2) { ans++; }
  else { if (ta != tb) { unite(ta, tb); unite(ta1, tb1); unite(ta2, tb2); } }
} else {
  if (ta == tb || ta == tb2) { ans++; }
  else { unite(ta, tb1); unite(ta1, tb2); unite(ta2, tb); }
}
