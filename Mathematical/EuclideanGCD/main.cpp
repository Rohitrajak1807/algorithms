#include <iostream>

struct vec2 {
	int64_t x;
	int64_t y;
};

int64_t euclid_gcd(int64_t a, int64_t b);

// given an equation xa + by = gcd(a,b), this algorithm finds x and y
vec2 extended_euclid_gcd(int64_t a, int64_t b);

int main() {
	std::cout << euclid_gcd(16, 4) << '\n';
	vec2 out = extended_euclid_gcd(16, 4);
	std::cout << out.x << '\t' << out.y;
	return 0;
}

int64_t euclid_gcd(int64_t a, int64_t b) {
	while (a != 0) {
		int64_t t = a;
		a = b % a;
		b = t;
	}
	return b;
}

vec2 extended_euclid_gcd(int64_t a, int64_t b) {
	int64_t x = 0,
			y = 1,
			u = 1,
			v = 0;
	while (a != 0) {
		int64_t q = b / a,
				r = b % a,
				m = x - u * q,
				n = y - v * q;
		b = a;
		a = r;
		x = u;
		y = v;
		u = m;
		v = n;
	}
	return {.x=x, .y=y};
}
