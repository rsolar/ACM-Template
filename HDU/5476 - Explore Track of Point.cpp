#include <bits/stdc++.h>
using namespace std;

struct Node {
  double x, y;
} A, B, C, M;

inline double dis(Node a, Node b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main() {
  int Case = 0, T;
  scanf("%d", &T);
  while (++Case <= T) {
    scanf("%lf %lf %lf %lf %lf %lf", &A.x, &A.y, &B.x, &B.y, &C.x, &C.y);
    M.x = (B.x + C.x) / 2.0, M.y = (B.y + C.y) / 2.0;
    double a = dis(B, C) / 2.0, b = dis(A, B), h = dis(A, M);
    double r = a * h / (a + b);
    double R = (a * a - r * r) / r / 2.0 + r;
    double ans = 2.0 * R * asin(a / R) + h;
    printf("Case #%d: %.4f\n", Case, ans);
  }
}
