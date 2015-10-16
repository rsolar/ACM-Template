#include <iostream>
#include <cstdio>
using namespace std;

const int N = 500005;

int n, k, mx, mxid;
int fac[N], card[N];
char name[N][11];

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
template<typename T> struct SegmentTree {
  T sum[N << 2];
  void push_up(int rt) {
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
  }
  void build(int l, int r, int rt) {
    if (l == r) { sum[rt] = 1; return; }
    int m = l + r >> 1;
    build(lson);
    build(rson);
    push_up(rt);
  }
  T query(T val, int l, int r, int rt) {
    if (l == r) {
      sum[rt] = 0;
      return l;
    }
    int m = l + r >> 1;
    int res = (val <= sum[rt << 1] ? query(val, lson) : query(val - sum[rt << 1], rson));
    push_up(rt);
    return res;
  }
};
SegmentTree<int> st;

void pre() {
  for (int i = 1; i < N; i++) {
    for (int j = i; j < N; j += i) {
      fac[j]++;
    }
  }
}

void getmx(int n) {
  mx = fac[1]; mxid = 1;
  for (int i = 2; i <= n; i++) {
    if (mx < fac[i]) {
      mx = fac[i]; mxid = i;
    }
  }
}

int main() {
  pre();
  while (~scanf("%d %d", &n, &k)) {
    getmx(n);
    for (int i = 1; i <= n; i++) {
      scanf("%s %d", name[i], &card[i]);
    }
    st.build(1, n, 1);
    int pos;
    for (int i = 1, nn = n; i <= mxid; i++) {
      pos = st.query(k, 1, n, 1);
      if (--nn == 0) { break; }
      if (card[pos] > 0) {
        k = (k + card[pos] - 2) % nn + 1;
      } else {
        k = ((k + card[pos] - 1) % nn + nn) % nn + 1;
      }
    }
    printf("%s %d\n", name[pos], mx);
  }
}
