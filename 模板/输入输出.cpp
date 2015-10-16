//输入一个整数
//G++ ONLY?
template <typename T> inline void getInt(T &x) {
  char c = 0;
  while (c < '0' || c > '9') { c = getchar(); };
  x = c - '0';
  while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
}

template <typename T> inline void getInt(T &x) {
  char c = 0; T sign = 1;
  while ((c < '0' || c > '9') && c != '-') { c = getchar(); };
  if (c == '-') { sign = -1; c = getchar(); }
  x = c - '0';
  while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
  x *= sign;
}

//空格作为分隔 读取一行的整数
void getLine(int a[]) {
  int i = 0;
  gets(buf);
  for (char *p = strtok(buf, " "); p; p = strtok(NULL, " ")) {
    sscanf(p, "%d", &a[i++]);
  }
}

//输出一个整数
template <typename T> inline void printInt(T x) {
  if (x > 9) { printInt(x / 10); }
  putchar(x % 10 + '0');
}
