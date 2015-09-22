#include <bits/stdc++.h>
using namespace std;

#define N 2000005

char s[N];

int main() {
  int C = 0, T;
  scanf("%d", &T);
  while (++C <= T) {
    scanf("%s", s);
    printf("Case #%d: ", C);
    int i, n = strlen(s);
    for (i = 0; i < n && s[i] == 'f'; i++);
    int k = i;
    if (k == n) { printf("%d\n", (n + 1) >> 1); continue; }
    for (; i < n && (s[i] == 'f' || s[i] == 'c'); i++);
    if (i != n) { puts("-1"); continue; }
    for (i = n; i < n + k; i++) { s[i] = 'f'; }
    s[n += k] = 0;
    int ans = 0;
    for (i = k; i < n; i++) {
      if (s[i] == 'c') {
        if (i < n - 2 && s[i + 1] == 'f' && s[i + 2] == 'f') { ans++; }
        else { ans = -1; break; }
      }
    }
    printf("%d\n", ans);
  }
}
