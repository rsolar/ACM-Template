#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

inline ull lowbit(ull x) { return x & (-x); }

int getL(ull d) {
  int l = 0;
  while (d) { l += d & 1; d >>= 1; }
  return l;
}

int main() {
  ull d;
  int s1, s2, l;
  int C = 0, T;
  scanf("%d", &T);
  while (++C <= T) {
    scanf("%I64u %d %d", &d, &s1, &s2);
    l = getL(++d);
    while (l < s1 || l > s2) {
      if (l < s1) { d += lowbit(~d); }
      else { d += lowbit(d); }
      l = getL(d);
    }
    printf("Case #%d: %I64u\n", C, d);
  }
}
