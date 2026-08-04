#ifndef EML_RESEARCH_EMLLIB_H
#define EML_RESEARCH_EMLLIB_H
#include <cassert>
#include <stdexcept>

#include "lib/eml.h"
#include "lib/pairing.h"
#include "lib/integer.h"

namespace eml {
	inline bool allow_algebra_expression = false;

	inline acc::integer emllib(const eml &a) {
		if (a.type) {
			if (allow_algebra_expression) {
				return acc::integer(a.type) + acc::integer_1;
			}
			throw std::logic_error("Did not support algebra expression!");
		}

		acc::integer left, right;
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

	inline eml emldecode(const acc::integer &n) {
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
		acc::integer cache = pairing::decode_a(n);
		if (cache == acc::integer_1) {
		} else if (cache <= pairing::algebra_domain + acc::integer_1) {
			res.lValue = std::make_shared<eml>(eml((cache - acc::integer_1).to_int()));
		} else {
			res.lValue = std::make_shared<eml>(emldecode(cache));
		}

		cache = pairing::decode_b(n);
		if (cache == acc::integer_1) {
		} else if (cache <= pairing::algebra_domain + acc::integer_1) {
			res.rValue = std::make_shared<eml>(eml((cache - acc::integer_1).to_int()));
		} else {
			res.rValue = std::make_shared<eml>(emldecode(cache));
		}

		return res;
	}

	inline std::vector<std::string> std_naming(const int count) {
		assert(count >= 0);

		std::vector<std::string> names;
		for (int i = 0; i < count && i < 3; i++) {
			names.push_back(new char[]{static_cast<char>(i + 'x'), '\0'}); // NOLINT(*-narrowing-conversions)
		}

		for (int i = 3; i < count && i < 7; i++) {
			names.push_back(new char[]{static_cast<char>(i + '^'), '\0'}); // NOLINT(*-narrowing-conversions)
		}

		for (int i = 7; i < count && i < 26; i++) {
			names.push_back(new char[]{static_cast<char>(i + '_'), '\0'}); // NOLINT(*-narrowing-conversions)
		}

		for (int i = 26; i < count ; i++) {
			names.push_back(std::string{"A_"} + std::to_string(i -25)); // NOLINT(*-narrowing-conversions)
		}

		return names;
	}

	inline void algebra_definition(const int count, const std::vector<std::string> &names) {
		assert(count == names.size());

		allow_algebra_expression = true;
		pairing::algebra_domain = acc::integer(count);

		for (int i = 0; i < count; i++) {
			algebra[i + 1] = names[i];
		}
	}

	inline void algebra_definition(const int count) {
		algebra_definition(count, std_naming(count));
	}

	inline acc::integer emllibS(const int count, const eml &x) {
		algebra_definition(count);
		return emllib(x);
	}

	inline eml emldecodeS(const int count, const acc::integer &x) {
		algebra_definition(count);
		return emldecode(x);
	}

	inline eml emlexplict(const int count, const eml &disc, const std::vector<eml> &par) {
		assert(count == par.size());
		if (disc.type) {
			return par[disc.type - 1];
		}
		eml res;

		if (disc.lValue) {
			res.lValue = std::make_shared<eml>(emlexplict(count, *(disc.lValue), par));
		}

		if (disc.rValue) {
			res.rValue = std::make_shared<eml>(emlexplict(count, *(disc.rValue), par));
		}

		return res;
	}

	inline acc::integer emllib(const emlexp& n) {
		return emllibS(n.algebra_count(), n.target());
	}

	static emlexp decodeEx0(const acc::integer &val) {
		const auto lV = pairing::decode_a0(val);
		const auto rV = pairing::decode_b0(val);

		const auto w = lV * (lV + acc::integer_1) / acc::integer_2;

		return {(lV - acc::integer_1).to_int(), emldecodeS((lV - acc::integer_1).to_int(), rV + w)};
	}

	static emlexp decodeEx(const acc::integer &val) {
		if (val.negative) {
			return {1, eml(val.opposite().to_int())};
		}

		if (val == acc::integer_0) {
			throw std::invalid_argument("DECLARE ONE");
		}

		return decodeEx0(val + acc::integer_1);
	}

	static acc::integer emllibEx(const int algebra_count, const eml &target) {
		if (target.type) {
			//leaf
			return acc::integer{-target.type};
		}

		const auto w = algebra_count * (algebra_count - 1) / 2;

		return pairing::pairing0(acc::integer{algebra_count + 1}, emllibS(algebra_count, target) - acc::integer{w});
	}

	static acc::integer emllibEx(const emlexp &val) {
		return emllibEx(val.algebra_count(), val.target());
	}
}

#endif //EML_RESEARCH_EMLLIB_H
