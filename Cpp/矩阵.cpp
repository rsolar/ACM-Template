//矩阵类
template<typename T> struct Matrix {
  vector<T> a; int h, w;
  Matrix(): a(), h(), w() {}
  Matrix(const Matrix &v): a(v.a), h(v.h), w(v.w) {}
  Matrix(const int &_h, const int &_w): a(_h * _w), h(_h), w(_w) { }
  static Matrix e(const int &_h, const int &_w) {
    Matrix res(_h, _w);
    for (int i = 0, n = min(_h, _w); i < n; i++) { res[i][i] = T(1); }
    return res;
  }
  static Matrix e(const Matrix &v) { return e(v.h, v.w); }
  T *operator[](const int &v) { return &a[v * w]; }
  const T *operator[](const int &v)const { return &a[v * w]; }
  Matrix &operator+=(const Matrix &b) {
    for (int i = 0, n = h * w; i < n; i++) { a[i] += b.a[i]; }
    return *this;
  }
  Matrix &operator-=(const Matrix &b) { return *this += -b; }
  Matrix &operator*=(const Matrix &b) {
    Matrix c(h, b.w);
    for (int i = 0; i < h; i++) {
      for (int k = 0; k < w; k++) {
        const T &tmp = (*this)[i][k];
        if (isZero(tmp)) { continue; }
        for (int j = 0; j < b.w; j++) { c[i][j] = (c[i][j] + tmp * b[k][j])/*%M*/; }
      }
    }
    swap(a, c.a); h = c.h; w = c.w; return *this;
  }
  Matrix operator-()const {
    Matrix ret(*this);
    for (int i = 0, n = h * w; i < n; i++) { ret.a[i] = -ret.a[i]; }
    return ret;
  }
  Matrix operator+(const Matrix &b)const { return Matrix(*this) += b; }
  Matrix operator-(const Matrix &b)const { return Matrix(*this) -= b; }
  Matrix operator*(const Matrix &b)const { return Matrix(*this) *= b; }
  Matrix operator^(const ll &v)const {
    Matrix ret(e(*this)), t(*this);
    for (ll b = v; b; b >>= 1) { if (b & 1) { ret *= t; } t *= t; }
    return ret;
  }
  bool operator==(const Matrix &v)const {
    if (h != v.h || w != v.w) { return false; }
    for (int i = 0, n = h * w; i < n; i++) { if (!isZero(a[i] - v.a[i])) { return false; } }
    return true;
  }
  bool operator!=(const Matrix &v)const { return !(*this == v); }
  T abs(const T &v)const { return v < 0 ? -v : v; }
  bool isZero(const T &v)const { return abs(v) < 1e-10; }
  void trans() {
    Matrix c(w, h);
    for (int i = 0; i < w; i++) { for (int j = 0; j < h; j++) { c[i][j] = a[j][i]; } }
    *this = c;
  }
  void input() { for (int i = 0, n = h * w; i < n; i++) { scanf("%d", &a[i]); } }
  void print()const {
    for (int i = 0, n = h * w; i < n; i++) { printf("%d%c", a[i], i % w == w - 1 ? '\n' : ' '); }
  }
  friend istream &operator>>(istream &in, Matrix &b) {
    for (int i = 0, n = b.h * b.w; i < n; i++) { in >> b.a[i]; }
    return in;
  }
  friend ostream &operator<<(ostream &out, const Matrix &b) {
    for (int i = 0, n = b.h * b.w; i < n; i++) { out << b.a[i] << (i % b.w == b.w - 1 ? '\n' : ' '); }
    return out;
  }
  //求逆矩阵 限double 可逆则返回true 结果在参数中
  bool inv(Matrix &v)const {
    if (h != w) { return false; }
    int is[N], js[N]; v = *this;
    for (int k = 0; k < h; k++) {
      double t = 0;
      for (int i = k; i < h; i++) {
        for (int j = k; j < h; j++) {
          if (abs(v[i][j]) > t) { t = abs(v[is[k] = i][js[k] = j]); }
        }
      }
      if (isZero(t)) { return false; }
      if (is[k] != k) { for (int j = 0; j < h; j++) { swap(v[k][j], v[is[k]][j]); } }
      if (js[k] != k) { for (int i = 0; i < h; i++) { swap(v[i][k], v[i][js[k]]); } }
      v[k][k] = 1.0 / v[k][k];
      for (int j = 0; j < h; j++) { if (j != k) { v[k][j] *= v[k][k]; } }
      for (int i = 0; i < h; i++) {
        if (i != k) { for (int j = 0; j < h; j++) { if (j != k) { v[i][j] -= v[i][k] * v[k][j]; } } }
      }
      for (int i = 0; i < h; i++) { if (i != k) { v[i][k] *= -v[k][k]; } }
    }
    for (int k = h - 1; k >= 0; k--) {
      for (int j = 0; j < h; j++) { if (js[k] != k) { swap(v[k][j], v[js[k]][j]); } }
      for (int i = 0; i < h; i++) { if (is[k] != k) { swap(v[i][k], v[i][is[k]]); } }
    }
    return true;
  }
  //求行列式 限double
  double det()const {
    if (h != w) { return 0; }
    int sign = 0; double ret = 1.0; Matrix c(*this);
    for (int i = 0, j, k; i < h; i++) {
      if (isZero(c[i][i])) {
        for (j = i + 1; j < h && isZero(c[j][i]); j++);
        if (j == h) { return 0; }
        for (k = i; k < h; k++) { swap(c[i][k], c[j][k]); }
        sign++;
      }
      ret *= c[i][i];
      for (k = i + 1; k < h; k++) { c[i][k] /= c[i][i]; }
      for (j = i + 1; j < h; j++) { for (k = i + 1; k < h; k++) { c[j][k] -= c[j][i] * c[i][k]; } }
    }
    return sign & 1 ? -ret : ret;
  }
};
