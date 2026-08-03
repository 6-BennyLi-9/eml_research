#include <map>
#include <string>

#include "lib/integer.h"
#include "lib/pairing.h"
#include "util/table.h"

lazy::table table;
std::map<acc::integer, acc::integer> mem;
int N = 10;

int main(const int argc, char** argv) {
	if (argc - 1) {
		printf("Pre-input detected, option: %s\n", argv[1]);

		N = std::stoi(argv[1]);
	}

	mem[acc::integer_1] = acc::integer_0;
	mem[acc::integer_2] = acc::integer_1;

	const auto MAX_VAL = pairing::pairing0(acc::integer(N), acc::integer(N));

	for (auto i = acc::integer(3); i <= MAX_VAL; i += acc::integer_1) {
		mem[i] = std::max(mem[pairing::decode_a0(i)], mem[pairing::decode_b0(i)]) + acc::integer_1;
	}

	const auto n = acc::integer(N);
	for (auto i = acc::integer_1; i <= n; i += acc::integer_1) {
		for (auto j = acc::integer_1; j <= n; j += acc::integer_1) {
			table.put(mem[pairing::pairing0(i, j)].to_string());
		}
		table.wrap();
	}

	table.print();
	table = lazy::table();
	for (auto i = acc::integer_1; i <= n; i += acc::integer_1) {
		for (auto j = acc::integer_1; j <= n; j += acc::integer_1) {
			table.put(pairing::pairing0(i, j).to_string());
		}
		table.wrap();
	}
	table.print();

	return 0;
}