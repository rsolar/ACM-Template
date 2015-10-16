#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

#define N 200005

int n, m;

template<typename T> struct SegmentTree {
  T mx[N << 2];
  void push_up(int rt) {
    mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
  }
  //初始化 + 建树
  void build(int l, int r, int rt) {
    if (l == r) { scanf("%d", &mx[rt]); return; }
    int m = l + r >> 1;
    build(l, m, rt << 1);
    build(m + 1, r, rt << 1 | 1);
    push_up(rt);
  }
  //单点修改
  void update(int p, T val, int l, int r, int rt) {
    if (l == r) {
      mx[rt] = val;
      return;
    }
    int m = l + r >> 1;
    if (p <= m) { update(p, val, l, m, rt << 1); }
    else { update(p, val, m + 1, r, rt << 1 | 1); }
    push_up(rt);
  }
  //区间和
  T query(int L, int R, int l, int r, int rt) {
    if (L <= l && r <= R) { return mx[rt]; }
    int m = l + r >> 1, ret = 0;
    if (L <= m) { ret = max(ret, query(L, R, l, m, rt << 1)); }
    if (m < R) { ret = max(ret, query(L, R, m + 1, r, rt << 1 | 1)); }
    return ret;
  }
};
SegmentTree<int> st;

int main() {
  char o[2]; int x, y;
  while (~scanf("%d %d", &n, &m)) {
    st.build(1, n, 1);
    while (m--) {
      scanf("%s %d %d", o, &x, &y);
      if (o[0] == 'U') {
        st.update(x, y, 1, n, 1);
      } else {
        printf("%d\n", st.query(x, y, 1, n, 1));
      }
    }
  }
}
