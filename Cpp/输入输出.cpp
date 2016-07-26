//关闭同步
ios_base::sync_with_stdio(false); cin.tie(NULL);
//输入一个非负整数
template<typename T> void getn(T &x) {
  char c;
  while (!isdigit(c = getchar()));
  for (x = 0; isdigit(c); c = getchar()) { x = x * 10 + c - '0'; }
}
//输入一个整数
template<typename T> void getn(T &x) {
  char c; bool neg = false;
  while ((c = getchar()) != '-' && !isdigit(c));
  if (c == '-') { neg = true; c = getchar(); }
  for (x = 0; isdigit(c); c = getchar()) { x = x * 10 + c - '0'; }
  if (neg) { x = -x; }
}
//输入一个数(int, long long, float, double)
template<typename T> void getn(T &x) {
  char c; bool neg = false;
  while ((c = getchar()) != '-' && c != '.' && !isdigit(c));
  if (c == '-') { neg = true; c = getchar(); }
  for (x = 0; isdigit(c); c = getchar()) { x = x * 10 + c - '0'; }
  if (c == ' ' || c == '\n' || c == EOF) { if (neg) { x = -x; } return; }
  for (T bit = 0.1; isdigit(c = getchar()); bit *= 0.1) { x += (c - '0') * bit; }
  if (neg) { x = -x; }
}
//空格作为分隔 读取一行的整数
const int BUFSIZE = 20 << 20;
char BUF[BUFSIZE];
void getl(int a[]) {
  int i = 0; gets(BUF);
  for (char *p = strtok(BUF, " "); p; p = strtok(NULL, " ")) { sscanf(p, "%d", &a[i++]); }
}
//配合fread
const int BUFSIZE = 20 << 20;
char BUF[BUFSIZE], *pt, *ed;
void read() { pt = BUF; ed = BUF + fread(BUF, sizeof(char), BUFSIZE, stdin); }
bool hasnext() {
  for (char *x = pt; x < ed; x++) {
    if (isspace(*x)) { continue; }
    if (isalnum(*x)) { return true; }
  }
  return false;
}
template<typename T> void nextn(T &x) {
  x = 0;
  for (bool flag = 0, neg = 0;; pt++) {
    if (isdigit(*pt)) { x = x * 10 + *pt - '0'; flag = true; }
    else if (flag) { if (neg) { x = -x; } break; }
    else if (*pt == '-') { neg = true; }
  }
}
inline void nextc(char &x) { x = *pt; ++pt; }
void nexts(char *s) { for (; *pt; s++, pt++) { *s = *pt; } *s = 0; }
//输出一个正整数
template<typename T> void printn(T x) {
  if (x > 9) { printn(x / 10); }
  putchar(x % 10 + '0');
}
