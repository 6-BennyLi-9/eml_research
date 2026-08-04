#ifndef EML_RESEARCH_CANTOR_H
#define EML_RESEARCH_CANTOR_H
#include "integer.h"

namespace pairing {
	inline acc::unsigned_integer algebra_domain(0);

	//cantor pairing
	//由于实际定义域与原函数不同，因此要做变换
	inline acc::unsigned_integer pairing0(const acc::unsigned_integer &a, const acc::unsigned_integer &b) {
		return (a + b - acc::integer_1) * (a + b - acc::unsigned_integer(2)) / acc::integer_2 + b + acc::integer_1;
	}

	inline acc::unsigned_integer pairing(const acc::unsigned_integer &a, const acc::unsigned_integer &b) {
		return pairing0(a, b) + algebra_domain;
	}

	inline acc::unsigned_integer t(const acc::unsigned_integer &n) {
		return (acc::integer_1 + acc::sqrt(acc::unsigned_integer(8) * n - acc::unsigned_integer(15))) / acc::integer_2 + acc::integer_1;
	}

	//the two below : decoder

	inline acc::unsigned_integer decode_a0(const acc::unsigned_integer &x) {
		return (t(x) * t(x) + acc::unsigned_integer(4) - t(x) - acc::unsigned_integer(2) * x) / acc::integer_2;
	}

	inline acc::unsigned_integer decode_b0(const acc::unsigned_integer &x) {
		return (acc::unsigned_integer(3) * t(x) + acc::unsigned_integer(2) * x - t(x) * t(x) - acc::unsigned_integer(4)) / acc::integer_2;
	}

	inline acc::unsigned_integer decode_a(const acc::unsigned_integer &n) {
		return decode_a0(n - algebra_domain);
	}

	inline acc::unsigned_integer decode_b(const acc::unsigned_integer &n) {
		return decode_b0(n - algebra_domain);
	}
}

#endif //EML_RESEARCH_CANTOR_H
