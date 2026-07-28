#ifndef EML_RESEARCH_EML_H
#define EML_RESEARCH_EML_H
#include <cstdio>
#include <memory>
#include <utility>

namespace eml {
	class eml {
	public:
		std::shared_ptr<eml> leftValue, rightValue;
		int isX;

		eml(const std::shared_ptr<eml> &leftValue, const std::shared_ptr<eml> &rightValue):
			leftValue(leftValue), rightValue(rightValue), isX(false)
		{}
		eml() : eml(nullptr, nullptr) {}

		explicit eml(const bool isX) :
			leftValue(nullptr), rightValue(nullptr), isX(isX)
		{}

		eml(const eml &leftValue, const eml &rightValue):
			eml(std::make_shared<eml>(leftValue), std::make_shared<eml>(rightValue))
		{}
		eml(const std::shared_ptr<eml> &leftValue, const eml &rightValue):
			eml(leftValue, std::make_shared<eml>(rightValue))
		{}
		eml(const eml &leftValue, const std::shared_ptr<eml> &rightValue):
			eml(std::make_shared<eml>(leftValue), rightValue)
		{}

		void print() const {
			if (isX) {
				printf("x");
				return;
			}
			if (leftValue) {
				printf("e^(");
				leftValue->print();
				printf(")");
			} else {
				printf("e");
			}

			if (rightValue) {
				printf(" - ln(");
				rightValue->print();
				printf(")");
			}
		}

		void println() const {
			print();
			printf("\n");
		}

		void print0() const {
			printf("eml(");
			if (leftValue) {
				leftValue->print0();
			} else {
				printf("1");
			}
			printf(", ");
			if (rightValue) {
				rightValue->print0();
			} else {
				printf("1");
			}
			printf(")");
		}

		void println0() const {
			print0();
			printf("\n");
		}
	};

	const auto X = eml(true);
	const auto E = eml();

	inline eml ln(const eml &e) {
		// return eml(nullptr, eml(eml(nullptr, e), nullptr));
		return eml{nullptr, eml{eml{nullptr, e}, nullptr}};
	}

	inline eml exp(const eml &e) {
		return eml{e, nullptr};
	}

	const auto ZERO = eml{nullptr,eml{eml{nullptr,nullptr},nullptr}};

	/**
	 * @param a a != 0
	 * @param b
	 */
	inline eml unsafe_minus(const eml &a, const eml &b) {
		return eml{ln(a), exp(b)};
	}

	const auto NEGATIVE_ONE = unsafe_minus(eml{ln(E), E}, E);
	const auto TWO = eml{ZERO, exp(NEGATIVE_ONE)};

	/**
	 *
	 * @param a 被根开的数
	 * @param b 被开的根数幂次(b-th root)
	 * @return the result
	 */
	inline eml root(const eml &a, const eml &b) {
		return exp(exp(unsafe_minus(ln(ln(a)), ln(b))));
	}

	inline eml sqrt(const eml &e) {
		return root(e, TWO);
	}

	///应该是小写，为了方便还是用 I
	const auto I = sqrt(NEGATIVE_ONE);

	/**
	 *
	 * @param a
	 * @param b b != i
	 */
	inline eml minus(const eml &a, const eml &b) {
		return unsafe_minus(unsafe_minus(I, b), unsafe_minus(I, a));
	}

	inline eml opposite(const eml &a) {
		return minus(ZERO, a);
	}

	inline eml plus(const eml &a, const eml &b) {
		return minus(a, opposite(b));
	}

	/***
	 * @param a ab != 0
	 * @param b ab != 0
	 */
	inline eml unsafe_times(const eml &a, const eml &b) {
		return exp(plus(ln(a), ln(b)));
	}
	/***
	 * @param a ab != 0
	 * @param b ab != 0
	 */
	inline eml unsafe_divide(const eml &a, const eml &b) {
		return exp(minus(ln(a), ln(b)));
	}

	const auto HALF_I = unsafe_divide(I, TWO);
	const auto QUARTER = unsafe_divide(exp(minus(ZERO, ln(TWO))), TWO);

	inline eml half_i_t(const eml &a) {
		return plus(unsafe_times(HALF_I, plus(a, HALF_I)), QUARTER);
	}

	/***
	 * @param a a != - i / 2
	 * @param b b != - i / 2
	 */
	inline eml times(const eml &a, const eml &b) {
		return plus(minus(minus(unsafe_times(plus(a, HALF_I), plus(b, HALF_I)), half_i_t(a)), half_i_t(b)),QUARTER);
	}

	/// @param a a != - i
	inline eml divide(const eml &a, const eml &b) {
		return minus(unsafe_divide(plus(a, I), b), unsafe_divide(I, b));
	}
}
#endif //EML_RESEARCH_EML_H
