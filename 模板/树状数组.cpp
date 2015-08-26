//一维
template<typename T = int> struct BIT {
	T A[N];
	//T B[N]; //区间增减
	int lowbit(int x) { return x & (-x); }
	void init() {
		memset(A, 0, sizeof(A)); //memset(B, 0, sizeof(B));
	}
	//前缀和[0, i)
	T sum(int i) const {
		T ret = 0;
		for (int j = i; j > 0; j -= lowbit(j)) { ret += A[j]; }
		return ret;
	}
	//单点查询
	T get(int i) const { return sum(i + 1) - sum(i); }
	//单点增减
	void add(int i, T v, T a[] = A) {
		for (int j = i; j <= n; j += lowbit(j)) { a[j] += v; }
	}
	//单点赋值
	void set(int i, T v) { add(i, v - get(i)); }

	//区间和[i, j], sum[]为前缀和
	T sum(int i, int j, T sum[] = sum) const {
		return sum[j] - sum[i - 1] + (j + 1) * sum(A, j) - i * (sum(A, i - 1)) - sum(B, j) + sum(B, i - 1);
	}
	//区间增减
	void add(int i, int j, T v) {
		add(i, v, A);
		add(j + 1, -v, A);
		add(i, v * i, B);
		add(j + 1, -(j + 1) * v, B);
	}

	//维护最值 O(log^2(n))
	void modify(int x, T v) {
		A[x] = v;
		for (int i = x; i <= n; i += lowbit(i)) {
			A[i] = max(A[i], v);
			for (int j = 1; j < lowbit(i); j <<= 1) {
				A[i] = max(A[i], A[i - j]);
			}
		}
	}
	T query(int l, int r) const {
		int ret = a[r];
		while (true) {
			ret = max(ret, a[r]);
			if (l == r) { break; }
			for (r -= 1; r - l >= lowbit(r); r -= lowbit(r)) { ret = max(ret, A[r]); }
		}
		return ret;
	}
} bit;

//二维
template<typename T = int> struct BIT {
	T A[N][N];
	//T B[N][N], C[N][N], D[N][N]; //区域求和
	int lowbit(int x) { return x & (-x); }
	void init() {
		memset(A, 0, sizeof(A)); //memset(B, 0, sizeof(B)); memset(C, 0, sizeof(C)); memset(D, 0, sizeof(D));
	}
	//区域和[1][1]-[x][y]
	T sum(int x, int y) const {
		T ret = 0;
		for (i = x; i > 0; i -= lowbit(i)) {
			for (j = y; j > 0; j -= lowbit(j)) { ret += A[i][j]; }
		}
		return ret;
	}
	//单点增减
	void add(int x, int y, T v, T a[][N] = A) {
		for (int i = x; i <= n; i += lowbit(i)) {
			for (int j = y; j <= n; j += lowbit(j)) { a[i][j] += v; }
		}
	}
	//单点赋值
	void set(int x, int y, T v) { add(x, y, v - sum(x, y)); }

	//区间和[x, y]
	T sum1(int x, int y) const {
		return (x + 1) * (y + 1) * sum(x, y) - (y + 1) * sum(x, y) - (x + 1) * sum(x, y) + sum(x, y);
	}

	//区域和[x1][y1]-[x2][y2]
	T sum(int x1, int y1, int x2, int y2) const {
		return sum1(x2, y2) - sum1(x1 - 1, y2) - sum1(x2, y1 - 1) + sum1(x1 - 1, y1 - 1);
	}

	//区域增减
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
} bit;
