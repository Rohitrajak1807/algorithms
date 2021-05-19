#include <iostream>
#include <cmath>

long double newton_sqrt(long double n, long double tolerance=0.0000001);

int main() {
	long double n = 18446744073709551615.0;
	long double root = newton_sqrt(n);
	std::cout << root << '\n' << std::sqrt(n) << '\n' << std::abs(root - std::sqrt(n));
	return 0;
}

long double newton_sqrt(long double n, long double tolerance) {
	long double a = n / 2;
	while(std::abs((n / a) -a) > tolerance) {
		a = (a + (n/a))/2;
	}
	return a;
}
