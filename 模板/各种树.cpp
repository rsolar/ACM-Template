//基本版本
template<typename T = int> struct SegmentTree {
	T sum[N << 2], add[N << 2];
	inline void push_up(int rt) { sum[rt] = sum[rt << 1] + sum[rt << 1 | 1]; }
	inline void push_down(int rt, int len) {
		if (add[rt]) {
			add[rt << 1] += add[rt];
			add[rt << 1 | 1] += add[rt];
			sum[rt << 1] += add[rt] * (len - (len >> 1));
			sum[rt << 1 | 1] += add[rt] * (len >> 1);
			add[rt] = 0;
		}
	}
	void build(int l, int r, int rt) {
		add[rt] = 0;
		if (l == r) { scanf("%d", &sum[rt]); return; }
		int m = l + r >> 1;
		build(l, m, rt << 1);
		build(m + 1, r, rt << 1 | 1);
		push_up(rt);
	}
	void update(int p, T val, int l, int r, int rt) {
		if (l == r) { sum[rt] += val; return; }
		push_down(rt, r - l + 1);
		int m = l + r >> 1;
		if (p <= m) { update(p, val, l, m, rt << 1); }
		else { update(p, val, m + 1, r, rt << 1 | 1); }
		push_up(rt);
	}
	void update(int L, int R, T val, int l, int r, int rt) {
		if (L <= l && r <= R) {
			add[rt] += val;
			sum[rt] += val * (r - l + 1);
			return;
		}
		push_down(rt, r - l + 1);
		int m = l + r >> 1;
		if (L <= m) { update(L, R, val, l, m, rt << 1); }
		if (m < R) { update(L, R, val, m + 1, r, rt << 1 | 1); }
		push_up(rt);
	}
	T query(int L, int R, int l, int r, int rt) {
		if (L <= l && r <= R) { return sum[rt]; }
		push_down(rt, r - l + 1);
		int m = l + r >> 1, ret = 0;
		if (L <= m) { ret += query(L, R, l, m, rt << 1); }
		if (m < R) { ret += query(L, R, m + 1, r, rt << 1 | 1); }
		return ret;
	}
} st;

//------------------------------------------------------------------------------

//实时开节点的线段树
#define N 60005
#define M 2500005
#define INF 0x3f3f3f3f

int n, a[N];

struct SegmentTree {
	int ls[M], rs[M], cnt[M], root[N],use[N], tot;
	void init() { tot = 0; memset(root, 0, sizeof(root)); }
	int new_node() {
		++tot; ls[tot] = rs[tot] = cnt[tot] = 0;
		return tot;
	}
	void update(int p, int val, int l, int r, int &rt) {
		if (!rt) { rt = new_node(); }
		if (l == r) { cnt[rt] += val; return; }
		int m = l + r >> 1;
		if (p <= m) { update(p, val, l, m, ls[rt]); }
		else { update(p, val, m + 1, r, rs[rt]); }
		cnt[rt] = cnt[ls[rt]] + cnt[rs[rt]];
	}
	int lowbit(int x) { return x & -x; }
	void modify(int x, int p, int val) {
		for (int i = x; i <= n; i += lowbit(i)) { update(p, val, 0, INF, root[i]); }
	}
	int sum(int x) {
		int ret = 0;
		for (int i = x; i > 0; i -= lowbit(i)) { ret += cnt[ls[use[i]]]; }
		return ret;
	}
	int query(int ss, int tt, int l, int r, int k) {
		for (int i = ss; i > 0; i -= lowbit(i)) { use[i] = root[i]; }
		for (int i = tt; i > 0; i -= lowbit(i)) { use[i] = root[i]; }
		while (l < r) {
			int m = l + r >> 1, tmp = sum(tt) - sum(ss);
			if (k <= tmp) {
				r = m;
				for (int i = ss; i > 0; i -= lowbit(i)) { use[i] = ls[use[i]]; }
				for (int i = tt; i > 0; i -= lowbit(i)) { use[i] = ls[use[i]]; }
			} else {
				l = m + 1;
				k -= tmp;
				for (int i = ss; i > 0; i -= lowbit(i)) { use[i] = rs[use[i]]; }
				for (int i = tt; i > 0; i -= lowbit(i)) { use[i] = rs[use[i]]; }
			}
		}
		return l;
	}
} st;
//区间第k大
int main() {
	int m, l, r, k;
	char op;
	while (~scanf("%d%d", &n, &m)) {
		st.init();
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			st.modify(i, a[i], 1);
		}
		while (m--) {
			scanf(" %c%d%d", &op, &l, &r);
			switch (op) {
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

//------------------------------------------------------------------------------
