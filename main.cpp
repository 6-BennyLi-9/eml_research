// #define DEBUG

#include <stdexcept>

#include "emllib.h"
#include "model.h"
#include "lib/eml.h"
#include "lib/integer.h"

using acc::acc_integer;

// ln x
const eml::eml example1 = eml::ln(eml::X);
// exp 2
const eml::eml example2 = eml::exp(eml::TWO);

const model::model core = {
	{
		// "高精度平方根测试", "debug",
		"TEST SQRT", "debug",
		[]()-> void {
			for (int i = 1; i <= 100; i++) {
				printf("%d, sqrt = ", i);
				acc::println(acc::sqrt(acc_integer(i)));
			}
		}
	},
	{
		// "EMLLIB 样例", "展示 EMLLIB 是如何工作的",
		"SAMPLE EMLLIB", "Shows how does EMLLIB work.",
		[]()-> void {
			example1.println();
			example1.println0();
			eml::emllib(example1).println();

			example2.println();
			example2.println0();
			eml::emllib(example2).println();
			eml::emllib(example2).printlnE();
		}
	},
	{
		// "EMLLIB 解码样例", "展示 EMLLIB 是如何被解码的",
		"SAMPLE EMLLIB DECODER", "Shows how does EMLLIB DECODER work.",
		[]()-> void {
			for (const int x: {42, 114514, 1919810, 123456789}) {
				eml::eml de = eml::emldecode(acc_integer(x));
				de.println();
				de.println0();
			}
		}
	}
};

int main() {
	for (int i = 0; i < core.size(); ++i) {
		printf("%d. [%s]\n    -- %s\n", i, core[i].name, core[i].description);
	}
	return 0;
}
