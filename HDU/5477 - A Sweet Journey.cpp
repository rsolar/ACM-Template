#include <bits/stdc++.h>
using namespace std;

int main() {
  int C = 0, T;
  scanf("%d", &T);
  while (++C <= T) {
    int n, a, b, l, x = 0, y = 0, t = 0, mn = 0;
    scanf("%d %d %d %d", &n, &a, &b, &l);
    for (int i = 0; i < n; i++) {
      scanf("%d", &x);
      t += (x - y) * b;
      scanf("%d", &y);
      t -= (y - x) * a;
      mn = min(mn, t);
    }
    printf("Case #%d: %d\n", C, -mn);
  }
}
