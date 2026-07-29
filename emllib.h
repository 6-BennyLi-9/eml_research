#ifndef EML_RESEARCH_EMLLIB_H
#define EML_RESEARCH_EMLLIB_H
#include <stdexcept>

#include "lib/eml.h"
#include "lib/pairing.h"
#include "lib/integer.h"

namespace eml{
	inline acc::acc_integer emllib(const eml &a) {
		if (a.type) {
			throw std::runtime_error("Type not supported");
		}

		acc::acc_integer left, right;
		if (a.leftValue) {
			left = emllib(*a.leftValue.get());
		} else {
			left = acc::integer_1;
		}

		if (a.rightValue) {
			right = emllib(*a.rightValue.get());
		} else {
			right = acc::integer_1;
		}

		return pairing::pairing(left, right);
	}

	inline eml emldecode(const acc::acc_integer &n) {
#ifdef DEBUG
		printf("at ");
		acc::println(n);
		printf("t = ");
		acc::print(pairing::t(n));
		printf(", a = ");
		acc::print(pairing::decode_a(n));
		printf(", b = ");
		acc::println(pairing::decode_b(n));
#endif

		eml res;
		if (pairing::decode_a(n) == acc::integer_1) {
			res.leftValue = nullptr;
		} else {
			res.leftValue = std::make_shared<eml>(emldecode(pairing::decode_a(n)));
		}
		if (pairing::decode_b(n) == acc::integer_1) {
			res.rightValue = nullptr;
		} else {
			res.rightValue = std::make_shared<eml>(emldecode(pairing::decode_b(n)));
		}

		return res;
	}
}

#endif //EML_RESEARCH_EMLLIB_H
