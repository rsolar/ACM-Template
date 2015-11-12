//hash_fun.h
inline size_t __stl_hash_string(const char *__s) {
  unsigned long __h = 0;
  for (; *__s; ++__s) { __h = 5 * __h + *__s; }
  return size_t(__h);
}
//BKDR Hash Function
inline size_t BKDRHash(const char *str) { /* const */
  size_t h = 0, seed = 131; // 31 131 1313 13131 131313 etc..
  while (*str) { h = h * seed + (*str++); }
  return (h & 0x7FFFFFFF);
}
//hash_map<string, XXX>
//C++: using namespace stdext;
//G++: using namespace __gnu_cxx;
struct str_hash {
  size_t operator()(const string &str)const {
    return __stl_hash_string(str.c_str());
  }
};
//Manacher 最长回文子串
//最长回文子串对应原串T中的位置: l = (i - R[i]) / 2; r = (i + R[i]) / 2 - 2;
char s[N];
char Mstr[N << 1];
int Mdp[N << 1];
void Manacher(char s[], int len) {
  int l = 0, mx = 0, id = 0;
  Mstr[l++] = '$'; Mstr[l++] = '#';
  for (int i = 0; i < len; i++) { Mstr[l++] = s[i]; Mstr[l++] = '#'; }
  Mstr[l] = 0;
  for (int i = 0; i < l; i++) {
    Mdp[i] = mx > i ? min(Mdp[(id << 1) - i], mx - i) : 1;
    while (Mstr[i + Mdp[i]] == Mstr[i - Mdp[i]]) { Mdp[i]++; }
    if (i + Mdp[i] > mx) { mx = i + Mdp[i]; id = i; }
  }
}
int main() {
  while (~scanf("%s", s)) {
    int len = strlen(s), Mlen = (len << 1) + 2, mxlen = 0, mxpos = 0;
    Manacher(s, len);
    for (int i = 0; i < Mlen; i++) {
      if (mxlen < Mdp[i]) { mxlen = Mdp[i]; mxpos = i; }
    }
    printf("%d\n", mxlen - 1); //s.substr((mxpos - mxlen) >> 1, mxlen - 1);
  }
}
//字符串最小/大表示
int minString(char s[]) {
  int m = strlen(s), i, j, k;
  char ss[m << 1];
  strcpy(ss, s); strcpy(ss + m, s);
  for (i = k = 0, j = 1; k < m && i < m && j < m;) {
    for (k = 0; k < m && ss[i + k] == ss[j + k]; k++);
    if (k < m) {
      if (ss[i + k] > ss[j + k]) { i += k + 1; } //最大则改为<
      else { j += k + 1; }
      if (i == j) { j++; }
    }
  }
  return min(i, j);
}
//strstr 在串s1中查找指定字符串s2的第一次出现
char *strstr(const char *str1, const char *str2);
//KMP O(M+N)
//Next[]的含义：x[i-Next[i]...i-1]=x[0...Next[i]-1]
//Next[i]为满足x[i-z...i-1]=x[0...z-1]的最大z值(就是x的自身匹配)
char x[N], y[N];
int Next[N];
void getNext(char x[], int m, int Next[]) {
  int i = 0, j = -1; Next[0] = -1;
  while (i < m) {
    while (j != -1 && x[i] != x[j]) { j = Next[j]; }
    Next[++i] = ++j;
  }
}
//改进版
void getNext(char x[], int m, int Next[]) {
  int i = 0, j = -1; Next[0] = -1;
  while (i < m) {
    while (j != -1 && x[i] != x[j]) { j = Next[j]; }
    if (x[++i] == x[++j]) { Next[i] = Next[j]; }
    else { Next[i] = j; }
  }
}
//返回x在y中出现的次数, 可以重叠
//x是模式串, y是主串
int KMP_Count(char x[], int m, char y[], int n, int Next[] = Next/*, int &longest, int &lp*/) {
  int i = 0, j = 0, ans = 0;
  //longest = 0; lp = 0;
  while (i < n) {
    while (j != -1 && y[i] != x[j]) { j = Next[j]; }
    i++; j++;
    //if (j > longest) { longest = j; lp = i − j; }
    if (j >= m) { j = Next[j]; ans++; }
  }
  return ans;
}
//扩展KMP
//Next[i]:x[i...m-1]与x[0...m-1]的最长公共前缀
//Extend[i]:y[i...n-1]与x[0...m-1]的最长公共前缀
int Next[N], Extend[N];
void getNext(char x[], int m, int Next[] = Next) {
  int j = 0, k = 1;
  while (j + 1 < m && x[j] == x[j + 1]) { j++; }
  Next[0] = m; Next[1] = j;
  for (int i = 2; i < m; i++) {
    int p = Next[k] + k - 1, l = Next[i - k];
    if (i + l < p + 1) { Next[i] = l; }
    else {
      j = max(0, p - i + 1);
      while (i + j < m && x[i + j] == x[j]) { j++; }
      Next[i] = j; k = i;
    }
  }
}
void getExtend(char x[], int m, char y[], int n, int Next[] = Next, int Extend[] = Extend) {
  getNext(x, m);
  int j = 0, k = 0;
  while (j < n && j < m && x[j] == y[j]) { j++; }
  Extend[0] = j;
  for (int i = 1; i < n; i++) {
    int p = Extend[k] + k - 1, l = Next[i - k];
    if (i + l < p + 1) { Extend[i] = l; }
    else {
      j = max(0, p - i + 1);
      while (i + j < n && j < m && y[i + j] == x[j]) { j++; }
      Extend[i] = j; k = i;
    }
  }
}
//Sunday
int Sunday(char x[], int m, char y[], int n) {
  int next[26] = {0};
  for (int j = 0; j < 26; j++) { next[j] = m + 1; }
  for (int j = 0; j < m; j++) { next[x[j] - 'a'] = m - j; }
  int pos = 0;
  while (pos <= n - m) {
    int i = pos, j;
    for (j = 0; j < m; ++j, ++i) {
      if (y[i] != x[j]) { pos += next[y[pos + m] - 'a']; break; }
    }
    if (j == m) { return pos; }
  }
  return -1;
}
//Rabin-Karp
#define UNSIGNED(x) ((unsigned char)x)
const int d = 257;
int hashMatch(char *s, int m, char *p, int n) {
  if (m > n || m == 0 || n == 0) { return -1; }
  //sv为s子串的hash结果, pv为p的hash结果, base为d的m-1次方
  unsigned sv = UNSIGNED(s[0]), pv = UNSIGNED(p[0]), base = 1;
  int i, j;
  //初始化sv, pv, base
  for (i = 1; i < m; i++) {
    pv = pv * d + UNSIGNED(p[i]);
    sv = sv * d + UNSIGNED(s[i]);
    base = base * d;
  }
  i = m - 1;
  do {
    if (!(sv ^ pv)) {
      for (j = 0; j < m && s[i - m + 1 + j] == p[j]; j++);
      if (j == m) { return i - m + 1; }
    }
    if (++i >= n) { break; }
    //O(1)时间内更新sv, sv + UNSIGNED(s[i - m]) * (~base + 1)等价于sv - UNSIGNED(s[i - m]) * base
    sv = (sv + UNSIGNED(s[i - m]) * (~base + 1)) * d + UNSIGNED(s[i]);
  } while (i < n);
  return -1;
}
//Trie
char buf[M];
struct Trie {
  int Next[N * 20][26], End[N * 20];
  int root, L;
  int newnode() { return L++; }
  void init() {
    memset(Next, -1, sizeof(Next));
    memset(End, 0, sizeof(End));
    L = 0; root = newnode();
  }
  void insert(char buf[]) {
    int len = strlen(buf);
    int now = root;
    for (int i = 0; i < len; i++) {
      int c = buf[i] - 'a';
      if (Next[now][c] == -1) {
        Next[now][c] = newnode();
      }
      now = Next[now][c];
    }
    End[now]++;
  }
  int query(char buf[]) {
    int len = strlen(buf);
    int now = root;
    for (int i = 0; i < len; i++) {
      int c = buf[i] - 'a';
      if (Next[now][c] == -1) { return -1; }
      now = Next[now][c];
    }
    return End[now];
  }
} tr;
//AC自动机
char buf[M];
struct Trie {
  int Next[N * 20][26], Fail[N * 20], End[N * 20];
  int root, L;
  int newnode() {
    memset(Next[L], -1, sizeof(Next[L])); End[L] = 0;
    return L++;
  }
  void init() { L = 0; root = newnode(); }
  void insert(char buf[]) {
    int len = strlen(buf);
    int now = root;
    for (int i = 0; i < len; i++) {
      int c = buf[i] - 'a';
      if (Next[now][c] == -1) {
        Next[now][c] = newnode();
      }
      now = Next[now][c];
    }
    End[now]++;
  }
  void build() {
    queue<int> que;
    Fail[root] = root;
    for (int i = 0; i < 26; i++) {
      if (Next[root][i] == -1) {
        Next[root][i] = root;
      } else {
        Fail[Next[root][i]] = root;
        que.push(Next[root][i]);
      }
    }
    while (!que.empty()) {
      int now = que.front(); que.pop();
      for (int i = 0; i < 26; i++) {
        if (Next[now][i] == -1) {
          Next[now][i] = Next[Fail[now]][i];
        } else {
          Fail[Next[now][i]] = Next[Fail[now]][i];
          que.push(Next[now][i]);
        }
      }
    }
  }
  int query(char buf[]) {
    int len = strlen(buf);
    int now = root;
    int res = 0;
    for (int i = 0; i < len; i++) {
      int c = buf[i] - 'a';
      now = Next[now][c];
      int temp = now;
      while (temp != root) {
        res += End[temp];
        //End[temp] = 0;
        temp = Fail[temp];
      }
    }
    return res;
  }
} ac;
//后缀数组
/*
* 倍增算法 O(nlogn)
* 待排序数组长度为n, 放在0 ~ n - 1中,在最后面补一个0
* da(str, sa, rnk, height, n + 1, m); //注意是n + 1
* 例如: n = 8; num[] = { 1, 1, 2, 1, 1, 1, 1, 2, $ }; 注意num最后一位为0, 其他大于0
* rnk[] = { 4, 6, 8, 1, 2, 3, 5, 7, 0 }; rnk[0 ~ n - 1]为有效值, rnk[n]必定为0无效值
* sa[] = { 8, 3, 4, 5, 0, 6, 1, 7, 2 }; sa[1 ~ n]为有效值, sa[0]必定为n是无效值
* height[] = { 0, 0, 3, 2, 3, 1, 2, 0, 1 }; height[2 ~ n]为有效值
*/
const int N = 20010;
char str[N];
int rnk[N], height[N], sa[N], t1[N], t2[N], c[N]; //求SA数组需要的中间变量, 不需要赋值
//待排序的字符串放在str数组中, 从str[0]到str[n-1],长度为n,且最大值小于m,
//除s[n-1]外的所有s[i]都大于0, r[n-1]=0
//函数结束以后结果放在sa数组中
bool cmp(int *r, int a, int b, int l) {
  return r[a] == r[b] && r[a + l] == r[b + l];
}

void da(int str[], int sa[], int rnk[], int height[], int n, int m) {
  int i, j, p, *x = t1, *y = t2; n++;
  //第一轮基数排序, 如果s的最大值很大, 可改为快速排序
  for (i = 0; i < m; i++) { c[i] = 0; }
  for (i = 0; i < n; i++) { c[x[i] = str[i]]++; }
  for (i = 1; i < m; i++) { c[i] += c[i - 1]; }
  for (i = n - 1; i >= 0; i--) { sa[--c[x[i]]] = i; }
  for (j = 1; j <= n; j <<= 1) {
    p = 0;
    //利用sa数组排序第二关键字
    for (i = n - j; i < n; i++) { y[p++] = i; } //后面的j个数第二关键字为空的最小
    for (i = 0; i < n; i++)if (sa[i] >= j) { y[p++] = sa[i] - j; }
    //这样数组y保存的就是按照第二关键字排序的结果
    //基数排序第一关键字
    for (i = 0; i < m; i++) { c[i] = 0; }
    for (i = 0; i < n; i++) { c[x[y[i]]]++; }
    for (i = 1; i < m; i++) { c[i] += c[i - 1]; }
    for (i = n - 1; i >= 0; i--) { sa[--c[x[y[i]]]] = y[i]; }
    swap(x, y); p = 1; x[sa[0]] = 0;
    for (i = 1; i < n; i++) { //根据sa和x数组计算新的x数组
      x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
    }
    if (p >= n) { break; }
    m = p; //下次基数排序的最大值
  }
  int k = 0; n--;
  for (i = 0; i <= n; i++) { rnk[sa[i]] = i; }
  for (i = 0; i < n; i++) {
    if (k) { k--; }
    j = sa[rnk[i] - 1];
    while (str[i + k] == str[j + k]) { k++; }
    height[rnk[i]] = k;
  }
}
/*
* DC3算法, O(n)
* 所有的相关数组都要开三倍
* da(str, sa, rnk, height, n, m);
*/
const int N = 2005;
#define F(x) ((x)/3+((x)%3==1?0:tb))
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)
int wa[N * 3], wb[N * 3], wv[N * 3], wss[N * 3];
int c0(int *r, int a, int b) {
  return r[a] == r[b] && r[a + 1] == r[b + 1] && r[a + 2] == r[b + 2];
}

int c12(int k, int *r, int a, int b) {
  if (k == 2) { return r[a] < r[b] || (r[a] == r[b] && c12(1, r, a + 1, b + 1)); }
  else { return r[a] < r[b] || (r[a] == r[b] && wv[a + 1] < wv[b + 1]); }
}

void Sort(int *r, int *a, int *b, int n, int m) {
  for (int i = 0; i < n; i++) { wv[i] = r[a[i]]; }
  for (int i = 0; i < m; i++) { wss[i] = 0; }
  for (int i = 0; i < n; i++) { wss[wv[i]]++; }
  for (int i = 1; i < m; i++) { wss[i] += wss[i - 1]; }
  for (int i = n - 1; i >= 0; i--) { b[--wss[wv[i]]] = a[i]; }
}

void dc3(int *r, int *sa, int n, int m) {
  int i, j, *rn = r + n;
  int *san = sa + n, ta = 0, tb = (n + 1) / 3, tbc = 0, p;
  r[n] = r[n + 1] = 0;
  for (i = 0; i < n; i++) { if (i % 3 != 0) { wa[tbc++] = i; } }
  Sort(r + 2, wa, wb, tbc, m);
  Sort(r + 1, wb, wa, tbc, m);
  Sort(r, wa, wb, tbc, m);
  for (p = 1, rn[F(wb[0])] = 0, i = 1; i < tbc; i++) {
    rn[F(wb[i])] = c0(r, wb[i - 1], wb[i]) ? p - 1 : p++;
  }
  if (p < tbc) { dc3(rn, san, tbc, p); }
  else { for (i = 0; i < tbc; i++) { san[rn[i]] = i; } }
  for (i = 0; i < tbc; i++) { if (san[i] < tb) { wb[ta++] = san[i] * 3; } }
  if (n % 3 == 1) { wb[ta++] = n - 1; }
  Sort(r, wb, wa, ta, m);
  for (i = 0; i < tbc; i++) { wv[wb[i] = G(san[i])] = i; }
  for (i = 0, j = 0, p = 0; i < ta && j < tbc; p++) {
    sa[p] = c12(wb[j] % 3, r, wa[i], wb[j]) ? wa[i++] : wb[j++];
  }
  for (; i < ta; p++) { sa[p] = wa[i++]; }
  for (; j < tbc; p++) { sa[p] = wb[j++]; }
}

void da(int str[], int sa[], int rnk[], int height[], int n, int m) {
  for (int i = n; i < n * 3; i++) { str[i] = 0; }
  dc3(str, sa, n + 1, m);
  int i, j, k = 0;
  for (i = 0; i <= n; i++) { rnk[sa[i]] = i; }
  for (i = 0; i < n; i++) {
    if (k) { k--; }
    j = sa[rnk[i] - 1];
    while (str[i + k] == str[j + k]) { k++; }
    height[rnk[i]] = k;
  }
}
//后缀自动机
const int N = 250005;
struct SAM_Node {
  SAM_Node *fa, *next[26];
  int len;
  int id, pos;
  SAM_Node() {}
  SAM_Node(int _len) : len(_len), fa(NULL) { memset(next, 0, sizeof(next)); }
};
SAM_Node SAM_node[N * 2], *SAM_root, *SAM_last;
int SAM_size;

SAM_Node *newSAM_Node(int len) {
  SAM_node[SAM_size] = SAM_Node(len);
  SAM_node[SAM_size].id = SAM_size;
  return &SAM_node[SAM_size++];
}

SAM_Node *newSAM_Node(SAM_Node *p) {
  SAM_node[SAM_size] = *p;
  SAM_node[SAM_size].id = SAM_size;
  return &SAM_node[SAM_size++];
}

void SAM_init() {
  SAM_size = 0; SAM_node[0].pos = 0;
  SAM_root = SAM_last = newSAM_Node(0);
}

void SAM_add(int x, int len) {
  SAM_Node *p = SAM_last, *np = newSAM_Node(p->len + 1);
  np->pos = len;
  SAM_last = np;
  for (; p && !p->next[x]; p = p->fa) { p->next[x] = np; }
  if (!p) { np->fa = SAM_root; return; }
  SAM_Node *q = p->next[x];
  if (q->len == p->len + 1) { np->fa = q; return; }
  SAM_Node *nq = newSAM_Node(q);
  nq->len = p->len + 1;
  q->fa = nq;
  np->fa = nq;
  for (; p && p->next[x] == q; p = p->fa) { p->next[x] = nq; }
}

void SAM_build(char *s) {
  SAM_init();
  for (int i = 0; i < s[i]; i++) { SAM_add(s[i] - 'a', i + 1); }
}
//加入串后进行拓扑排序
char str[N];
int topocnt[N];
SAM_Node *topsam[N * 2];
int n = strlen(str);
SAM_build(str);
memset(topocnt, 0, sizeof(topocnt));
for (int i = 0; i < SAM_size; i++) { topocnt[SAM_node[i].len]++; }
for (int i = 1; i <= n; i++) { topocnt[i] += topocnt[i - 1]; }
for (int i = 0; i < SAM_size; i++) { topsam[--topocnt[SAM_node[i].len]] = &SAM_node[i]; }
//多串的建立,注意SAM_init()的调用
void SAM_build(char *s) {
  int len = strlen(s);
  SAM_last = SAM_root;
  for (int i = 0; i < len; i++) {
    if (!SAM_last->next[s[i] - '0'] || !(SAM_last->next[s[i] - '0']->len == i + 1)) {
      SAM_add(s[i] - '0', i + 1);
    } else {
      SAM_last = SAM_last->next[s[i] - '0'];
    }
  }
}
//回文自动机
char buf[M];
struct PalindromicTree {
  int Next[N][26], Fail[N], cnt[N], len[N];
  int num[N]; //以i节点为回文串的末尾字符结尾的但不包含本条路径上的回文串的数目
  int tol, S[N];
  int root, L;
  int newnode(int l) {
    memset(Next[L], 0, sizeof(Next[L]));
    cnt[L] = 0; num[L] = 0; len[L] = l;
    return L++;
  }
  void init() {
    L = 0; tol = 0; S[tol] = -1; root = newnode(0); Fail[root] = newnode(-1);
  }
  int getFail(int x) {
    while (S[tol - len[x] - 1] != S[tol]) { x = Fail[x]; }
    return x;
  }
  void Insert(char buf[]) {
    int len = strlen(buf);
    int cur = root, now;
    for (int i = 0; i < len; i++) {
      int c = buf[i] - 'a';
      S[++tol] = c;
      cur = getFail(cur);
      if (Next[cur][c] == 0) {
        now = newnode(len[cur] + 2);
        Fail[now] = Next[getFail(Fail[cur])][c];
        Next[cur][c] = now;
        num[now] = num[Fail[now]] + 1;
      }
      cur = Next[cur][c];
      cnt[cur]++;
    }
    for (int i = L - 1; i >= 0; --i) { cnt[Fail[i]] += cnt[i]; }
  }
} pat;
