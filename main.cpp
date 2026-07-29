#define DEBUG

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

static eml::eml emldecode(const acc_integer &n) {
#ifdef DEBUG
	printf("at ");
	acc::println_acc(n);
	printf("t = ");
	acc::print_acc(pairing::t(n));
	printf(", a = ");
	acc::print_acc(pairing::decode_a(n));
	printf(", b = ");
	acc::println_acc(pairing::decode_b(n));
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
	for (int i = 1; i <= 100; i++) {
		printf("%d, sqrt = ", i);
		acc::println_acc(acc::sqrt(acc_integer(i)));
	}
	// example1.println();
	// example1.println0();
	//
	// acc::println_acc(emllib(example1));
	//
	// eml::eml example2 = emldecode(acc_integer(1654));
	// example2.println();
	// example2.println0();
	return 0;
}
