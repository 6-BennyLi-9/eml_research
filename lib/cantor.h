#pragma once
#ifndef EML_RESEARCH_CANTOR_H
#ifndef EML_RESEARCH_INTEGER_H
#include "integer.h"
#endif
using acc::acc_integer;

namespace cantor {//cantor pairing
	inline acc_integer cantor(const acc_integer &a, const acc_integer &b) {
		return (a+b) * (a + b + acc::integer_1) / acc::integer_2 + b;
	}

	inline acc_integer decode_w(const acc_integer &n) {
		return (acc::sqrt(acc_integer(8) * n + acc::integer_1) - acc::integer_1) / acc::integer_2;
	}

	inline acc_integer decode_t(const acc_integer &n) {
		return decode_w(n) * (decode_w(n) + acc::integer_1) / acc::integer_2;
	}

	//the two below : decoder

	inline acc_integer decode_b(const acc_integer &n) {
		return n - decode_t(n);
	}

	inline acc_integer decode_a(const acc_integer &n) {
		return decode_w(n) - decode_b(n);
	}
}

#define EML_RESEARCH_CANTOR_H

#endif //EML_RESEARCH_CANTOR_H
