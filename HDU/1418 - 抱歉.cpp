#include <iostream>
#include <cstdio>
using namespace std;

int main() {
	unsigned m, n;
	while (scanf("%u %u", &n, &m), (n || m)) {
		printf("%u\n", m + n - 2);
	}
}
