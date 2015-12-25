//iostream关闭同步
ios_base::sync_with_stdio(false); cin.tie(NULL);
//输入一个非负整数
template<typename T> inline bool getInt(T &x) {
  char c;
  while (!isdigit(c = getchar())) { if (c == EOF) { return false; } }
  for (x = 0; isdigit(c); c = getchar()) { x = x * 10 + c - '0'; }
  return true;
}
//输入一个整数
template<typename T> inline bool getInt(T &x) {
  char c; bool neg = false;
  while ((c = getchar()) != '-' && c != EOF && !isdigit(c));
  if (c == EOF) { return false; }
  if (c == '-') { neg = true; c = getchar(); }
  for (x = 0; isdigit(c); c = getchar()) { x = x * 10 + c - '0'; }
  if (neg) { x = -x; } return true;
}
//输入一个数(int, long long, float, double)
template<typename T> inline bool getNum(T &x) {
  char c; bool neg = false;
  while ((c = getchar()) != '-' && c != '.' && c != EOF && !isdigit(c));
  if (c == EOF) { return false; }
  if (c == '-') { neg = true; c = getchar(); }
  for (x = 0; isdigit(c); c = getchar()) { x = x * 10 + c - '0'; }
  if (c == ' ' || c == '\n' || c == EOF) { if (neg) { x = -x; } return true; }
  for (T bit = 0.1; isdigit(c = getchar()); bit *= 0.1) { x += (c - '0') * bit; }
  if (neg) { x = -x; } return true;
}
//空格作为分隔 读取一行的整数
inline void getLine(int a[]) {
  int i = 0; gets(buf);
  for (char *p = strtok(buf, " "); p; p = strtok(NULL, " ")) {
    sscanf(p, "%d", &a[i++]);
  }
}
//配合fread
const int BUFSIZE = 20 << 20;
char BUF[BUFSIZE], *pt, *ed;
inline void Read() { pt = BUF; ed = BUF +  fread(BUF, sizeof(char), BUFSIZE, stdin); }
inline bool hasNext() {
  for (char *x = pt; x < ed; ++x) {
    if (isspace(*x)) { continue; }
    if (isalnum(*x)) { return true; }
  }
  return false;
}
template<typename T> inline void getInt(T &x) {
  x = 0;
  for (bool flag = 0, neg = 0;; ++pt) {
    if (isdigit(*pt)) { x = (x << 3) + (x << 1) + *pt - '0'; flag = true; }
    else if (flag) { if (neg) { x = -x; } break; }
    else if (*pt == '-') { neg = true; }
  }
}
inline void getChar(char &x) { x = *pt; ++pt; }
inline void getStr(char *s) { for (; *pt; ++s, ++pt) { *s = *pt; } *s = 0; }
//输出一个整数
template<typename T> inline void printInt(T x) {
  if (x > 9) { printInt(x / 10); }
  putchar(x % 10 + '0');
}
