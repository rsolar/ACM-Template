#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define N 5000005

template <class T> inline bool getInt(T &x) {
  char c = 0; T sign = 1;
  if ((c = getchar()) == EOF) { return false; }
  while ((c < '0' || c > '9') && c != '-') { c = getchar(); };
  if (c == '-') { sign = -1; c = getchar(); }
  x = c - '0';
  while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
  x *= sign;
  return true;
}

int n, t[N];
ll a, b;

inline ll calc(int t1, int t2) {
  return a * t1 * t1 + b * t2;
}

int main() {
  int C = 0, T;
  scanf("%d", &T);
  while (++C <= T) {
    scanf("%d %I64d %I64d", &n, &a, &b);
    for (int i = 0; i < n; i++) {
      getInt(t[i]);
    }
    sort(t, t + n);
    printf("Case #%d: ", C);
    if (a > 0) {
      if (b > 0) {
        printf("%I64d\n", max(calc(t[n - 1], t[n - 2]), max(calc(t[n - 2], t[n - 1]), calc(t[0], t[n - 1]))));
      } else if (b == 0) {
        printf("%I64d\n", max(calc(t[n - 1], 0), calc(t[0], 0)));
      } else {
        printf("%I64d\n", max(calc(t[n - 1], t[0]), max(calc(t[0], t[1]), calc(t[1], t[0]))));
      }
    } else if (a == 0) {
      if (b > 0) {
        printf("%I64d\n", calc(0, t[n - 1]));
      } else if (b == 0) {
        puts("0");
      } else {
        printf("%I64d\n", calc(0, t[0]));
      }
    } else {
      int k = lower_bound(t, t + n, 0) - t;
      int mn = t[k], pos = k;
      if (k > 0 && -t[k - 1] < mn) {
        mn = -t[k - 1]; pos--;
      }
      if (b > 0) {
        if (pos != n - 1) {
          printf("%I64d\n", calc(mn, t[n - 1]));
        } else {
          printf("%I64d\n", max(calc(t[n - 2], mn), calc(mn, t[n - 2])));
        }
      } else if (b == 0) {
        printf("%I64d\n", calc(mn, 0));
      } else {
        if (pos != 0) {
          printf("%I64d\n", calc(mn, t[0]));
        } else {
          printf("%I64d\n", max(calc(t[1], mn), calc(mn, t[1])));
        }
      }
    }
  }
}
