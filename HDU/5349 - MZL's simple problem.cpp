#include <iostream>
#include <cstdio>
#include <set>
using namespace std;

inline void getInt(int &x) {
	char c = 0; int sign = 1;
	while ((c < '0' || c > '9') && c != '-') { c = getchar(); };
	if (c == '-') { sign = -1; c = getchar(); }
	x = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
	x *= sign;
}

multiset<int> st;

int main() {
	int T, x;
	getInt(T);
	while (T--) {
		getInt(x);
		switch (x) {
			case 1: getInt(x); st.insert(x); break;
			case 2: if (!st.empty()) { st.erase(st.begin()); } break;
			case 3: printf("%d\n", st.empty() ? 0 : * (--st.end())); break;
		}
	}
}
