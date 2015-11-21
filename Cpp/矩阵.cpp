//矩阵模板
#define fabs(x) ((x)>=0?(x):-(x))
#define isZero(x) (fabs(x)<1e-10)
template <typename T> struct Matrix {
  int r, c; T m[N][N];
  Matrix(int _r = N, int _c = N): r(_r), c(_c) { init(); }
  void init() { for (int i = 0; i < r; i++) { for (int j = 0; j < c; j++) { m[i][j] = 0; } } }
  void input() { for (int i = 0; i < r; i++) { for (int j = 0; j < c; j++) { scanf("%d", &m[i][j]); } } }
  void print() { for (int i = 0; i < r; i++) { for (int j = 0; j < c; j++) { printf("%d ", m[i][j]); } putchar('\n'); } }
  //初始化为单位矩阵
  void e() { for (int i = 0; i < r; i++) { for (int j = 0; j < c; j++) {  m[i][j] = !(i ^ j); } } }
  T *const operator[](const int i) { return m[i]; }
  Matrix &operator=(const Matrix &mat) {
    for (int i = 0; i < r; i++) { for (int j = 0; j < c; j++) { m[i][j] = mat.m[i][j]; } }
    return *this;
  }
  Matrix &operator=(const T mat[]) {
    for (int i = 0, cnt = 0; i < r; i++) { for (int j = 0; j < c; j++) { m[i][j] = mat[cnt++]; } }
    return *this;
  }
  Matrix operator+(const Matrix &mat) {
    Matrix rt(r, c); rt = *this;
    for (int i = 0; i < r; i++) { for (int j = 0; j < c; j++) { m[i][j] += mat.m[i][j]; } }
    return rt;
  }
  Matrix operator-(const Matrix &mat) {
    Matrix rt(r, c); rt = *this;
    for (int i = 0; i < r; i++) { for (int j = 0; j < c; j++) { m[i][j] -= mat.m[i][j]; } }
    return rt;
  }
  Matrix operator*(const Matrix &mat) {
    Matrix rt(r, mat.c);
    for (int i = 0; i < r; i++) {
      for (int k = 0; k < c; k++) {
        if (!isZero(m[i][k])) {
          for (int j = 0; j < mat.c; j++) { rt.m[i][j] = rt.m[i][j] + m[i][k] * mat.m[k][j]; }
        }
      }
    }
    return rt;
  }
  //矩阵快速幂
  Matrix operator^(ll n) {
    Matrix rt(r, c), base(r, c); rt.e(); base = *this;
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
    for (int i = 0; i < c; i++) { for (int j = 0; j < r; j++) { rt.m[i][j] = m[j][i]; } }
    return rt;
  }
  //求逆矩阵 限double
  bool inv(Matrix &a) {
    int i, j, k, is[N], js[N]; double t;
    if (a.r != a.c) { return false; }
    for (k = 0; k < a.r; k++) {
      for (t = 0, i = k; i < a.r; i++) {
        for (j = k; j < a.r; j++) {
          if (fabs(a.m[i][j]) > t) {
            t = fabs(a.m[is[k] = i][js[k] = j]);
          }
        }
      }
      if (isZero(t)) { return false; }
      if (is[k] != k) { for (j = 0; j < a.r; j++) { swap(a.m[k][j], a.m[is[k]][j]); } }
      if (js[k] != k) { for (i = 0; i < a.r; i++) { swap(a.m[i][k], a.m[i][js[k]]); } }
      a.m[k][k] = 1.0 / a.m[k][k];
      for (j = 0; j < a.r; j++) { if (j != k) { a.m[k][j] *= a.m[k][k]; } }
      for (i = 0; i < a.r; i++) {
        if (i != k) {
          for (j = 0; j < a.r; j++) {
            if (j != k) { a.m[i][j] -= a.m[i][k] * a.m[k][j]; }
          }
        }
      }
      for (i = 0; i < a.r; i++) { if (i != k) { a.m[i][k] *= -a.m[k][k]; } }
    }
    for (k = a.r - 1; k >= 0; k--) {
      for (j = 0; j < a.r; j++) { if (js[k] != k) { swap(a.m[k][j], a.m[js[k]][j]); } }
      for (i = 0; i < a.r; i++) { if (is[k] != k) { swap(a.m[i][k], a.m[i][is[k]]); } }
    }
    return true;
  }
  //求行列式
  double det(const Matrix &a) {
    int i, j, k, sign = 0; double b[N][N], ret = 1, t;
    if (a.r != a.c) { return 0; }
    for (i = 0; i < a.r; i++) { for (j = 0; j < a.c; j++) { b[i][j] = a.m[i][j]; } }
    for (i = 0; i < a.r; i++) {
      if (isZero(b[i][i])) {
        for (j = i + 1; j < a.r; j++) { if (!isZero(b[j][i])) { break; } }
        if (j == a.r) { return 0; }
        for (k = i; k < a.r; k++) { swap(b[i][k], b[j][k]); }
        sign++;
      }
      ret *= b[i][i];
      for (k = i + 1; k < a.r; k++) { b[i][k] /= b[i][i]; }
      for (j = i + 1; j < a.r; j++) { for (k = i + 1; k < a.r; k++) { b[j][k] -= b[j][i] * b[i][k]; } }
    }
    if (sign & 1) { ret = -ret; }
    return ret;
  }
};
