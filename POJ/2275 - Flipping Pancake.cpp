#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

#define N 35

int n, a[N];
vector<int> ans;

void flip(int pos) {
  reverse(a + 1, a + pos + 1);
  ans.push_back(pos);
}

int main() {
  while (scanf("%d", &n), n) {
    ans.clear();
    for (int i = 1; i <= n; i++) {
      scanf("%d", &a[i]);
    }
    for (int i = n; i > 0; i--) {
      if (a[i] != i) {
        int pos = find(a + 1, a + i + 1, i) - a;
        if (pos != 1) { flip(pos); }
        flip(i);
      }
    }
    printf("%d", ans.size());
    for (size_t i = 0; i < ans.size(); i++) {
      printf(" %d", ans[i]);
    }
    putchar('\n');
  }
}
