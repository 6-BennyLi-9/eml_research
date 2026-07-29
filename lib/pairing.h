#ifndef EML_RESEARCH_CANTOR_H
#define EML_RESEARCH_CANTOR_H

#ifndef EML_RESEARCH_INTEGER_H
#include "integer.h"
#endif

namespace pairing {
	//cantor pairing
	//由于实际定义域与原函数不同，因此要做变换
	inline acc::acc_integer pairing(const acc::acc_integer &a, const acc::acc_integer &b) {
		return (a+b) * (a + b - acc::acc_integer(3)) / acc::integer_2 + b + acc::integer_2;
	}

	inline acc::acc_integer t(const acc::acc_integer &n) {
		return (acc::integer_1 + acc::sqrt(acc::acc_integer(8) * n - acc::acc_integer(15))) / acc::integer_2 + acc::integer_1;
	}

	//the two below : decoder

	inline acc::acc_integer decode_a(const acc::acc_integer &n) {
		return (t(n)*t(n) + acc::acc_integer(4) - t(n) - acc::acc_integer(2) * n) / acc::integer_2;
	}

	inline acc::acc_integer decode_b(const acc::acc_integer &n) {
		return (acc::acc_integer(3) * t(n) + acc::acc_integer(2) * n- t(n)*t(n) - acc::acc_integer(4)) / acc::integer_2;
	}
}

#endif //EML_RESEARCH_CANTOR_H
