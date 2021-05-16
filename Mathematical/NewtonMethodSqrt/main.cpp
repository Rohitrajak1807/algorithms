#include <iostream>
#include <cmath>

double newton_sqrt(double n, double tolerance=0.0000001);

int main() {
	double n = 18446744073709551615.0;
	double root = newton_sqrt(n);
	std::cout << root << '\n' << std::sqrt(n) << '\n' << std::abs(root - std::sqrt(n));
	return 0;
}

double newton_sqrt(double n, double tolerance) {
	double a = n / 2;
	while(std::abs((n / a) -a) > tolerance) {
		a = (a + (n/a))/2;
	}
	return a;
}
