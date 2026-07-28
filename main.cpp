#include "lib/cantor.h"

int main() {
	auto res = cantor::cantor(acc_integer(65465116), acc_integer(23185));
	acc::println_acc(res);
	acc::println_acc(cantor::decode_a(res));
	acc::println_acc(cantor::decode_b(res));
	return 0;
}
