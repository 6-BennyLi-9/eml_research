#ifndef EML_RESEARCH_CANTOR_H
#define EML_RESEARCH_CANTOR_H

#ifndef EML_RESEARCH_INTEGER_H
#include "integer.h"
#endif

using acc::acc_integer;

namespace pairing {
	//cantor pairing
	//由于实际定义域与原函数不同，因此要做变换
	inline acc_integer pairing(const acc_integer &a, const acc_integer &b) {
		return (a+b) * (a + b - acc_integer(3)) / acc::integer_2 + b + acc::integer_2;
	}

	inline acc_integer t(const acc_integer &n) {
		return (acc::integer_1 + acc::sqrt(acc_integer(8) * n - acc_integer(15))) / acc::integer_2 + acc::integer_1;
	}

	//the two below : decoder

	inline acc_integer decode_a(const acc_integer &n) {
		return (t(n)*t(n) + acc_integer(4) - t(n) - acc_integer(2) * n) / acc::integer_2;
	}

	inline acc_integer decode_b(const acc_integer &n) {
		return (acc_integer(3) * t(n) +  acc_integer(2) * n- t(n)*t(n) - acc_integer(4)) / acc::integer_2;
	}
}

#endif //EML_RESEARCH_CANTOR_H
