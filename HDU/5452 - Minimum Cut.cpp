#include <bits/stdc++.h>
using namespace std;

#define N 20005

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

int n, m, deg[N], deg2[N];

int main() {
  int u, v;
  int C = 0, T;
  getInt(T);
  while (++C <= T) {
    memset(deg, 0, sizeof(deg));
    memset(deg2, 0, sizeof(deg2));
    getInt(n); getInt(m);
    for (int i = 0; i < n; i++) {
      getInt(u); getInt(v);
      deg[u]++; deg[v]++;
    }
    for (int i = n; i < m; i++) {
      getInt(u); getInt(v);
      deg2[u]++; deg2[v]++;
    }
    int ans = INT_MAX;
    for (int i = 1; i <= n; i++) {
      if (deg[i] == 1) {
        ans = min(ans, deg[i] + deg2[i]);
      }
    }
    printf("Case #%d: %d\n", C, ans);
  }
}
