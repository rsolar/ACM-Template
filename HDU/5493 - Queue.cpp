#include <bits/stdc++.h>
using namespace std;

#define N 100005

int n, ans[N];
struct Node {
  int h, k;
  bool operator<(const Node &r) const { return h < r.h; }
} a[N];

template<typename T> struct BIT {
  T A[N], num[N];
  int lowbit(int x) { return x & (-x); }
  void init() {
    memset(A, 0, sizeof(A));
  }
  T sum(int i) {
    T ret = 0;
    for (int j = i; j > 0; j -= lowbit(j)) { ret += A[j]; }
    return ret;
  }
  void add(int i, T v) {
    for (int j = i; j <= n; j += lowbit(j)) { A[j] += v; }
  }
  int getK(int l, int r, int k) {
    while (l <= r) {
      int mid = l + ((r - l) >> 1);
      if (sum(mid) >= k) { r = mid - 1; }
      else { l = mid + 1; }
    }
    return l;
  }
};
BIT<int> bit1, bit2;

int main() {
  int C = 0, T;
  scanf("%d", &T);
  while (++C <= T) {
    bit1.init(); bit2.init();
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d %d", &a[i].h, &a[i].k);
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
      bit1.add(i, 1);
      bit2.add(i, 1);
    }
    bool flag = true;
    for (int i = 1; i <= n; i++) {
      if (a[i].k >= n - i + 1) {
        flag = false; break;
      }
      int pos = min(bit1.getK(1, n, a[i].k + 1), n - bit2.getK(1, n, a[i].k + 1) + 1);
      ans[pos] = a[i].h;
      bit1.add(pos, -1);
      bit2.add(n - pos + 1, -1);
    }
    printf("Case #%d:", C);
    if (!flag) {
      puts(" impossible");
    } else {
      for (int i = 1; i <= n; i++) {
        printf(" %d", ans[i]);
      }
      putchar('\n');
    }
  }
}
