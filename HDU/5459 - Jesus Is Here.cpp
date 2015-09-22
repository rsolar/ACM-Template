#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define N 222222
#define M 530600414

struct Node {
  ll len, cnt, sum, ans;
} a[N];
int n;

void init() {
  a[3] = {3, 1, 1, 0};
  a[4] = {5, 1, 3, 0};
  for (int i = 5; i <= 201314; i++) {
    a[i].len = (a[i - 2].len + a[i - 1].len) % M;
    a[i].cnt = (a[i - 2].cnt + a[i - 1].cnt) % M;
    a[i].sum = (a[i - 2].sum + a[i - 1].sum + a[i - 2].len * a[i - 1].cnt) % M;
    a[i].ans = (a[i - 2].ans + a[i - 1].ans + ((a[i - 2].len * a[i - 2].cnt - a[i - 2].sum) % M) * a[i - 1].cnt + a[i - 1].sum * a[i - 2].cnt) % M;
  }
}

int main() {
  init();
  int C = 0, T;
  scanf("%d", &T);
  while (++C <= T) {
    scanf("%d", &n);
    printf("Case #%d: %I64d\n", C, a[n].ans);
  }
}
