#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

#define N 200005

int h, w, n;

template<typename T> struct SegmentTree {
  T mx[N << 2];
  void push_up(int rt) {
    mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
  }
  void build(int l, int r, int rt) {
    mx[rt] = w;
    if (l == r) { return; }
    int m = l + r >> 1;
    build(l, m, rt << 1);
    build(m + 1, r, rt << 1 | 1);
  }
  T query(int x, int l, int r, int rt) {
    if (l == r) { mx[rt] -= x; return l; }
    int m = l + r >> 1, ret = mx[rt << 1] >= x ? query(x, l, m, rt << 1) : query(x, m + 1, r, rt << 1 | 1);
    push_up(rt);
    return ret;
  }
};
SegmentTree<int> st;

int main() {
  int t;
  while (~scanf("%d %d %d", &h, &w, &n)) {
    h = min(h, n);
    st.build(1, h, 1);
    while (n--) {
      scanf("%d", &t);
      if (st.mx[1] < t) { puts("-1"); continue; }
      printf("%d\n", st.query(t, 1, h, 1));
    }
  }
}
