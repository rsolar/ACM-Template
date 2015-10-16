#include <iostream>
#include <cstdio>
using namespace std;

const int N = 200005;
int n, pos[N], val[N], ans[N];

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
template<typename T> struct SegmentTree {
  T sum[N << 2];
  void build(int l, int r, int rt) {
    sum[rt] = r - l + 1;
    if (l == r) { return; }
    int m = l + r >> 1;
    build(lson);
    build(rson);
  }
  T query(int pos, int l, int r, int rt) {
    sum[rt]--;
    if (l == r) { return l; }
    int m = l + r >> 1;
    if (pos < sum[rt << 1]) { query(pos, lson); }
    else { query(pos - sum[rt << 1], rson); }
  }
};
SegmentTree<int> st;

int main() {
  while (~scanf("%d", &n)) {
    for (int i = 0; i < n; i++) {
      scanf("%d %d", &pos[i], &val[i]);
    }
    st.build(0, n - 1, 1);
    for (int i = n - 1; i >= 0; i--) {
      ans[st.query(pos[i], 0, n - 1, 1)] = val[i];
    }
    for (int i = 0; i < n; i++) {
      if (i) { putchar(' '); }
      printf("%d", ans[i]);
    }
    putchar('\n');
  }
}
