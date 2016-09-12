//线性规划 单纯形法
//n为变量个数, m为不等式个数
//目标: maxmize(∑(c[i] * x[i]), 0 <= i < n)
//约束: ∑(a[i][j] * x[j], 0 <= j < n) <= b[i] and x[i] >= 0, 0 <= i < n
const int MAXN = 1005, MAXM = 1005;
const double EPS = 1e-9, INF = 1e20;
struct Simplex {
  int n, m;
  double a[MAXM][MAXN], b[MAXM], c[MAXN], ret;
  int sgn(double x) { return (fabs(x) < EPS ? 0 : (x < 0 ? -1 : 1)); }
  void init(int _n, int _m) {
    n = _n; m = _m; ret = 0;
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    memset(c, 0, sizeof(c));
  }
  void pivot(int row, int col) {
    b[row] /= a[row][col]; a[row][col] = 1.0 / a[row][col];
    for (int i = 0; i < n; i++) { if (i != col) { a[row][i] *= a[row][col]; } }
    for (int i = 0; i < m; i++) {
      if (i != row && sgn(a[i][col])) {
        b[i] -= a[i][col] * b[row];
        for (int j = 0; j < n; j++) { if (j != col) { a[i][j] -= a[i][col] * a[row][j]; } }
        a[i][col] = -a[i][col] * a[row][col];
      }
    }
    ret += c[col] * b[row];
    for (int i = 0; i < n; i++) { if (i != col) { c[i] -= c[col] * a[row][i]; } }
    c[col] = -c[col] * a[row][col];
    //debug();
  }
  double simplex() {
    int row, col;
    while (true) {
      for (col = 0; col < n; col++) { if (sgn(c[col]) > 0) { break; } }
      if (col == n) { return ret; }
      double mn = INF;
      for (int i = 0; i < m; i++) {
        if (sgn(a[i][col]) > 0 && b[i] / a[i][col] < mn) { mn = b[i] / a[i][col], row = i; }
      }
      if (mn == INF) { return INF; }
      pivot(row, col);
    }
  }
  void debug() {
    printf("c");
    for (int i = 0; i < n; i++) { printf(" %6.3f", c[i]); }
    printf(" %6.3f\n", ret);
    for (int i = 0; i < m; i++) {
      printf("a");
      for (int j = 0; j < n; j++) { printf(" %6.3f", a[i][j]); }
      printf(" %6.3f\n", b[i]);
    }
  }
} sp;
//最小费用最大流
//每个等式为图中一个顶点, 添加源点S和汇点T
//如果一个等式右边为非负整数c, 从源点S向该等式对应的顶点连接一条容量为c, 权值为0的有向边
//如果一个等式右边为负整数c, 从该等式对应的顶点向汇点T连接一条容量为c, 权值为0的有向边
//如果一个变量X[i]在第j个等式中出现为X[i], 在第k个等式中出现为-X[i], 从顶点j向顶点k连接一条容量为INF, 权值为V[i]的有向边
//如果一个变量Y[i]在第j个等式中出现为Y[i], 在第k个等式中出现为-Y[i], 从顶点j向顶点k连接一条容量为∞, 权值为0的有向边
//构图以后, 求从源点S到汇点T的最小费用最大流, 费用值就是结果
