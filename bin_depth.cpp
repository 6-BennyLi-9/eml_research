#include <map>
#include <set>
#include <string>

#include "lib/integer.h"
#include "lib/pairing.h"
#include "util/table.h"

static lazy::table table;
static std::map<acc::unsigned_integer, acc::unsigned_integer> mem;
static int N = 4;
static std::set<acc::unsigned_integer> G;
static std::set<acc::unsigned_integer> Gp;
static acc::unsigned_integer C = acc::integer_1;
static acc::unsigned_integer C_p = acc::integer_1;

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
	printf("Gp_%d = {", x);
	flag = false;
	for (const auto& item: Gp) {
		if (flag) {
			printf(", ");
		}
		flag = true;

		item.print();
	}

	printf("}\n");
}

static void printDecode(const acc::unsigned_integer& x) {
	if (x == acc::integer_1) {
		// printf("1");
		printf("Arrived Leaf: 1\n");
		return;
	}

	printf("At %s, can be decode to <%s, %s>\n", x.to_string().c_str(), pairing::decode_a0(x).to_string().c_str(), pairing::decode_b0(x).to_string().c_str());
	printDecode(pairing::decode_a0(x));
	printDecode(pairing::decode_b0(x));

	// printf("<");
	// printDecode(pairing::decode_a0(x));
	// printf(", ");
	// printDecode(pairing::decode_b0(x));
	// printf(">");
}

int main(const int argc, char** argv) {
	if (argc - 1) {
		printf("Pre-input detected, option: %s\n", argv[1]);

		N = std::stoi(argv[1]);
	}

	mem[acc::integer_1] = acc::integer_0;
	mem[acc::integer_2] = acc::integer_1;

	const auto MAX_VAL = pairing::pairing0(acc::unsigned_integer(N), acc::unsigned_integer(N));

	for (auto i = acc::unsigned_integer(3); i <= MAX_VAL; i += acc::integer_1) {
		mem[i] = std::max(mem[pairing::decode_a0(i)], mem[pairing::decode_b0(i)]) + acc::integer_1;
	}

	const auto n = acc::unsigned_integer(N);
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
	printf("C_n: Count of values which depth is n.\n");
	G.insert(acc::integer_1);
	Gp.insert(acc::integer_1);

	std::set<acc::unsigned_integer> Gnew;

	printG(1);
	printf("C_1:1\n");

	for (int i = 1; i < N; ++i) {
		Gnew.clear();

		for (const auto& itemX: G) {
			for (const auto& itemY: Gp) {
				Gnew.insert(pairing::pairing0(itemX, itemY));
				Gnew.insert(pairing::pairing0(itemY, itemX));
			}
		}

		G = Gnew;
		for (const auto& item: G) {
			Gp.insert(item);
		}

		printG(i + 1);

		C = C * C + acc::integer_2 * C * (C_p - C);
		C_p = C_p + C;

		printf("C_%d:", i + 1);
		C.println();

		// printf("%d\n", static_cast<int>(G.size()));
	}

	printDecode(acc::unsigned_integer(21));
	return 0;
}