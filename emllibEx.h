#ifndef EML_RESEARCH_EMLLIB_PLUS_H
#define EML_RESEARCH_EMLLIB_PLUS_H
#include "emllib.h"
#include "lib/eml.h"

namespace eml {
	const auto DECLARE_ONE = std::invalid_argument("DECLARE ONE");

	class eml_expression {
		const int _algebra_count;
		const eml _target;
	public:
		eml_expression(const int algebra_count, const eml &target)
			: _algebra_count(algebra_count),
			_target(target) {
		}

		[[nodiscard]] int algebra_count() const {
			return _algebra_count;
		}

		[[nodiscard]] eml target() const {
			return _target;
		}
	};

	static eml_expression decodeEx0(const acc::integer &val) {
		const auto lV = pairing::decode_a0(val);
		const auto rV = pairing::decode_b0(val);

		const auto w = lV * (lV + acc::integer_1) / acc::integer_2;

		return {(lV - acc::integer_1).to_int(), emldecodeS((lV - acc::integer_1).to_int(), rV + w)};
	}

	static eml_expression decodeEx(const acc::integer &val) {
		if (val.negative) {
			return {1, eml(val.opposite().to_int())};
		}
		if (val == acc::integer_0) {
			throw DECLARE_ONE;
		}

		return decodeEx0(val - acc::integer_1);
	}

	static acc::integer emllibEx(const int algebra_count, const eml &target) {
		if (target.type) {
			//leaf
			return acc::integer{-target.type};
		}

		const auto w = algebra_count * (algebra_count - 1) / 2;

		return pairing::pairing0(acc::integer{algebra_count + 1}, emllibS(algebra_count, target) - acc::integer{w});
	}
}

#endif //EML_RESEARCH_EMLLIB_PLUS_H
