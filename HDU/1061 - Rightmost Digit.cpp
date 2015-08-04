#include <iostream>
#include <cstdio>
using namespace std;

int a[10][4] = {{0, 0, 0, 0},
	{1, 1, 1, 1},
	{2, 4, 8, 6},
	{3, 9, 7, 1},
	{4, 6, 4, 6},
	{5, 5, 5, 5},
	{6, 6, 6, 6},
	{7, 9, 3, 1},
	{8, 4, 2, 6},
	{9, 1, 9, 1}
};

int main() {
	int T, n;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		printf("%d\n", a[n % 10][n % 4 - 1 >= 0 ? n % 4 - 1 : 3]);
	}
}
