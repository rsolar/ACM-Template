#include <bits/stdc++.h>
using namespace std;

int main() {
	string s;
	while (cin >> s) {
		for (size_t i = 0; i < s.size(); i++) {
			if (s.substr(i, 5) == "Apple") {
				puts("MAI MAI MAI!");
			} else if (s.substr(i, 6) == "iPhone") {
				puts("MAI MAI MAI!");
			} else if (s.substr(i, 4) == "iPod") {
				puts("MAI MAI MAI!");
			} else if (s.substr(i, 4) == "iPad") {
				puts("MAI MAI MAI!");
			} else if (s.substr(i, 4) == "Sony") {
				puts("SONY DAFA IS GOOD!");
			}
		}
	}
}
