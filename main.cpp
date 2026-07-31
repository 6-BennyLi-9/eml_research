// #define DEBUG

#include <cstring>
#include <stdexcept>

#include "emllib.h"
#include "model.h"
#include "lib/eml.h"
#include "lib/integer.h"

using acc::integer;

// ln x
const eml::eml example1 = eml::ln(eml::X);
// exp 2
const eml::eml example2 = eml::exp(eml::TWO);

const model::model core = {
	{
		// "高精度平方根测试", "debug",
		"DEBUG", "debug",
		[] {
			eml::algebra_definition(2);
			const auto times = eml::eml{eml::eml{nullptr, {{eml::ln({nullptr, eml::X}), eml::eml(2)}, nullptr}},nullptr};
			times.println();
			eml::emllib(times).println();
			auto oldTimes = eml::unsafe_times(eml::eml(1), eml::eml(2));
			oldTimes.println();

			acc::integer("1006223783010386972525519400225122423494749603838855805076470783074657").println();

			eml::emldecodeS(0, acc::integer(1)).println();
			eml::emllibS(0, eml::E).println();
		}
	},
	{
		// "EMLLIB 样例", "展示 EMLLIB 是如何工作的",
		"SAMPLE EMLLIB", "Shows how does EMLLIB work.",
		[]{
			eml::algebra_definition(1, {"x"});
			example1.println();
			example1.println0();
			eml::emllib(example1).println();

			eml::algebra_definition(0, {});
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
		[]{
			for (const int x: {10, 42, 114514, 1919810, 123456789}) {
				eml::eml de = eml::emldecode(integer(x));
				de.println();
				de.println0();
			}
		}
	},
	{
		"SAMPLE ALGEBRA DECODER", "Shows how does EMLLIB DECODER work with algebra.",
		[] {
			eml::algebra_definition(2,{"x", "y"});

			for (const int x: {10, 42, 114514, 1919810, 123456789}) {
				eml::eml de = eml::emldecode(integer(x));
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
	}
};

int main(const int argc, char* argv[]) {
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

			printf("\n==========================\n\nFinished successfully in %lld ms.\n", static_cast<long long int>(core[mode].run().count()));
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

		printf("\n\n==========================\n\nFinished successfully in %lld ms.\n", static_cast<long long int>(core[mode].run().count()));
	}
	return 0;
}
