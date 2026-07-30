#ifndef EML_RESEARCH_EMLLIB_H
#define EML_RESEARCH_EMLLIB_H
#include <assert.h>
#include <stdexcept>

#include "lib/eml.h"
#include "lib/pairing.h"
#include "lib/integer.h"

namespace eml{
	inline bool allow_algebra_expression = false;

	inline acc::acc_integer emllib0(const eml &a) {
		if (a.type) {
			if (allow_algebra_expression) {
				return acc::acc_integer(a.type) + acc::integer_1;
			}
			throw std::logic_error("Did not support algebra expression!");
		}

		acc::acc_integer left, right;
		if (a.leftValue) {
			left = emllib0(*a.leftValue.get());
		} else {
			left = acc::integer_1;
		}

		if (a.rightValue) {
			right = emllib0(*a.rightValue.get());
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
		acc::acc_integer cache = pairing::decode_a(n);
		if (cache == acc::integer_1) {
			res.leftValue = nullptr;
		} else if (cache <= pairing::algebra_domain + acc::integer_1) {
			res.leftValue = std::make_shared<eml>(eml((cache - acc::integer_1).toSigned()));
		} else {
			res.leftValue = std::make_shared<eml>(emldecode(cache));
		}

		cache = pairing::decode_b(n);
		if (cache == acc::integer_1) {
			res.rightValue = nullptr;
		} else if (cache <= pairing::algebra_domain + acc::integer_1) {
			res.rightValue = std::make_shared<eml>(eml((cache - acc::integer_1).toSigned()));
		} else {
			res.rightValue = std::make_shared<eml>(emldecode(cache));
		}

		return res;
	}

	inline void algebra_definition(const int &count, const std::vector<const char *> &names) {
		assert(count == names.size());

		allow_algebra_expression = true;
		pairing::algebra_domain = acc::acc_integer(count);

		for (int i = 0; i < count; i++) {
			algebra[i + 1] = names[i];
		}
	}
}

#endif //EML_RESEARCH_EMLLIB_H
