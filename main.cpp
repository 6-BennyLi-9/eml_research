#include "lib/cantor.h"
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

	return cantor::cantor(left, right);
}

// ln x
const eml::eml example1 = eml::ln(eml::X);

static eml::eml emldecode(acc_integer n) {
	eml::eml res;
	if (cantor::decode_a(n) == acc::integer_1) {
		res.leftValue = nullptr;
	} else {
		res.leftValue = std::make_shared<eml::eml>(emldecode(cantor::decode_a(n)));
	}
	if (cantor::decode_b(n) == acc::integer_1) {
		res.rightValue = nullptr;
	} else {
		res.rightValue = std::make_shared<eml::eml>(emldecode(cantor::decode_b(n)));
	}

	return res;
}

int main() {
	example1.println();
	example1.println0();

	acc::println_acc(emllib(example1));

	eml::eml example2 = emldecode(acc_integer(4));
	example2.println();
	example2.println0();
	return 0;
}
