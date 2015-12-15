//矩阵模板
#define fabs(x) ((x)>=0?(x):-(x))
#define isZero(x) (fabs(x)<1e-10)
template <typename T> struct Matrix {
  int r, c; T m[N][N];
  Matrix(int _r = N, int _c = N): r(_r), c(_c) { init(); }
  Matrix(const Matrix &mat): r(mat.r), c(mat.c) {
    for (int i = 0; i < r; i++) { for (int j = 0; j < c; j++) { m[i][j] = mat.m[i][j]; } }
  }
  void init() { for (int i = 0; i < r; i++) { for (int j = 0; j < c; j++) { m[i][j] = 0; } } }
  void input() { for (int i = 0; i < r; i++) { for (int j = 0; j < c; j++) { scanf("%d", &m[i][j]); } } }
  void print() { for (int i = 0; i < r; i++) { for (int j = 0; j < c; j++) { printf("%d%c", m[i][j], j == c - 1 ? '\n' : ' '); } } }
  //初始化为单位矩阵
  void e() { for (int i = 0; i < r; i++) { for (int j = 0; j < c; j++) {  m[i][j] = !(i ^ j); } } }
  T *const operator[](const int i) { return m[i]; }
  Matrix &operator=(const Matrix &mat) {
    r = mat.r; c = mat.c;
    for (int i = 0; i < r; i++) { for (int j = 0; j < c; j++) { m[i][j] = mat.m[i][j]; } }
    return *this;
  }
  Matrix &operator=(const T a[]) {
    for (int i = 0, cnt = 0; i < r; i++) { for (int j = 0; j < c; j++) { m[i][j] = a[cnt++]; } }
    return *this;
  }
  Matrix operator+(const Matrix &mat) {
    Matrix rt = *this;
    for (int i = 0; i < r; i++) { for (int j = 0; j < c; j++) { m[i][j] += mat.m[i][j]; } }
    return rt;
  }
  Matrix operator-(const Matrix &mat) {
    Matrix rt = *this;
    for (int i = 0; i < r; i++) { for (int j = 0; j < c; j++) { m[i][j] -= mat.m[i][j]; } }
    return rt;
  }
  Matrix operator*(const Matrix &mat) {
    Matrix rt(r, mat.c);
    for (int i = 0; i < r; i++) {
      for (int k = 0; k < c; k++) {
        if (!isZero(m[i][k])) {
          for (int j = 0; j < mat.c; j++) { rt[i][j] = (rt[i][j] + m[i][k] * mat.m[k][j]) % M; }
        }
      }
    }
    return rt;
  }
  //矩阵快速幂
  Matrix operator^(ll n) {
    Matrix rt(r, c), base = *this; rt.e();
    while (n) {
      if (n & 1) { rt = rt * base; }
      base = base * base; n >>= 1;
    }
    return rt;
  }
  bool operator==(const Matrix &mat) {
    if (r != mat.r || c != mat.c) { return false; }
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        if (!isZero(m[i][j] - mat.m[i][j])) { return false; }
      }
    }
    return true;
  }
  //矩阵转置
  Matrix trans() {
    Matrix rt(c, r);
    for (int i = 0; i < c; i++) { for (int j = 0; j < r; j++) { rt[i][j] = m[j][i]; } }
    return rt;
  }
  //求逆矩阵 限double
  bool inv(Matrix &a) {
    if (r != c) { return false; }
    int is[N], js[N]; a = *this;
    for (int k = 0; k < a.r; k++) {
      double t = 0;
      for (int i = k; i < a.r; i++) {
        for (int j = k; j < a.r; j++) {
          if (fabs(a[i][j]) > t) { t = fabs(a[is[k] = i][js[k] = j]); }
        }
      }
      if (isZero(t)) { return false; }
      if (is[k] != k) { for (int j = 0; j < a.r; j++) { swap(a[k][j], a[is[k]][j]); } }
      if (js[k] != k) { for (int i = 0; i < a.r; i++) { swap(a[i][k], a[i][js[k]]); } }
      a[k][k] = 1.0 / a[k][k];
      for (int j = 0; j < a.r; j++) { if (j != k) { a[k][j] *= a[k][k]; } }
      for (int i = 0; i < a.r; i++) {
        if (i != k) { for (int j = 0; j < a.r; j++) { if (j != k) { a[i][j] -= a[i][k] * a[k][j]; } } }
      }
      for (int i = 0; i < a.r; i++) { if (i != k) { a[i][k] *= -a[k][k]; } }
    }
    for (int k = a.r - 1; k >= 0; k--) {
      for (int j = 0; j < a.r; j++) { if (js[k] != k) { swap(a[k][j], a[js[k]][j]); } }
      for (int i = 0; i < a.r; i++) { if (is[k] != k) { swap(a[i][k], a[i][is[k]]); } }
    }
    return true;
  }
  //求行列式
  double det() {
    int sign = 0; double ret = 1.0;
    if (r != c) { return 0; }
    Matrix a = *this;
    for (int i = 0, j; i < r; i++) {
      if (isZero(a[i][i])) {
        for (j = i + 1; j < r; j++) { if (!isZero(a[j][i])) { break; } }
        if (j == r) { return 0; }
        for (int k = i; k < r; k++) { swap(a[i][k], a[j][k]); }
        sign++;
      }
      ret *= a[i][i];
      for (int k = i + 1; k < r; k++) { a[i][k] /= a[i][i]; }
      for (int j = i + 1; j < r; j++) { for (int k = i + 1; k < r; k++) { a[j][k] -= a[j][i] * a[i][k]; } }
    }
    if (sign & 1) { ret = -ret; }
    return ret;
  }
};
