#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define N 50005

template<typename T> struct BIT {
  int n;
  T A[N];
  int lowbit(int x) { return x & (-x); }
  void init() {
    memset(A, 0, sizeof(A));
  }
  //前缀和[0, i)
  T sum(int i) {
    T ret = 0;
    for (int j = i; j > 0; j -= lowbit(j)) { ret += A[j]; }
    return ret;
  }
  //单点增减
  void add(int i, T v) {
    for (int j = i; j <= n; j += lowbit(j)) { A[j] += v; }
  }
  //区间和[i, j]
  T sum(int i, int j) {
    return sum(j) - sum(i - 1);
  }
};
BIT<int> bit;

int main() {
  char o[9]; int x, y;
  int C = 0, T;
  scanf("%d", &T);
  while (++C <= T) {
    scanf("%d", &bit.n);
    bit.init();
    for (int i = 1; i <= bit.n; i++) {
      scanf("%d", &x);
      bit.add(i, x);
    }
    printf("Case %d:\n", C);
    while (scanf("%s", o), o[0] != 'E') {
      scanf("%d %d", &x, &y);
      if (o[0] == 'A') {
        bit.add(x, y);
      } else if (o[0] == 'S') {
        bit.add(x, -y);
      } else {
        printf("%d\n", bit.sum(x, y));
      }
    }
  }
}
