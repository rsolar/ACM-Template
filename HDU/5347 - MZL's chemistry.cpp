#include <iostream>
#include <cstdio>
using namespace std;

#define N 105

int p[N];

int main() {
	int a, b;
	p[1] = 100; p[2] = 200;
	for (int i = 3; i <= 10; i++) { p[i] = i + 80; } p[4] = 5 + 80; p[5] = 4 + 80; p[7] = 8 + 80; p[8] = 7 + 80;
	for (int i = 11; i <= 18; i++) { p[i] = i + 60; } p[12] = 13 + 60; p[13] = 12 + 60; p[15] = 16 + 60; p[16] = 15 + 60;
	p[35] = 46; p[36] = 47; p[53] = 26; p[54] = 27; p[85] = 6; p[86] = 7;
	while (~scanf("%d %d", &a, &b)) {
		puts(p[a] > p[b] ? "FIRST BIGGER" : "SECOND BIGGER");
	}
}
