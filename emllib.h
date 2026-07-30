#ifndef EML_RESEARCH_EMLLIB_H
#define EML_RESEARCH_EMLLIB_H
#include <cassert>
#include <stdexcept>

#include "lib/eml.h"
#include "lib/pairing.h"
#include "lib/integer.h"

namespace eml{
	inline bool allow_algebra_expression = false;

	inline acc::acc_integer emllib(const eml &a) {
		if (a.type) {
			if (allow_algebra_expression) {
				return acc::acc_integer(a.type) + acc::integer_1;
			}
			throw std::logic_error("Did not support algebra expression!");
		}

		acc::acc_integer left, right;
		if (a.lValue) {
			left = emllib(*a.lValue.get());
		} else {
			left = acc::integer_1;
		}

		if (a.rValue) {
			right = emllib(*a.rValue.get());
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
			res.lValue = nullptr;
		} else if (cache <= pairing::algebra_domain + acc::integer_1) {
			res.lValue = std::make_shared<eml>(eml((cache - acc::integer_1).toSigned()));
		} else {
			res.lValue = std::make_shared<eml>(emldecode(cache));
		}

		cache = pairing::decode_b(n);
		if (cache == acc::integer_1) {
			res.rValue = nullptr;
		} else if (cache <= pairing::algebra_domain + acc::integer_1) {
			res.rValue = std::make_shared<eml>(eml((cache - acc::integer_1).toSigned()));
		} else {
			res.rValue = std::make_shared<eml>(emldecode(cache));
		}

		return res;
	}

	inline std::vector<const char *> std_naming(const int &count) {
		assert(count >= 0);
		assert(count <= 26);

		std::vector<const char *> names;
		for (int i = 0; i < count && i < 3; i++) {
			names.push_back(new char[]{static_cast<char>(i + 'x'), '\0'}); // NOLINT(*-narrowing-conversions)
		}

		for (int i = 3; i < count; i++) {
			names.push_back(new char[]{static_cast<char>(i + 'a'), '\0'}); // NOLINT(*-narrowing-conversions)
		}

		return names;
	}

	inline void algebra_definition(const int &count, const std::vector<const char *> &names) {
		assert(count == names.size());

		allow_algebra_expression = true;
		pairing::algebra_domain = acc::acc_integer(count);

		algebra.clear();
		for (int i = 0; i < count; i++) {
			algebra[i + 1] = names[i];
		}
	}

	inline acc::acc_integer emllibS(const int &count, const eml &x) {
		algebra_definition(count, std_naming(count));
		return emllib(x);
	}
	inline eml emldecodeS(const int &count, const acc::acc_integer &x) {
		algebra_definition(count, std_naming(count));
		return emldecode(x);
	}
}

#endif //EML_RESEARCH_EMLLIB_H
