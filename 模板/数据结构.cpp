//http://blog.csdn.net/wjf_wzzc/article/details/39672563
//http://blog.csdn.net/wjf_wzzc/article/details/24560117
//http://blog.csdn.net/wjf_wzzc/article/details/38646837

//一维树状数组
//单点修改 + 单点查询 + 区间修改 + 区间查询 + 区间最值
int n;
template<typename T> struct BIT {
  T A[N]; //T B[N]; //区间增减/维护最值
  int lowbit(int x) { return x & (-x); }
  void init() { memset(A, 0, sizeof(A)); /*memset(B, 0, sizeof(B));*/ }
  //单点增减
  void add(int i, T v) { while (i <= n) { A[i] += v; i += lowbit(i); } }
  //单点赋值
  void set(int i, T v) { add(i, v - query(i, i)); }
  //不带区间修改时求前缀和 [1, i]
  T sum(int i) { T ret = 0; while (i) { ret += A[i]; i -= lowbit(i); } return ret; }
  //区间和[i, j]
  T query(int i, int j) { return sum(j) - sum(i - 1); }

  //带区间修改时求前缀和 区间求和用query(i, j)
  T sum(int x) {
    if (x == 0) { return 0; }
    T ret1 = 0, ret2 = 0;
    for (int i = x; i <= n; i += lowbit(i)) { ret1 += A[i]; }
    for (int i = x - 1; i > 0; i -= lowbit(i)) { ret2 += B[i]; }
    return ret1 * x + ret2;
  }
  //带区间修改时区间增减
  void add(int x, T v) {
    for (int i = x; i > 0; i -= lowbit(i)) { A[i] += v; }
    for (int i = x; i <= n; i += lowbit(i)) { B[i] += x * v; }
  }
  void add(int i, int j, T v) { add(j, v); if (i > 1) { add(i - 1, -v); } }

  //维护区间最值 O(log^2(n))
  void modify(int x, T v) {
    B[x] = v;
    for (int i = x; i <= n; i += lowbit(i)) {
      A[i] = max(A[i], v);
      for (int j = 1; j < lowbit(i); j <<= 1) {
        A[i] = max(A[i], A[i - j]);
      }
    }
  }
  T query(int l, int r) {
    T ret = B[r];
    for (;;) {
      ret = max(ret, B[r]);
      if (l == r) { break; }
      for (r -= 1; r - l >= lowbit(r); r -= lowbit(r)) { ret = max(ret, A[r]); }
    }
    return ret;
  }

  //求区间第K大的下标/值 O(log^2(n))
  int getK(int l, int r, int k) {
    while (l <= r) {
      int mid = l + ((r - l) >> 1);
      if (sum(mid) >= k) { r = mid - 1; }
      else { l = mid + 1; }
    }
    return l; //A[l]
  }
};
BIT<int> bit;
//二维树状数组
//单点修改 + 单点求和 + 区域修改 + 区域求和
int n, m;
template<typename T> struct BIT {
  T A[N][N]; //T B[N][N], C[N][N], D[N][N]; //区域求和
  int lowbit(int x) { return x & (-x); }
  void init() { memset(A, 0, sizeof(A)); /*memset(B, 0, sizeof(B)); memset(C, 0, sizeof(C)); memset(D, 0, sizeof(D));*/ }
  //区域和[1][1]-[x][y]
  T sum(int x, int y) {
    T ret = 0;
    for (int i = x; i > 0; i -= lowbit(i)) { for (int j = y; j > 0; j -= lowbit(j)) { ret += A[i][j]; } }
    return ret;
  }
  //单点查询
  T sumv(int x, int y) { return sum(x, y) + sum(x - 1, y - 1) - sum(x, y - 1) - sum(x - 1, y); }
  //单点增减
  void add(int x, int y, T v) {
    for (int i = x; i <= n; i += lowbit(i)) { for (int j = y; j <= m; j += lowbit(j)) { A[i][j] += v; } }
  }
  //单点赋值
  void set(int x, int y, T v) { add(x, y, v - sumv(x, y)); }

  //区域和[x1][y1]-[x2][y2]
  T sum1(int x, int y) {
    return (x + 1) * (y + 1) * sum(x, y) - (y + 1) * sum(x, y) - (x + 1) * sum(x, y) + sum(x, y);
  }
  T sum(int x1, int y1, int x2, int y2) {
    return sum1(x2, y2) - sum1(x1 - 1, y2) - sum1(x2, y1 - 1) + sum1(x1 - 1, y1 - 1);
  }
  //区域增减
  void add(int x, int y, T v, T a[][N]) {
    for (int i = x; i <= n; i += lowbit(i)) { for (int j = y; j <= m; j += lowbit(j)) { a[i][j] += v; } }
  }
  void add(int x1, int y1, int x2, int y2, T v) {
    add(x1, y1, v, A); add(x2 + 1, y1, -v, A);
    add(x1, y2 + 1, -v, A); add(x2 + 1, y2 + 1, v, A);
    add(x1, y1, v * x1, B); add(x2 + 1, y1, -v * (x2 + 1), B);
    add(x1, y2 + 1, -v * x1, B); add(x2 + 1, y2 + 1, v * (x2 + 1), B);
    add(x1, y1, v * y1, C); add(x2 + 1, y1, -v * y1, C);
    add(x1, y2 + 1, -v * (y2 + 1), C); add(x2 + 1, y2 + 1, v * (y2 + 1), C);
    add(x1, y1, v * x1 * y1, D); add(x2 + 1, y1, -v * (x2 + 1) * y1, D);
    add(x1, y2 + 1, -v * x1 * (y2 + 1), D); add(x2 + 1, y2 + 1, v * (x2 + 1) * (y2 + 1), D);
  }
};
BIT<int> bit;
//线段树  单点修改 + 单点查询 + 区间查询
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
template<typename T> struct SegmentTree {
  T data[N << 2];
  T calc(const T &x, const T &y)const { return x + y; }
  void push_up(int rt) { data[rt] = calc(data[rt << 1], data[rt << 1 | 1]); }
  //初始化/建树
  void build(int l, int r, int rt) {
    if (l == r) { scanf("%d", &data[rt]); return; }
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
    push_up(rt);
  }
  //单点修改
  void update(int p, T val, int l, int r, int rt) {
    if (l == r) {
      data[rt] += val; //data[rt] = val;
      return;
    }
    int m = (l + r) >> 1;
    if (p <= m) { update(p, val, lson); }
    else { update(p, val, rson); }
    push_up(rt);
  }
  //区间和
  T query(int L, int R, int l, int r, int rt) {
    if (L <= l && r <= R) { return data[rt]; }
    int m = (l + r) >> 1; T ret = 0;
    if (L <= m) { ret = calc(ret, query(L, R, lson)); }
    if (m < R) { ret = calc(ret, query(L, R, rson)); }
    return ret;
  }
};
SegmentTree<int> st;
//线段树 单点修改 + 单点查询 + 区间修改(延迟标记) + 区间查询
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
template<typename T> struct SegmentTree {
  T data[N << 2], lazy[N << 2];
  T calc(const int &x, const int &y)const { return x + y; }
  void push_up(int rt) { data[rt] = calc(data[rt << 1], data[rt << 1 | 1]); }
  //区间求和的标记下推
  void push_down(int rt, int len) {
    if (lazy[rt]) {
      lazy[rt << 1] += lazy[rt]; data[rt << 1] += lazy[rt] * (len - (len >> 1));
      lazy[rt << 1 | 1] += lazy[rt]; data[rt << 1 | 1] += lazy[rt] * (len >> 1);
      lazy[rt] = 0;
    }
  }
  //区间最值的标记下推
  void push_down(int rt) {
    if (lazy[rt]) {
      lazy[rt << 1] += lazy[rt]; data[rt << 1] += lazy[rt];
      lazy[rt << 1 | 1] += lazy[rt]; data[rt << 1 | 1] += lazy[rt];
      lazy[rt] = 0;
    }
  }
  //初始化/建树
  void build(int l, int r, int rt) {
    lazy[rt] = 0;
    if (l == r) { scanf("%d", &data[rt]); return; } //mx[rt] = a[i];
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
    push_up(rt);
  }
  //单点修改
  void update(int p, T val, int l, int r, int rt) {
    if (l == r) {
      data[rt] += val; //data[rt] = val;
      return;
    }
    push_down(rt, r - l + 1); //push_down(rt);
    int m = (l + r) >> 1;
    if (p <= m) { update(p, val, lson); }
    else { update(p, val, rson); }
    push_up(rt);
  }
  //区间增减
  void update(int L, int R, T val, int l, int r, int rt) {
    if (L <= l && r <= R) {
      lazy[rt] += val;
      data[rt] += val * (r - l + 1); //data[rt] += val;
      return;
    }
    push_down(rt, r - l + 1); //push_down(rt);
    int m = (l + r) >> 1;
    if (L <= m) { update(L, R, val, lson); }
    if (m < R) { update(L, R, val, rson); }
    push_up(rt);
  }
  //区间和
  T query(int L, int R, int l, int r, int rt) {
    if (L <= l && r <= R) { return data[rt]; }
    push_down(rt, r - l + 1); //push_down(rt);
    int m = (l + r) >> 1; T ret = 0;
    if (L <= m) { ret = calc(ret, query(L, R, lson)); }
    if (m < R) { ret = calc(ret, query(L, R, rson)); }
    return ret;
  }
};
SegmentTree<int> st;
//非递归版线段树
const int N = ((131072 << 1) + 10); //节点个数->不小于区间长度+2的最小2的正整数次幂*2+10
#define l(x) ((x)<<1) //x的左儿子，利用堆的性质
#define r(x) (((x)<<1)|1) //x的右儿子，利用堆的性质
template<typename T> struct zkwSegmentTree {
  int M, dl[N], dr[N]; //底层的节点数 节点的左右端点
  int stack[30], top;//栈
  T sum[N]; //节点的区间和
  T add[N]; //延迟标记
  void pushdown(int rt) {
    if (add[rt] && rt < M) {
      add[l(rt)] += add[rt]; sum[l(rt)] += add[rt] * (dr[l(rt)] - dl[l(rt)] + 1);
      add[r(rt)] += add[rt]; sum[r(rt)] += add[rt] * (dr[r(rt)] - dl[r(rt)] + 1);
      add[rt] = 0;
    }
  }
  void build(int n) {
    for (M = 1; M < n + 2; M <<= 1);
    for (int i = 1; i <= n; i++) { //建树
      scanf("%d", &sum[M + i]); dl[M + i] = dr[M + i] = i;
    }
    for (int i = M - 1; i >= 1; i--) { //预处理节点左右端点
      sum[i] = sum[l(i)] + sum[r(i)]; dl[i] = dl[l(i)]; dr[i] = dr[r(i)];
    }
  }
  void pushpath(int x) {
    for (top = 0;; x; x >>= 1) { stack[++top] = x; }
    while (top--) { pushdown(stack[top]); }
  }
  //区间求和
  T query(int tl , int tr) {
    T res = 0;
    for (int tl = tl + M - 1, tr = tr + M + 1; tl ^ tr ^ 1; tl >>= 1, tr >>= 1) {
      if (~tl & 1) {
        if (!insl) { pushpath(insl = tl ^ 1); }
        res += sum[tl ^ 1];
      }
      if (tr & 1) {
        if (!insr) { pushpath(insr = tl ^ 1); }
        res += sum[tr ^ 1];
      }
    }
    return res;
  }
  //区间修改
  void update(int tl , int tr , T val) {
    for (int tl = tl + M - 1, tr = tr + M + 1; tl ^ tr ^ 1; tl >>= 1, tr >>= 1) {
      if (~tl & 1) {
        if (!insl) { pushpath(insl = tl ^ 1); }
        add[tl ^ 1] += val; sum[tl ^ 1] += val * (dr[tl ^ 1] - dl[tl ^ 1] + 1);
      }
      if (tr & 1) {
        if (!insr) { pushpath(insr = tr ^ 1); }
        add[tr ^ 1] += val; sum[tr ^ 1] += val * (dr[tr ^ 1] - dl[tr ^ 1] + 1);
      }
    }
    for (int insl = insl >> 1; insl; insl >>= 1) { sum[insl] = sum[l(insl)] + sum[r(insl)]; }
    for (int insr = insr >> 1; insr; insr >>= 1) { sum[insr] = sum[l(insr)] + sum[r(insr)]; }
  }
};
zkwSegmentTree<int> st;
//------------------------------------------------------------------------------
!!!
//实时开节点的线段树 (无需离散化)
const int N = 60005;
const int M = 2500005;
const int INF = 0x3f3f3f3f;
int n, a[N];
#define lson l,m,ls[rt]
#define rson m+1,r,rs[rt]
struct SegmentTree {
  int ls[M], rs[M], cnt[M], root[N], use[N], tot;
  void init() {
    tot = 0;
    memset(root, 0, sizeof(root));
    memset(ls, 0, sizeof(ls));
    memset(rs, 0, sizeof(rs));
    memset(cnt, 0, sizeof(cnt));
  }
  int new_node() { return ++tot; }
  void update(int p, int val, int l, int r, int &rt) {
    if (!rt) { rt = new_node(); }
    if (l == r) { cnt[rt] += val; return; }
    int m = (l + r) >> 1;
    if (p <= m) { update(p, val, lson); }
    else { update(p, val, rson); }
    cnt[rt] = cnt[ls[rt]] + cnt[rs[rt]];
  }
  int lowbit(int x) { return x & -x; }
  //单点修改
  void modify(int x, int p, int val) {
    for (int i = x; i <= n; i += lowbit(i)) { update(p, val, 0, INF, root[i]); }
  }
  int sum(int x) {
    int ret = 0;
    for (int i = x; i > 0; i -= lowbit(i)) { ret += cnt[ls[use[i]]]; }
    return ret;
  }
  //查询区间第K大
  int query(int ss, int tt, int l, int r, int k) {
    for (int i = ss; i > 0; i -= lowbit(i)) { use[i] = root[i]; }
    for (int i = tt; i > 0; i -= lowbit(i)) { use[i] = root[i]; }
    while (l < r) {
      int m = (l + r) >> 1, tmp = sum(tt) - sum(ss);
      if (k <= tmp) {
        r = m;
        for (int i = ss; i > 0; i -= lowbit(i)) { use[i] = ls[use[i]]; }
        for (int i = tt; i > 0; i -= lowbit(i)) { use[i] = ls[use[i]]; }
      } else {
        l = m + 1; k -= tmp;
        for (int i = ss; i > 0; i -= lowbit(i)) { use[i] = rs[use[i]]; }
        for (int i = tt; i > 0; i -= lowbit(i)) { use[i] = rs[use[i]]; }
      }
    }
    return l;
  }
} st;
//BZOJ1901 区间第k大
int main() {
  int m, l, r, k; char op[5];
  while (~scanf("%d%d", &n, &m)) {
    st.init();
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &a[i]);
      st.modify(i, a[i], 1);
    }
    while (m--) {
      scanf("%s%d%d", op, &l, &r);
      switch (op[0]) {
        case 'Q':
          scanf("%d", &k);
          printf("%d\n", st.query(l - 1, r, 0, INF, k));
          break;
        case 'C':
          st.modify(l, a[l], -1);
          a[l] = r;
          st.modify(l, a[l], 1);
          break;
      }
    }
  }
}
//平衡二叉树 常用操作
//注意这些操作适用于不允许重复值的平衡二叉树(set而非multiset)
//对于允许重复值(拥有cnt域)的实现, 只要在一些+1的地方稍作修改(改成cnt[x])即可
bool find(int v) {
  for (int x = root; x; x = ch[x][key[x] < v]) {
    if (key[x] == v) { return true; }
  }
  return false;
}
int getKth(int k) {
  int x = root;
  while (size[ch[x][0]] + 1 != k) {
    if (k < size[ch[x][0]] + 1) { x = ch[x][0]; }
    else { k -= size[ch[x][0]] + 1; x = ch[x][1]; }
  }
  return key[x];
}
int getRank(int v) {
  int ret = 0, x = root;
  while (x) {
    if (v < key[x]) { x = ch[x][0]; }
    else { ret += size[ch[x][0]] + 1; x = ch[x][1]; }
  }
  return ret;
}
int getPre(int v) {
  int x = root, y = 0;
  while (x) {
    if (v < key[x]) { x = ch[x][0]; }
    else { y = x; x = ch[x][1]; }
  }
  return y;
}
int getNext(int v) {
  int x = root, y = 0;
  while (x) {
    if (v > key[x]) { x = ch[x][1]; }
    else { y = x; x = ch[x][0]; }
  }
  return y;
}
int getMin() {
  if (size[root] == 0) { return -1; }
  int x = root;
  while (ch[x][0]) { x = ch[x][0]; }
  return x;
}
int getMax() {
  if (size[root] == 0) { return -1; }
  int x = root;
  while (ch[x][1]) { x = ch[x][1]; }
  return x;
}
//Debug遍历
void treaval(int x) {
  if (x != 0) {
    treaval(ch[x][0]);
    printf("Node%2d:lson %2d rson %2d size = %2d ,val = %2d\n", x, ch[x][0], ch[x][1], size[x], key[x]);
    treaval(ch[x][1]);
  }
}
void debug() {
  printf("root:%d\n", root);
  treaval(root);
  putchar('\n');
}
//基于旋转的Treap 允许重复值
struct Treap {
  int tot, root;
  int ch[N][2], key[N], pt[N], cnt[N], size[N];
  void init() { tot = root = 0; pt[0] = INF; }
  void push_up(int x) { size[x] = size[ch[x][0]] + size[ch[x][1]] + cnt[x]; }
  void new_node(int &x, int v) {
    x = ++tot;
    ch[x][0] = ch[x][1] = 0;
    size[x] = cnt[x] = 1;
    pt[x] = rand();
    key[x] = v;
  }
  void rotate(int &x, int f) {
    int y = ch[x][f];
    ch[x][f] = ch[y][f ^ 1];
    ch[y][f ^ 1] = x;
    push_up(x);
    push_up(y);
    x = y;
  }
  void insert(int &x, int v) {
    if (!x) { new_node(x, v); return; }
    if (key[x] == v) {
      ++cnt[x];
    } else {
      int f = key[x] < v;
      insert(ch[x][f], v);
      if (pt[ch[x][f]] < pt[x]) {
        rotate(x, f);
      }
    }
    push_up(x);
  }
  void erase(int &x, int v) {
    if (!x) { return; }
    if (key[x] == v) {
      if (cnt[x] > 1) {
        --cnt[x];
      } else {
        if (!ch[x][0] && !ch[x][1]) {
          x = 0;
        } else {
          rotate(x, pt[ch[x][0]] > pt[ch[x][1]]);
          erase(x, v);
        }
      }
    } else {
      erase(ch[x][key[x] < v], v);
    }
    push_up(x);
  }
  void insert(int v) { insert(root, v); }
  void erase(int v) { erase(root, v); }
} treap;
//Size Balanced Tree 不允许重复值
struct SBT {
  int root, tot;
  int ch[N][2], key[N], size[N];
  void init() { tot = root = 0; size[0] = 0; }
  void rotate(int &x, int f) {
    int y = ch[x][f];
    ch[x][f] = ch[y][f ^ 1];
    ch[y][f ^ 1] = x;
    size[y] = size[x];
    size[x] = size[ch[x][0]] + size[ch[x][1]] + 1;
    x = y;
  }
  void maintain(int &x, int f) {
    if (size[ch[ch[x][f]][f]] > size[ch[x][f ^ 1]]) {
      rotate(x, f);
    } else if (size[ch[ch[x][f]][f ^ 1]] > size[ch[x][f ^ 1]]) {
      rotate(ch[x][f], f ^ 1); rotate(x, f);
    } else {
      return;
    }
    maintain(ch[x][0], 0);
    maintain(ch[x][1], 1);
    maintain(x, 0);
    maintain(x, 1);
  }
  void insert(int &x, int v) {
    if (!x) {
      x = ++tot;
      ch[x][0] = ch[x][1] = 0;
      size[x] = 1;
      key[x] = v;
    } else {
      ++size[x];
      insert(ch[x][key[x] < v], v);
      maintain(x, key[x] < v);
    }
  }
  int erase(int &x, int v) {
    if (!x) { return 0; }
    --size[x];
    if (key[x] == v || (key[x] > v && !ch[x][0]) || (key[x] < v && !ch[x][1])) {
      int ret = key[x];
      if (ch[x][0] && ch[x][1]) {
        key[x] = erase(ch[x][0], v + 1);
      } else {
        x = ch[x][0] + ch[x][1];
      }
      return ret;
    }
    return erase(ch[x][key[x] < v], v);
  }
  void insert(int v) { insert(root, v); }
  void erase(int v) { erase(root, v); }
} sbt;
//Splay ver.1
int k1, k2, num[N];
struct Splay {
  int root, tot, point;
  int ch[N][2], pre[N], size[N];
  int key[N], add[N], rev[N];
  bool isroot(int x) { return !pre[x] || ch[pre[x]][0] != x && ch[pre[x]][1] != x; }
  void rotate(int x) {
    int y = pre[x], f = ch[y][1] == x;
    ch[y][f] = ch[x][f ^ 1];
    pre[ch[y][f]] = y;
    if (!isroot(y)) { ch[pre[y]][ch[pre[y]][1] == y] = x; }
    pre[x] = pre[y];
    ch[x][f ^ 1] = y;
    pre[y] = x;
    push_up(y);
  }
  void splay(int x) {
    push_down(x);
    while (!isroot(x)) {
      int y = pre[x], z = pre[y];
      if (isroot(y)) {
        push_down(y);
        push_down(x);
        rotate(x);
      } else {
        push_down(z);
        push_down(y);
        push_down(x);
        rotate((ch[z][1] == y) == (ch[y][1] == x) ? y : x);
        rotate(x);
      }
    }
    push_up(x);
  }
  void new_node(int &x, int v, int fa) {
    x = ++tot;
    ch[x][0] = ch[x][1] = 0;
    pre[x] = fa;
    size[x] = 1;
    key[x] = v;
    add[x] = rev[x] = 0;
  }
  void update_add(int x, int v) {
    if (x) { key[x] += v; add[x] += v; }
  }
  void update_rev(int x) {
    if (x) { rev[x] ^= 1; swap(ch[x][0], ch[x][1]); }
  }
  void push_down(int x) {
    if (add[x]) {
      update_add(ch[x][0], add[x]);
      update_add(ch[x][1], add[x]);
      add[x] = 0;
    }
    if (rev[x]) {
      update_rev(ch[x][0]);
      update_rev(ch[x][1]);
      rev[x] = 0;
    }
  }
  void push_up(int x) { size[x] = size[ch[x][0]] + size[ch[x][1]] + 1; }
  void build(int &x, int l, int r, int fa) {
    int m = l + r >> 1;
    new_node(x, num[m], fa);
    if (l < m) { build(ch[x][0], l, m - 1, x); }
    if (r > m) { build(ch[x][1], m + 1, r, x); }
    push_up(x);
  }
  void init(int n) {
    root = tot = size[0] = 0;
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &num[i]);
    }
    build(root, 1, n, 0);
    point = 1;
  }
  int find(int rt, int k) {
    int x = rt;
    while (size[ch[x][0]] + 1 != k) {
      push_down(x);
      if (k <= size[ch[x][0]]) {
        x = ch[x][0];
      } else {
        k -= size[ch[x][0]] + 1;
        x = ch[x][1];
      }
    }
    return x;
  }
  void split(int &x, int &y, int sz) {
    if (!sz) { y = x; x = 0; return; }
    y = find(x, sz + 1);
    splay(y);
    x = ch[y][0];
    ch[y][0] = 0;
    push_up(y);
  }
  void split3(int &x, int &y, int &z, int l, int r) {
    split(x, z, r); split(x, y, l - 1);
  }
  void join(int &x, int &y) {
    if (!x || !y) { x |= y; return; }
    x = find(x, size[x]);
    splay(x);
    ch[x][1] = y;
    pre[y] = x;
    push_up(x);
  }
  void join3(int &x, int y, int z) {
    join(y, z); join(x, y);
  }
  void evert() {
    if (point > 1) {
      int x;
      split(root, x, point - 1);
      swap(root, x);
      join(root, x);
      point = 1;
    }
  }
  void plus(int v) {
    evert();
    int x, y;
    split3(root, x, y, point, point + k2 - 1);
    update_add(x, v);
    join3(root, x, y);
  }
  void reverse() {
    evert();
    int x, y;
    split3(root, x, y, point, point + k1 - 1);
    update_rev(x);
    join3(root, x, y);
  }
  void insert(int v) {
    evert();
    int x, y;
    split(root, x, point);
    new_node(y, v, 0);
    join3(root, y, x);
  }
  void erase() {
    evert();
    int x, y;
    split3(root, x, y, point, point);
    join(root, y);
  }
  void move(int tag) {
    switch (tag) {
      case 1:
        if (--point == 0) { point = size[root]; }
        break;
      case 2:
        if (++point == size[root] + 1) { point = 1; }
        break;
    }
  }
  void query() {
    evert();
    int x, y;
    split3(root, x, y, point, point);
    printf("%d\n", key[x]);
    join3(root, x, y);
  }
} splay;
//HDU 4453
int main() {
  int n, m, v, cas = 0;
  char op[10];
  while (~scanf("%d%d%d%d", &n, &m, &k1, &k2) && (n || m || k1 || k2)) {
    splay.init(n);
    printf("Case #%d:\n", ++cas);
    while (m--) {
      scanf("%s", op);
      switch (op[0]) {
        case 'a':
          scanf("%d", &v);
          splay.plus(v);
          break;
        case 'r':
          splay.reverse();
          break;
        case 'i':
          scanf("%d", &v);
          splay.insert(v);
          break;
        case 'd':
          splay.erase();
          break;
        case 'm':
          scanf("%d", &v);
          splay.move(v);
          break;
        case 'q':
          splay.query();
          break;
      }
    }
  }
}
//Splay ver.2
const int N = 500005;
const int INF = 0x3f3f3f3f;
int n, q;
struct Splay {
  int pre[N], ch[N][2], key[N], size[N];
  int root, tot1;
  int sum[N], rev[N], same[N];
  int lx[N], rx[N], mx[N];
  int s[N], tot2; //内存池和容量
  int a[N];
  void NewNode(int &r, int father, int k) {
    if (tot2) { r = s[tot2--]; } //取的时候是tot2--,存的时候就是++tot2
    else { r = ++tot1; }
    pre[r] = father;
    ch[r][0] = ch[r][1] = 0;
    key[r] = k;
    sum[r] = k;
    rev[r] = same[r] = 0;
    lx[r] = rx[r] = mx[r] = k;
    size[r] = 1;
  }
  void Update_Rev(int r) {
    if (!r) { return; }
    swap(ch[r][0], ch[r][1]);
    swap(lx[r], rx[r]);
    rev[r] ^= 1;
  }
  void Update_Same(int r, int v) {
    if (!r) { return; }
    key[r] = v;
    sum[r] = v * size[r];
    lx[r] = rx[r] = mx[r] = max(v, v * size[r]);
    same[r] = 1;
  }
  void push_up(int r) {
    int lson = ch[r][0], rson = ch[r][1];
    size[r] = size[lson] + size[rson] + 1;
    sum[r] = sum[lson] + sum[rson] + key[r];
    lx[r] = max(lx[lson], sum[lson] + key[r] + max(0, lx[rson]));
    rx[r] = max(rx[rson], sum[rson] + key[r] + max(0, rx[lson]));
    mx[r] = max(0, rx[lson]) + key[r] + max(0, lx[rson]);
    mx[r] = max(mx[r], max(mx[lson], mx[rson]));
  }
  void push_down(int r) {
    if (same[r]) {
      Update_Same(ch[r][0], key[r]);
      Update_Same(ch[r][1], key[r]);
      same[r] = 0;
    }
    if (rev[r]) {
      Update_Rev(ch[r][0]);
      Update_Rev(ch[r][1]);
      rev[r] = 0;
    }
  }
  void Build(int &x, int l, int r, int father) {
    if (l > r) { return; }
    int mid = (l + r) / 2;
    NewNode(x, father, a[mid]);
    Build(ch[x][0], l, mid - 1, x);
    Build(ch[x][1], mid + 1, r, x);
    push_up(x);
  }
  void Init() {
    root = tot1 = tot2 = 0;
    ch[root][0] = ch[root][1] = size[root] = pre[root] = 0;
    same[root] = rev[root] = sum[root] = key[root] = 0;
    lx[root] = rx[root] = mx[root] = -INF;
    NewNode(root, 0, -1);
    NewNode(ch[root][1], root, -1);
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }
    Build(ch[ch[root][1]][0], 0, n - 1, ch[root][1]);
    push_up(ch[root][1]);
    push_up(root);
  }
  //旋转,0为左旋，1为右旋
  void Rotate(int x, int kind) {
    int y = pre[x];
    push_down(y);
    push_down(x);
    ch[y][!kind] = ch[x][kind];
    pre[ch[x][kind]] = y;
    if (pre[y]) { ch[pre[y]][ch[pre[y]][1] == y] = x; }
    pre[x] = pre[y];
    ch[x][kind] = y;
    pre[y] = x;
    push_up(y);
  }
  //Splay调整，将r结点调整到goal下面
  void Splay(int r, int goal) {
    push_down(r);
    while (pre[r] != goal) {
      if (pre[pre[r]] == goal) {
        push_down(pre[r]);
        push_down(r);
        Rotate(r, ch[pre[r]][0] == r);
      } else {
        push_down(pre[pre[r]]);
        push_down(pre[r]);
        push_down(r);
        int y = pre[r];
        int kind = ch[pre[y]][0] == y;
        if (ch[y][kind] == r) {
          Rotate(r, !kind);
          Rotate(r, kind);
        } else {
          Rotate(y, kind);
          Rotate(r, kind);
        }
      }
    }
    push_up(r);
    if (goal == 0) { root = r; }
  }
  int Get_kth(int r, int k) {
    push_down(r);
    int t = size[ch[r][0]] + 1;
    if (t == k) { return r; }
    if (t > k) { return Get_kth(ch[r][0], k); }
    else { return Get_kth(ch[r][1], k - t); }
  }
  //在第pos个数后面插入tot个数
  void Insert(int pos, int tot) {
    for (int i = 0; i < tot; i++) { scanf("%d", &a[i]); }
    Splay(Get_kth(root, pos + 1), 0);
    Splay(Get_kth(root, pos + 2), root);
    Build(ch[ch[root][1]][0], 0, tot - 1, ch[root][1]);
    push_up(ch[root][1]);
    push_up(root);
  }
  //删除子树
  void erase(int r) {
    if (!r) { return; }
    s[++tot2] = r;
    erase(ch[r][0]);
    erase(ch[r][1]);
  }
  //从第pos个数开始连续删除tot个数
  void Delete(int pos, int tot) {
    Splay(Get_kth(root, pos), 0);
    Splay(Get_kth(root, pos + tot + 1), root);
    erase(ch[ch[root][1]][0]);
    pre[ch[ch[root][1]][0]] = 0;
    ch[ch[root][1]][0] = 0;
    push_up(ch[root][1]);
    push_up(root);
  }
  //将从第pos个数开始的连续的tot个数修改为c
  void Make_Same(int pos, int tot, int c) {
    Splay(Get_kth(root, pos), 0);
    Splay(Get_kth(root, pos + tot + 1), root);
    Update_Same(ch[ch[root][1]][0], c);
    push_up(ch[root][1]);
    push_up(root);
  }
  //将第pos个数开始的连续tot个数进行反转
  void Reverse(int pos, int tot) {
    Splay(Get_kth(root, pos), 0);
    Splay(Get_kth(root, pos + tot + 1), root);
    Update_Rev(ch[ch[root][1]][0]);
    push_up(ch[root][1]);
    push_up(root);
  }
  //得到第pos个数开始的tot个数的和
  int Get_Sum(int pos, int tot) {
    Splay(Get_kth(root, pos), 0);
    Splay(Get_kth(root, pos + tot + 1), root);
    return sum[ch[ch[root][1]][0]];
  }
  //得到第pos个数开始的tot个数中最大的子段和
  int Get_MaxSum(int pos, int tot) {
    Splay(Get_kth(root, pos), 0);
    Splay(Get_kth(root, pos + tot + 1), root);
    return mx[ch[ch[root][1]][0]];
  }
  void InOrder(int r) {
    if (!r) { return; }
    push_down(r);
    InOrder(ch[r][0]);
    printf("%d ", key[r]);
    InOrder(ch[r][1]);
  }
} splay;
int main() {
  while (scanf("%d%d", &n, &q) == 2) {
    splay.Init();
    char op[20];
    int x, y, z;
    while (q--) {
      scanf("%s", op);
      if (strcmp(op, "INSERT") == 0) {
        scanf("%d%d", &x, &y);
        splay.Insert(x, y);
      } else if (strcmp(op, "DELETE") == 0) {
        scanf("%d%d", &x, &y);
        splay.Delete(x, y);
      } else if (strcmp(op, "MAKE-SAME") == 0) {
        scanf("%d%d%d", &x, &y, &z);
        splay.Make_Same(x, y, z);
      } else if (strcmp(op, "REVERSE") == 0) {
        scanf("%d%d", &x, &y);
        splay.Reverse(x, y);
      } else if (strcmp(op, "GET-SUM") == 0) {
        scanf("%d%d", &x, &y);
        printf("%d\n", splay.Get_Sum(x, y));
      } else if (strcmp(op, "MAX-SUM") == 0) {
        printf("%d\n", splay.Get_MaxSum(1, splay.size[root] - 2));
      }
    }
  }
}
//主席树


//Link-Cut Tree 动态树
struct LCT {
  int ch[N][2], pre[N], key[N], rev[N];
  int add[N], vmax[N];
  bool isroot(int x) { return !pre[x] || ch[pre[x]][0] != x && ch[pre[x]][1] != x; }
  void rotate(int x) {
    int y = pre[x], f = ch[y][1] == x;
    ch[y][f] = ch[x][f ^ 1];
    pre[ch[y][f]] = y;
    if (!isroot(y)) { ch[pre[y]][ch[pre[y]][1] == y] = x; }
    pre[x] = pre[y];
    ch[x][f ^ 1] = y;
    pre[y] = x;
    push_up(y);
  }
  void splay(int x) {
    push_down(x);
    while (!isroot(x)) {
      int y = pre[x], z = pre[y];
      if (isroot(y)) {
        push_down(y);
        push_down(x);
        rotate(x);
      } else {
        push_down(z);
        push_down(y);
        push_down(x);
        rotate((ch[z][1] == y) == (ch[y][1] == x) ? y : x);
        rotate(x);
      }
    }
    push_up(x);
  }
  int access(int x) {
    int y = 0;
    for (; x; x = pre[x]) {
      splay(x);
      ch[x][1] = y;
      push_up(x);
      y = x;
    }
    return y;
  }
  void evert(int x) {
    rev[access(x)] ^= 1;
    splay(x);
  }
  void push_up(int x) { vmax[x] = max(max(vmax[ch[x][0]], vmax[ch[x][1]]), key[x]); }
  void push_down(int x) {
    if (add[x]) {
      key[x] += add[x];
      if (ch[x][0]) {
        add[ch[x][0]] += add[x];
        vmax[ch[x][0]] += add[x];
      }
      if (ch[x][1]) {
        add[ch[x][1]] += add[x];
        vmax[ch[x][1]] += add[x];
      }
      add[x] = 0;
    }
    if (rev[x]) {
      if (ch[x][0]) { rev[ch[x][0]] ^= 1; }
      if (ch[x][1]) { rev[ch[x][1]] ^= 1; }
      swap(ch[x][0], ch[x][1]);
      rev[x] = 0;
    }
  }
  int find_root(int x) {
    while (pre[x]) { x = pre[x]; }
    return x;
  }
  //如果u,v不在同一颗子树中,则通过在u,v之间连边的方式,连接这两颗子树
  void link(int u, int v) {
    if (find_root(u) == find_root(v)) { puts("-1"); return; }
    evert(u);
    pre[u] = v;
  }
  //如果u,v在同一颗子树中,且u!=v,则将u视为这颗子树的根以后,切断v与其父亲结点的连接
  void cut(int u, int v) {
    if (u == v || find_root(u) != find_root(v)) { puts("-1"); return; }
    evert(u);
    access(v);
    splay(v);
    pre[ch[v][0]] = 0;
    ch[v][0] = 0;
    push_up(v);
  }
  //如果u,v在同一颗子树中,则将u,v之间路径上所有点的点权增加w
  void update(int u, int v, int w) {
    if (find_root(u) != find_root(v)) { puts("-1"); return; }
    evert(u);
    access(v);
    splay(v);
    add[v] += w;
    vmax[v] += w;
    push_down(v);
  }
  //如果u,v在同一颗子树中，返回u,v之间路径上点权的最大值
  void query(int u, int v) {
    if (find_root(u) != find_root(v)) { puts("-1"); return; }
    evert(u);
    access(v);
    splay(v);
    printf("%d\n", vmax[v]);
  }
  struct graph {
    int head[N], to[N << 1], next[N << 1];
    int tot;
    void init() { tot = 0; memset(head, 0xff, sizeof(head)); }
    void add(int u, int v) {
      to[tot] = v;
      next[tot] = head[u];
      head[u] = tot++;
    }
  } g;
  void dfs(int u, int fa) {
    for (int i = g.head[u]; ~i; i = g.next[i]) {
      int v = g.to[i];
      if (v != fa) {
        dfs(v, u);
        pre[v] = u;
      }
    }
  }
  void init(int n) {
    int m, x, y;
    g.init();
    for (int i = 1; i < n; ++i) {
      scanf("%d%d", &x, &y);
      g.add(x, y); g.add(y, x);
    }
    memset(ch, 0, sizeof(ch));
    memset(pre, 0, sizeof(pre));
    memset(rev, 0, sizeof(rev));
    memset(add, 0, sizeof(add));
    vmax[0] = 0;
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &key[i]);
      vmax[i] = key[i];
    }
    dfs(1, 0);
  }
} lct;
//HDU 4010
int main() {
  int n, q, op, x, y, w;
  while (~scanf("%d", &n)) {
    lct.init(n);
    scanf("%d", &q);
    while (q--) {
      scanf("%d", &op);
      switch (op) {
        case 1:
          scanf("%d%d", &x, &y);
          lct.link(x, y);
          break;
        case 2:
          scanf("%d%d", &x, &y);
          lct.cut(x, y);
          break;
        case 3:
          scanf("%d%d%d", &w, &x, &y);
          lct.update(x, y, w);
          break;
        case 4:
          scanf("%d%d", &x, &y);
          lct.query(x, y);
          break;
      }
    }
    putchar('\n');
  }
}
//不基于旋转的Treap
int num[N];
struct Treap {
  int tot, root;
  int ch[N][2], pt[N], size[N];
  int key[N], vmin[N], add[N], rev[N];
  void init() { tot = 0; }
  void new_node(int &x, int v) {
    x = ++tot;
    ch[x][0] = ch[x][1] = 0;
    size[x] = 1;
    pt[x] = rand();
    key[x] = vmin[x] = v;
    add[x] = rev[x] = 0;
  }
  void merge(int &p, int x, int y) {
    if (!x || !y) { p = x | y; return; }
    if (pt[x] < pt[y]) {
      push_down(x);
      merge(ch[x][1], ch[x][1], y);
      p = x;
    } else {
      push_down(y);
      merge(ch[y][0], x, ch[y][0]);
      p = y;
    }
    push_up(p);
  }
  void split(int p, int sz, int &x, int &y) {
    if (!sz) { x = 0; y = p; return; }
    push_down(p);
    if (size[ch[p][0]] >= sz) {
      y = p;
      split(ch[p][0], sz, x, ch[y][0]);
    } else {
      x = p;
      split(ch[p][1], sz - size[ch[p][0]] - 1, ch[x][1], y);
    }
    push_up(p);
  }
  void update_add(int x, int v) {
    if (x) { key[x] += v; add[x] += v; vmin[x] += v; }
  }
  void update_rev(int x) {
    if (x) { swap(ch[x][0], ch[x][1]); rev[x] ^= 1; }
  }
  void push_down(int x) {
    if (add[x]) {
      update_add(ch[x][0], add[x]);
      update_add(ch[x][1], add[x]);
      add[x] = 0;
    }
    if (rev[x]) {
      update_rev(ch[x][0]);
      update_rev(ch[x][1]);
      rev[x] = 0;
    }
  }
  void push_up(int x) {
    size[x] = 1;
    vmin[x] = key[x];
    if (ch[x][0]) {
      size[x] += size[ch[x][0]];
      vmin[x] = min(vmin[x], vmin[ch[x][0]]);
    }
    if (ch[x][1]) {
      size[x] += size[ch[x][1]];
      vmin[x] = min(vmin[x], vmin[ch[x][1]]);
    }
  }
  int build(int &x, int l, int r) {
    int m = l + r >> 1;
    new_node(x, num[m]);
    if (l < m) { build(ch[x][0], l, m - 1); }
    if (r > m) { build(ch[x][1], m + 1, r); }
    push_up(x);
  }
  void plus(int l, int r, int v) {
    int x, y;
    split(root, l - 1, root, x);
    split(x, r - l + 1, x, y);
    update_add(x, v);
    merge(x, x, y);
    merge(root, root, x);
  }
  void reverse(int l, int r) {
    int x, y;
    split(root, l - 1, root, x);
    split(x, r - l + 1, x, y);
    update_rev(x);
    merge(x, x, y);
    merge(root, root, x);
  }
  void revolve(int l, int r, int k) {
    int x, y, p, q;
    k %= r - l + 1;
    if (!k) { return; }
    split(root, l - 1, root, x);
    split(x, r - l + 1, x, y);
    split(x, r - l + 1 - k, p, q);
    merge(x, q, p);
    merge(x, x, y);
    merge(root, root, x);
  }
  void insert(int k, int v) {
    int x, y;
    new_node(x, v);
    split(root, k, root, y);
    merge(root, root, x);
    merge(root, root, y);
  }
  void erase(int k) {
    int x, y;
    split(root, k - 1, root, x);
    split(x, 1, x, y);
    merge(root, root, y);
  }
  int query(int l, int r) {
    int x, y, ret;
    split(root, l - 1, root, x);
    split(x, r - l + 1, x, y);
    ret = vmin[x];
    merge(x, x, y);
    merge(root, root, x);
    return ret;
  }
} treap;
//POJ 3580
int main() {
  int n, m, x, y, v;
  char op[10];
  while (~scanf("%d", &n)) {
    treap.init();
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &num[i]);
    }
    treap.build(treap.root, 1, n);
    scanf("%d", &m);
    while (m--) {
      scanf("%s", op);
      switch (op[0]) {
        case 'A':
          scanf("%d%d%d", &x, &y, &v);
          treap.plus(x, y, v);
          break;
        case 'R':
          scanf("%d%d", &x, &y);
          if (op[3] == 'E') {
            treap.reverse(x, y);
          } else {
            scanf("%d", &v);
            treap.revolve(x, y, v);
          }
          break;
        case 'I':
          scanf("%d%d", &x, &v);
          treap.insert(x, v);
          break;
        case 'D':
          scanf("%d", &x);
          treap.erase(x);
          break;
        case 'M':
          scanf("%d%d", &x, &y);
          printf("%d\n", treap.query(x, y));
          break;
      }
    }
  }
}
//可持久化Treap
const int N = 50005;
const int M = 5000005;
int root[N], vs, d;
struct Treap {
  int tot;
  int ch[M][2], size[M];
  char key[M];
  bool hey(int x, int y) { return (long long)rand() * (size[x] + size[y]) < (long long)size[x] * RAND_MAX; }
  void init() { tot = 0; }
  void new_node(int &x, char v) {
    x = ++tot;
    ch[x][0] = ch[x][1] = 0;
    size[x] = 1;
    key[x] = v;
  }
  void copy_node(int &x, int y) {
    if (!y) { x = 0; return; }
    x = ++tot;
    ch[x][0] = ch[y][0];
    ch[x][1] = ch[y][1];
    size[x] = size[y];
    key[x] = key[y];
  }
  void merge(int &p, int x, int y) {
    if (!x || !y) {
      p = 0;
      if (x) { copy_node(p, x); }
      if (y) { copy_node(p, y); }
      return;
    }
    if (hey(x, y)) {
      copy_node(p, x);
      merge(ch[p][1], ch[x][1], y);
    } else {
      copy_node(p, y);
      merge(ch[p][0], x, ch[y][0]);
    }
    push_up(p);
  }
  void split(int p, int sz, int &x, int &y) {
    if (!sz) { x = 0; copy_node(y, p); return; }
    if (size[ch[p][0]] >= sz) {
      copy_node(y, p);
      split(ch[p][0], sz, x, ch[y][0]);
      push_up(y);
    } else {
      copy_node(x, p);
      split(ch[p][1], sz - size[ch[p][0]] - 1, ch[x][1], y);
      push_up(x);
    }
  }
  void push_up(int x) {
    size[x] = 1;
    if (ch[x][0]) { size[x] += size[ch[x][0]]; }
    if (ch[x][1]) { size[x] += size[ch[x][1]]; }
  }
  void build(char str[], int &x, int l, int r) {
    int m = l + r >> 1;
    new_node(x, str[m]);
    if (l < m) { build(str, ch[x][0], l, m - 1); }
    if (r > m) { build(str, ch[x][1], m + 1, r); }
    push_up(x);
  }
  void insert(int k, char str[]) {
    int x, y, z;
    build(str, x, 0, strlen(str) - 1);
    split(root[vs], k, y, z);
    merge(y, y, x);
    merge(root[++vs], y, z);
  }
  void erase(int k, int sz) {
    int x, y, z;
    split(root[vs], k - 1, x, y);
    split(y, sz, y, z);
    merge(root[++vs], x, z);
  }
  void output(int x) {
    if (ch[x][0]) { output(ch[x][0]); }
    putchar(key[x]);
    d += key[x] == 'c';
    if (ch[x][1]) { output(ch[x][1]); }
  }
  void output(int v, int k, int sz) {
    int x, y, z;
    split(root[v], k - 1, x, y);
    split(y, sz, y, z);
    output(y);
    putchar('\n');
  }
} treap;
//UVa 12538
int main() {
  int n, op, p, c, v;
  char s[105];
  treap.init();
  vs = d = 0;
  scanf("%d", &n);
  while (n--) {
    scanf("%d", &op);
    switch (op) {
      case 1:
        scanf("%d%s", &p, s);
        treap.insert(p - d, s);
        break;
      case 2:
        scanf("%d%d", &p, &c);
        treap.erase(p - d, c - d);
        break;
      case 3:
        scanf("%d%d%d", &v, &p, &c);
        treap.output(v - d, p - d, c - d);
        break;
    }
  }
}
//树链剖分

//KD-Tree

//划分树
int part[20][N]; //表示每层每个位置的值
int sorted[N]; //已经排序好的数
int tol[20][N]; //tol[p][i] 表示第i层从1到i有数分入左边
void build(int l, int r, int dep) {
  if (l == r) { return; }
  int m = l + r >> 1, cnt = m - l + 1; //表示等于中间值而且被分入左边的个数
  for (int i = l; i <= r; ++i) {
    if (part[dep][i] < sorted[m]) { --cnt; }
  }
  int lpos = l, rpos = m + 1;
  for (int i = l; i <= r; ++i) {
    if (part[dep][i] < sorted[m]) {
      part[dep + 1][lpos++] = part[dep][i];
    } else if (part[dep][i] == sorted[m] && cnt > 0) {
      part[dep + 1][lpos++] = part[dep][i];
      --cnt;
    } else {
      part[dep + 1][rpos++] = part[dep][i];
    }
    tol[dep][i] = tol[dep][l - 1] + lpos - l;
  }
  build(l, m, dep + 1);
  build(m + 1, r, dep + 1);
}
//离线查询区间第k大的数, [L, R]是要查询的小区间, [l, r]是大区间
int query(int L, int R, int k, int l, int r, int dep) {
  if (L == R) { return part[dep][L]; }
  int m = l + r >> 1, cnt = tol[dep][R] - tol[dep][L - 1];
  if (cnt >= k) {
    int tl = l + tol[dep][L - 1] - tol[dep][l - 1], tr = tl + cnt - 1;
    return query(tl, tr, k, l, m, dep + 1);
  } else {
    int tr = R + tol[dep][r] - tol[dep][R], tl = tr - (R - L - cnt);
    return query(tl, tr, k - cnt, m + 1, r, dep + 1);
  }
}
//左偏树
int val[N], ls[N], rs[N], dep[N], fa[N];
void init(int n) {
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &val[i]);
    ls[i] = rs[i] = dep[i] = 0;
    fa[i] = i;
  }
}

int find(int x) {
  if (fa[x] != x) {
    fa[x] = find(fa[x]);
  }
  return fa[x];
}

int merge(int x, int y) {
  if (!x || !y) {
    return x | y;
  }
  if (val[x] < val[y]) {
    swap(x, y);
  }
  rs[x] = merge(rs[x], y);
  fa[rs[x]] = x;
  if (dep[ls[x]] < dep[rs[x]]) {
    swap(ls[x], rs[x]);
  }
  dep[x] = dep[rs[x]] + 1;
  return x;
}

int push(int x, int y) {
  return merge(x, y);
}

int pop(int x) {
  int a = ls[x], b = rs[x];
  ls[x] = rs[x] = dep[x] = 0;
  fa[x] = x;
  fa[a] = a;
  fa[b] = b;
  return merge(a, b);
}
//POJ 2201
int main() {
  int n, m, x, y;
  while (~scanf("%d", &n)) {
    init(n);
    scanf("%d", &m);
    while (m--) {
      scanf("%d%d", &x, &y);
      int a = find(x), b = find(y);
      if (a == b) {
        puts("-1");
      } else {
        val[a] >>= 1;
        val[b] >>= 1;
        a = push(pop(a), a);
        b = push(pop(b), b);
        printf("%d\n", val[merge(a, b)]);
      }
    }
  }
}
//哈夫曼树
template<typename T> struct Huffman {
  int lChild[N << 1], rChild[N << 1], parent[N << 1], weight[N << 1], n, tot;
  char key[N];
  void init() { n = tot = 0; }
  void build(char s[], T w[]) {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > que;
    pair<int, int> x, y;
    n = strlen(s); tot = (n << 1) - 1;
    for (int i = 0; i < n; i++) {
      weight[i] = w[i]; key[i] = s[i]; lChild[i] = rChild[i] = parent[i] = 0;
      que.push(make_pair(weight[i], i));
    }
    for (int i = n; i < m; i++) {
      x = que.top(); que.pop(); y = que.top(); que.pop();
      lChild[i] = x.second; rChild[i] = y.second; weight[i] = x.first + y.first;
      parent[x.second] = parent[y.second] = i; parent[i] = 0;
    }
  }
  void getCode(vector<string> &code) {
    code.clear(); code.resize(n);
    for (int i = 0, pos; i < n; i++) {
      pos = i;
      while (pos != tot - 1) {
        if (pos == lChild[parent[pos]]) { code[i] = '0' + code[i]; }
        else { code[i] = '1' + code[i]; }
      }
    }
  }
  char *encode(char s[], const vector<string> &code) {
    string ret;
    for (int i = 0, j; s[i]; i++) {
      for (j = 0; j < n && s[i] != key[j]; j++);
      ret += code[j];
    }
    return ret.c_str();
  }
  char *decode(char s[], const vector<string> &code) {
    string ret;
    for (int i = 0, pos = tot - 1; s[i]; i++) {
      if (pos >= n) {
        if (s[i] == '0') { pos = lChild[pos]; }
        else { pos = rChild[pos]; }
      } else {
        ret += key[pos];
        pos = tot - 1;
      }
    }
    return ret.c_str();
  }
}
//笛卡尔树

