//hash_fun.h
inline size_t __stl_hash_string(const char *__s) {
	unsigned long __h = 0;
	for (; *__s; ++__s) { __h = 5 * __h + *__s; }
	return size_t(__h);
}

//BKDR Hash Function
inline size_t BKDRHash(char *str) {
	size_t h = 0, seed = 131; // 31 131 1313 13131 131313 etc..
	while (*str) { h = h * seed + (*str++); }
	return (h & 0x7FFFFFFF);
}

//hash_map
//C++: using namespace stdext;
//G++: using namespace __gnu_cxx;
struct str_hash {
	size_t operator()(const string &str) const {
		return __stl_hash_string(str.c_str());
	}
};

//------------------------------------------------------------------------------

//Manacher 最长回文子串
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

//------------------------------------------------------------------------------

//字符串最小表示
int minString(char s[], int m) {
	int i, j, k;
	char ss[m << 1];
	for (i = 0; i < m; i++) { ss[i] = ss[i + m] = s[i]; }
	for (i = k = 0, j = 1; k < m && i < m && j < m;) {
		for (k = 0; k < m && ss[i + k] == ss[j + k]; k++);
		if (k < m) {
			if (ss[i + k] > ss[j + k]) { i += k + 1; }
			else { j += k + 1; }
			if (i == j) { j++; }
		}
	}
	return min(i, j);
}

//------------------------------------------------------------------------------

//strstr 在串中查找指定字符串的第一次出现
char *strstr(char *str1, const char *str2);

//KMP O(M+N)
//Next[]的含义：x[i-Next[i]...i-1]=x[0...Next[i]-1]
//Next[i]为满足x[i-z...i-1]=x[0...z-1]的最大z值(就是x的自身匹配)
char x[N], y[N];
int Next[N];

void getNext(char x[], int m, int Next[] = Next) {
	int i = 0, j = -1; Next[0] = -1;
	while (i < m) {
		while (j != -1 && x[i] != x[j]) { j = Next[j]; }
		Next[++i] = ++j;
	}
}
//返回x在y中出现的次数，可以重叠
//x是模式串，y是主串
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

void preExtend(char x[], int m, int Next[] = Next) {
	int j = 0, k = 1;
	while (j + 1 < m && x[j] == x[j + 1]) { j++; }
	Next[0] = m; Next[1] = j;
	for (int i = 2; i < m; i++) {
		int p = Next[k] + k - 1, l = Next[i - k];
		if (i + l < p + 1) { Next[i] = l; }
		else {
			j = max(0, p - i + 1);
			while (i + j < m && x[i + j] == x[j]) { j++; }
			Next[i] = j;
			k = i;
		}
	}
}

void getExtend(char x[], int m, char y[], int n, int Next[] = Next, int Extend[] = Extend) {
	preExtend(x, m);
	int j = 0, k = 0;
	while (j < n && j < m && x[j] == y[j]) { j++; }
	Extend[0] = j;
	for (int i = 1; i < n; i++) {
		int p = Extend[k] + k - 1, l = Next[i - k];
		if (i + l < p + 1) { Extend[i] = l; }
		else {
			j = max(0, p - i + 1);
			while (i + j < n && j < m && y[i + j] == x[j]) { j++; }
			Extend[i] = j;
			k = i;
		}
	}
}

//------------------------------------------------------------------------------

//Trie / AC自动机
char buf[M];

struct Trie {
	int Next[N * 50][26], Fail[N * 50], End[N * 50];
	int root, L;
	inline int newnode() {
		memset(Next[L], -1, sizeof(Next[L]));
		End[L] = 0;
		return L++;
	}
	void init() {
		L = 0;
		root = newnode();
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
				End[temp] = 0;
				temp = Fail[temp];
			}
		}
		return res;
	}
} ac;
