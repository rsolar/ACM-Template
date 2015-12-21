//分数类 保持最简
#define abs(x) ((x)>=0?(x):-(x))
template<typename T> struct Fraction {
  T a, b; //分子, 分母
  T sign(T x) { return x > 0 ? 1 : -1; }
  Fraction(T x = 0): a(x) , b(1) {}
  Fraction(T x, T y) {
    T m = __gcd(abs(x) , abs(y));
    a = x / m * sign(y); b = (a == 0 ? 1 : abs(y / m));
  }
  Fraction operator+(const Fraction &f) {
    T m = __gcd(b, f.b);
    return Fraction(f.b / m * a + b / m * f.a, b / m * f.b);
  }
  Fraction operator-(const Fraction &f) {
    T m = __gcd(b, f.b);
    return Fraction(f.b / m * a - b / m * f.a, b / m * f.b);
  }
  Fraction operator*(const Fraction &f) {
    T m1 = __gcd(abs(a), f.b), m2 = __gcd(b, abs(f. a));
    return Fraction((a / m1) * (f.a / m2), (b / m2) * (f.b / m1));
  }
  Fraction operator/(const Fraction &f) {
    return (*this) * Fraction(f.b, f.a);
  }
  void print() {
    if (a == 0) { putchar('0'); } else if (b == 1) { printf("%d", a); } else { printf("%d//%d", a, b); }
  }
  friend ostream &operator<<(ostream &out, const Fraction &f) {
    if (f.a == 0) { out << 0; } else if (f.b == 1) { out << f.a; } else { out << f.a << '/' << f.b; }
    return out;
  }
};
