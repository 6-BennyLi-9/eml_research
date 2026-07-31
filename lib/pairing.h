#ifndef EML_RESEARCH_CANTOR_H
#define EML_RESEARCH_CANTOR_H
#include "integer.h"

namespace pairing {
	inline acc::integer algebra_domain(0);

	//cantor pairing
	//由于实际定义域与原函数不同，因此要做变换
	inline acc::integer pairing0(const acc::integer &a, const acc::integer &b) {
		return (a + b - acc::integer_1) * (a + b - acc::integer(2)) / acc::integer_2 + b + acc::integer_1;
	}
	inline acc::integer pairing(const acc::integer &a, const acc::integer &b) {
		return pairing0(a, b) + algebra_domain;
	}

	inline acc::integer t(const acc::integer &n) {
		return (acc::integer_1 + acc::sqrt(acc::integer(8) * n - acc::integer(15))) / acc::integer_2 + acc::integer_1;
	}

	//the two below : decoder

	inline acc::integer decode_a0(const acc::integer &x) {
		return (t(x)*t(x) + acc::integer(4) - t(x) - acc::integer(2) * x) / acc::integer_2;
	}

	inline acc::integer decode_b0(const acc::integer &x) {
		return (acc::integer(3) * t(x) + acc::integer(2) * x - t(x)*t(x) - acc::integer(4)) / acc::integer_2;
	}
	inline acc::integer decode_a(const acc::integer &n) {
		return decode_a0(n - algebra_domain);
	}

	inline acc::integer decode_b(const acc::integer &n) {
		return decode_b0(n - algebra_domain);
	}
}

#endif //EML_RESEARCH_CANTOR_H
