#ifndef EML_RESEARCH_CANTOR_H
#define EML_RESEARCH_CANTOR_H

#ifndef EML_RESEARCH_INTEGER_H
#include "integer.h"
#endif

namespace pairing {
	inline acc::acc_integer algebra_domain(0);

	//cantor pairing
	//由于实际定义域与原函数不同，因此要做变换
	inline acc::acc_integer pairing(const acc::acc_integer &a, const acc::acc_integer &b) {
		return (a + b - acc::integer_1) * (a + b - acc::acc_integer(2)) / acc::integer_2 + b + acc::integer_1 + algebra_domain;
	}

	inline acc::acc_integer t(const acc::acc_integer &n) {
		return (acc::integer_1 + acc::sqrt(acc::acc_integer(8) * n - acc::acc_integer(15))) / acc::integer_2 + acc::integer_1;
	}

	//the two below : decoder

	inline acc::acc_integer decode_a(const acc::acc_integer &n) {
		const acc::acc_integer &x = n - algebra_domain;
		return (t(x)*t(x) + acc::acc_integer(4) - t(x) - acc::acc_integer(2) * x) / acc::integer_2;
	}

	inline acc::acc_integer decode_b(const acc::acc_integer &n) {
		const acc::acc_integer &x = n - algebra_domain;
		return (acc::acc_integer(3) * t(x) + acc::acc_integer(2) * x - t(x)*t(x) - acc::acc_integer(4)) / acc::integer_2;
	}
}

#endif //EML_RESEARCH_CANTOR_H
