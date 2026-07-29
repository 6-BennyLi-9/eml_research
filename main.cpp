// #define DEBUG

#include "lib/pairing.h"
#include "lib/eml.h"
#include "lib/integer.h"

using acc::acc_integer;

static acc_integer emllib(const eml::eml &a) {
	acc_integer left, right;
	if (a.leftValue) {
		left = emllib(*a.leftValue.get());
	} else {
		left = acc::integer_1;
	}

	if (a.rightValue) {
		right = emllib(*a.rightValue.get());
	} else {
		right = acc::integer_1;
	}

	return pairing::pairing(left, right);
}

// ln x
const eml::eml example1 = eml::ln(eml::X);
// exp 2
const eml::eml example2 = eml::exp(eml::TWO);

static eml::eml emldecode(const acc_integer &n) {
#ifdef DEBUG
	printf("at ");
	acc::println(n);
	printf("t = ");
	acc::print(pairing::t(n));
	printf(", a = ");
	acc::print(pairing::decode_a(n));
	printf(", b = ");
	acc::println(pairing::decode_b(n));
#endif

	eml::eml res;
	if (pairing::decode_a(n) == acc::integer_1) {
		res.leftValue = nullptr;
	} else {
		res.leftValue = std::make_shared<eml::eml>(emldecode(pairing::decode_a(n)));
	}
	if (pairing::decode_b(n) == acc::integer_1) {
		res.rightValue = nullptr;
	} else {
		res.rightValue = std::make_shared<eml::eml>(emldecode(pairing::decode_b(n)));
	}

	return res;
}

int main() {
	// for (int i = 1; i <= 100; i++) {
	// 	printf("%d, sqrt = ", i);
	// 	acc::println_acc(acc::sqrt(acc_integer(i)));
	// }
	example1.println();
	example1.println0();
	emllib(example1).println();

	example2.println();
	example2.println0();
	emllib(example2).println();
	emllib(example2).printlnE();

	for (const int x: {42, 114514, 1919810, 123456789}) {
		eml::eml de = emldecode(acc_integer(x));
		de.println();
		de.println0();
	}
	return 0;
}
