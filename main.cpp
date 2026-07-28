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

// x + 2
const eml::eml example1 = eml::plus(eml::X, eml::TWO);

int main() {
	example1.println();
	example1.println0();

	acc::println_acc(emllib(example1));

	return 0;
}
