#include <map>
#include <set>
#include <string>

#include "lib/integer.h"
#include "lib/pairing.h"
#include "util/table.h"

static lazy::table table;
static std::map<acc::integer, acc::integer> mem;
static int N = 4;
static std::set<acc::integer> G;
static std::set<acc::integer> G_p;

static void printG(int x) {
	printf("G_%d = {", x);
	bool flag = false;
	for (const auto& item: G) {
		if (flag) {
			printf(", ");
		}
		flag = true;

		item.print();
	}

	printf("}\n");
}

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

	printf("G_n: List of values which depth is n.\n");
	G.insert(acc::integer_1);
	G_p.insert(acc::integer_1);

	std::set<acc::integer> G_n;
	std::set<acc::integer> G_p_n;

	printG(1);

	for (int i = 1; i < N; ++i) {
		G_n.clear();
		G_p_n.clear();

		for (const auto& itemX: G) {
			for (const auto& itemY: G_p) {
				G_n.insert(pairing::pairing0(itemX, itemY));
			}
		}

		for (const auto& itemX: G_p) {
			for (const auto& itemY: G) {
				G_n.insert(pairing::pairing0(itemX, itemY));
			}
		}

		G = G_n;
		for (const auto& item: G_n) {
			G_p.insert(item);
		}

		printG(i + 1);
	}
	return 0;
}