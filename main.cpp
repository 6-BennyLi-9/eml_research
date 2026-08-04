// #define DEBUG

#include <cstring>

#include "emllib.h"
#include "emllibEx.h"
#include "util/model.h"
#include "lib/eml.h"
#include "lib/emlsurvey.h"
#include "lib/integer.h"
#include "util/table.h"

// ln x
const eml::eml example1 = eml::ln(eml::X);
// exp 2
const eml::eml example2 = eml::exp(eml::TWO);
const lazy::model core = {
	{
		"DEBUG", "debug",
		[] {
#define int_of(s) acc::integer(s)
			int_of(-1).println();
			(int_of(-1) + int_of(-2)).println();
			(int_of(-1) - int_of(-2)).println();
			(int_of(-1) / int_of(1)).println();
			(int_of(-2) / int_of(1)).println();
			(int_of(-1) * int_of(-2)).println();
			(int_of(1) * int_of(-2)).println();
#undef inf_of
		}
	},
	{
		// "EMLLIB 样例", "展示 EMLLIB 是如何工作的",
		"SAMPLE EMLLIB", "Shows how does EMLLIB work.",
		[] {
			eml::algebra_definition(1);
			example1.println();
			example1.println0();
			eml::emllib(example1).println();

			eml::algebra_definition(0);
			example2.println();
			example2.println0();
			eml::emllib(example2).println();
			eml::emllib(example2).printlnE();

			eml::emllib(eml::ZERO).println();
		}
	},
	{
		// "EMLLIB 解码样例", "展示 EMLLIB 是如何被解码的",
		"SAMPLE EMLLIB DECODER", "Shows how does EMLLIB DECODER work.",
		[] {
			for (const int x: {10, 42, 114514, 1919810, 123456789}) {
				acc::integer(x).println();
				eml::eml de = eml::emldecode(acc::integer(x));
				de.println();
				de.println0();
			}
		}
	},
	{
		"SAMPLE ALGEBRA DECODER", "Shows how does EMLLIB DECODER work with algebra.",
		[] {
			eml::algebra_definition(2, {"x", "y"});

			for (const int x: {10, 42, 114514, 1919810, 123456789}) {
				acc::integer(x).println();
				eml::eml de = eml::emldecode(acc::integer(x));
				de.println();
				de.println0();
			}
		}
	},
	{
		"SAMPLE EMLLIB EXPLICT", "Shows how does EMLLIB EXPLICT replace the algebra with other algebra.",
		[] {
			auto decode = eml::emldecodeS(2, acc::integer(9527));
			decode.println();

			decode = eml::emlexplict(2, decode, {eml::E, eml::ZERO});
			decode.println();
		}
	},
	{
		"SAMPLE EMLSURVEY", "Shows how does EMLSURVEY work.",
		[] {
			eml::ZERO.println0();
			auto op = eml::ZERO;
			// op.println();
			eml::survey(op).println();
			printf("\n");

			op = eml::tan(eml::X);
			eml::survey(op).println();
			printf("\n");

			op = eml::sin(eml::X) / eml::cos(eml::X);
			eml::survey(op).println();
			printf("\n");
		}
	},
	{
		"SAMPLE EMLLIB PLUS", "Shows how does EMLLIB work strictly.",
		[] {
			constexpr int N_S = 1;
			constexpr int N_E = 17;
			lazy::table t;

			for (int i = N_S; i <= N_E; ++i) {
				for (int j = N_S; j <= N_E; ++j) {
					const auto s = eml::emldecodeS(i - 1, acc::integer(j + (i + 1) * i / 2));

					t.put(s.to_string());
					// eml::survey(s).println();
				}
				t.wrap();
			}

			printf("\n");
			t.with_index(N_S, N_S).print();
		}
	},
	{
		"CANTOR BINARY TREE DEPTH", "The pairing function which used in this programme is based on the cantor pairing function. This programme shows the depth of each tree in emllib.",
		[] {
			constexpr int N = 25;
			lazy::table t;
			std::map<acc::integer, acc::integer> mem;

			mem[acc::integer_1] = acc::integer_0;
			mem[acc::integer_2] = acc::integer_1;

			const auto MAX_VAL = pairing::pairing0(acc::integer_1, acc::integer(N));

			for (auto i = acc::integer(3); i <= MAX_VAL; i += acc::integer_1) {
				mem[i] = std::max(mem[pairing::decode_a0(i)], mem[pairing::decode_b0(i)]) + acc::integer_1;
			}

			for (int i = 1; i <= N; ++i) {
				t.put(std::to_string(i));
				t.put(mem[pairing::pairing0(acc::integer_1, acc::integer(i))].to_string());
				t.wrap();
			}

			t.print();

			printf("Depth of <x,y> equals to the depth of the maximum of the depth of <x,1> and <1,y>.\nSee more in bin_depth.cpp.\n");
		}
	},
	{
		"SAMPLE EMLLIB EX", "Shows how does EMLLIB EX work.",
		[] {
			eml::algebra_definition(50);
			printf("Range: {..., -3, -2, -1}\n");

			eml::decodeEx(acc::integer{-3}).target().println();
			eml::decodeEx(acc::integer{-2}).target().println();
			eml::decodeEx(acc::integer{-1}).target().println();

			printf("Range: {0}\n1\nRange: {1, 2, 3, ...}\n");

			eml::decodeEx(acc::integer{1}).target().println();
			eml::decodeEx(acc::integer{2}).target().println();
			eml::decodeEx(acc::integer{3}).target().println();
		}
	}
};


int main(const int argc, char *argv[]) {
	// freopen("main.out", "w", stdout);

	for (int i = 0; i < core.size(); ++i) {
		printf("%d. [%s]\n    -- %s\n", i, core[i].name.c_str(), core[i].description.c_str());
	}

	printf("==========================\n");

	if (argc - 1) {
		printf("Pre-input detected, option: %s\n", argv[1]);

		if (!strcmp(argv[1], "-m") || !strcmp(argv[1], "--mode")) {
			const int mode = std::stoi(argv[2]);

			printf("Mode selected: %d\n", mode);

			if (mode < 0 || mode >= core.size()) {
				printf("Error: invalid mode selected: %d\n", mode);
				return -1;
			}

			printf("\n==========================\n\nFinished successfully in %lld ms.\n",
					static_cast<long long int>(core[mode].run().count()));
		} else {
			printf("Error: invalid option code: %s\n", argv[0]);
		}
	} else {
		printf("In manual input period. Please input the code:");
		char str[10];
		scanf("%s", str);
		const int mode = std::stoi(str);

		if (mode < 0 || mode >= core.size()) {
			printf("Error: invalid mode selected: %d\n", mode);
			return -1;
		}

		printf("\n\n==========================\n\nFinished successfully in %lld ms.\n",
				static_cast<long long int>(core[mode].run().count()));
	}
	return 0;
}
