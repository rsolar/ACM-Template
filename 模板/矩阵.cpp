#define fabs(x) ((x)>=0?(x):-(x))
#define isZero(x) (fabs(x)<1e-10)

template <typename T> struct Matrix {
  int r, c;
  T m[N][N];
  void init() {
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        m[i][j] = 0;
      }
    }
  }
  Matrix(int _r = N, int _c = N): r(_r), c(_c) { init(); }
  void e() {
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        m[i][j] = !(i ^ j);
      }
    }
  }
  Matrix &operator=(const Matrix &mat) {
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        m[i][j] = mat.m[i][j];
      }
    }
    return *this;
  }
  Matrix &operator=(const int mat[]) {
    for (int i = 0, cnt = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        m[i][j] = mat[cnt++];
      }
    }
    return *this;
  }
  Matrix operator+(const Matrix &mat) {
    Matrix rt(r, c); rt = *this;
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        m[i][j] += mat.m[i][j];
      }
    }
    return rt;
  }
  Matrix operator-(const Matrix &mat) {
    Matrix rt(r, c); rt = *this;
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        m[i][j] -= mat.m[i][j];
      }
    }
    return rt;
  }
  Matrix operator*(const Matrix &mat) {
    Matrix rt(r, mat.c);
    for (int i = 0; i < r; i++) {
      for (int k = 0; k < c; k++) {
        if (!isZero(m[i][k])) {
          for (int j = 0; j < mat.c; j++) {
            rt.m[i][j] = rt.m[i][j] + m[i][k] * mat.m[k][j];
          }
        }
      }
    }
    return rt;
  }
  Matrix operator^(int n) {
    Matrix rt(r, c), base(r, c); rt.e(); base = *this;
    while (n) {
      if (n & 1) { rt = rt * base; }
      base = base * base;
      n >>= 1;
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
  Matrix trans() {
    Matrix rt(c, r);
    for (int i = 0; i < c; i++) {
      for (int j = 0; j < r; j++) {
        rt.m[i][j] = m[j][i];
      }
    }
    return rt;
  }
  void print() {
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        printf("%d ", m[i][j]);
      }
      putchar('\n');
    }
  }
};

//求逆矩阵
int inv(Matrix &a) {
  int i, j, k, is[N], js[N];
  double t;
  if (a.r != a.c) { return 0; }
  for (k = 0; k < a.r; k++) {
    for (t = 0, i = k; i < a.r; i++) {
      for (j = k; j < a.r; j++) {
        if (fabs(a.m[i][j]) > t) {
          t = fabs(a.m[is[k] = i][js[k] = j]);
        }
      }
    }
    if (isZero(t)) { return 0; }
    if (is[k] != k) {
      for (j = 0; j < a.r; j++) {
        t = a.m[k][j], a.m[k][j] = a.m[is[k]][j], a.m[is[k]][j] = t;
      }
    }
    if (js[k] != k) {
      for (i = 0; i < a.r; i++) {
        t = a.m[i][k], a.m[i][k] = a.m[i][js[k]], a.m[i][js[k]] = t;
      }
    }
    a.m[k][k] = 1.0 / a.m[k][k];
    for (j = 0; j < a.r; j++) {
      if (j != k) {
        a.m[k][j] *= a.m[k][k];
      }
    }
    for (i = 0; i < a.r; i++) {
      if (i != k) {
        for (j = 0; j < a.r; j++) {
          if (j != k) {
            a.m[i][j] -= a.m[i][k] * a.m[k][j];
          }
        }
      }
    }
    for (i = 0; i < a.r; i++) {
      if (i != k) { a.m[i][k] *= -a.m[k][k]; }
    }
  }
  for (k = a.r - 1; k >= 0; k--) {
    for (j = 0; j < a.r; j++) {
      if (js[k] != k) {
        t = a.m[k][j], a.m[k][j] = a.m[js[k]][j], a.m[js[k]][j] = t;
      }
    }
    for (i = 0; i < a.r; i++) {
      if (is[k] != k) {
        t = a.m[i][k], a.m[i][k] = a.m[i][is[k]], a.m[i][is[k]] = t;
      }
    }
  }
  return 1;
}

//求行列式
double det(const Matrix &a) {
  int i, j, k, sign = 0;
  double b[N][N], ret = 1, t;
  if (a.r != a.c) { return 0; }
  for (i = 0; i < a.r; i++) {
    for (j = 0; j < a.c; j++) {
      b[i][j] = a.m[i][j];
    }
  }
  for (i = 0; i < a.r; i++) {
    if (isZero(b[i][i])) {
      for (j = i + 1; j < a.r; j++) {
        if (!isZero(b[j][i])) {
          break;
        }
      }
      if (j == a.r) { return 0; }
      for (k = i; k < a.r; k++) {
        t = b[i][k], b[i][k] = b[j][k], b[j][k] = t;
      }
      sign++;
    }
    ret *= b[i][i];
    for (k = i + 1; k < a.r; k++) {
      b[i][k] /= b[i][i];
    }
    for (j = i + 1; j < a.r; j++) {
      for (k = i + 1; k < a.r; k++) {
        b[j][k] -= b[j][i] * b[i][k];
      }
    }
  }
  if (sign & 1) { ret = -ret; }
  return ret;
}
