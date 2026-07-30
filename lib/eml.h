#ifndef EML_RESEARCH_EML_H
#define EML_RESEARCH_EML_H
#include <cstdio>
#include <map>
#include <memory>
#include <utility>

#include "integer.h"

namespace eml {
	static std::map<signed, const char*> algebra;
	class eml {
	public:
		std::shared_ptr<eml> lValue, rValue;
		//0 -- normal expression
		//1,2,3,... --- algebra
		signed type;


		eml(const std::shared_ptr<eml> &leftValue, const std::shared_ptr<eml> &rightValue):
			lValue(leftValue), rValue(rightValue), type(0)
		{}
		eml() : eml(nullptr, nullptr) {}

		explicit eml(const signed &type) :
			lValue(nullptr), rValue(nullptr), type(type)
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
			if (type) {
				printf("%s", algebra[type]);
				return;
			}
			if (lValue) {
				printf("e^(");
				lValue->print();
				printf(")");
			} else {
				printf("e");
			}

			if (rValue) {
				printf(" - ln(");
				rValue->print();
				printf(")");
			}
		}

		void println() const {
			print();
			printf("\n");
		}

		void print0() const {
			if (type) {
				printf("%s", algebra[type]);
				return;
			}

			printf("eml(");
			if (lValue) {
				lValue->print0();
			} else {
				printf("1");
			}
			printf(", ");
			if (rValue) {
				rValue->print0();
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

	inline acc::acc_integer emllib(const eml &);
	inline eml emldecode(const acc::acc_integer &);
	inline acc::acc_integer emllibS(const int &, const eml &);
	inline eml emldecodeS(const int &, const acc::acc_integer &);

	inline eml emlexplict(const int &, const eml &, const std::vector<eml> &);

	inline eml emlexplict(const int & p1, const acc::acc_integer & acc, const std::vector<eml> & p3) {
		return emlexplict(p1, emldecode(acc), p3);
	}
	inline eml emlexplict(const int & p1, const int & acc, const std::vector<eml> & p3) {
		return emlexplict(p1, emldecode(acc::acc_integer(acc)), p3);
	}

#define emlFunction(name) inline eml name(const eml &x)
#define emlOperator(name) inline eml name(const eml &a, const eml &b)

	const auto X = eml(1);
	const auto E = eml();

	emlFunction(ln) {
		// return eml(nullptr, eml(eml(nullptr, e), nullptr));
		return eml{nullptr, eml{eml{nullptr, x}, nullptr}};
	}

	emlFunction(exp) {
		return eml{x, nullptr};
	}

	const auto ONE = ln(E);
	// const auto ZERO = eml{nullptr,eml{eml{nullptr,nullptr},nullptr}};
	const auto ZERO = emldecodeS(0, acc::acc_integer(7));
	/// WARNING: USE IT CAREFULLY
	const auto NEGATIVE_INF = ln(ZERO);

	//使用负无穷消去第一项
	emlFunction(opposite) {
		return {NEGATIVE_INF, exp(x)};
	}

	emlFunction(inv) {
		return {{NEGATIVE_INF, x}, nullptr};
	}

	/**
	 * @param a a != 0
	 * @param b
	 */
	emlOperator(unsafe_minus) {
		return eml{ln(a), exp(b)};
	}

	//(e - 1) - e
	const auto NEGATIVE_ONE = unsafe_minus(eml{ln(E), E}, E);
	//1 - ( -1 )
	const auto TWO = eml{ZERO, exp(NEGATIVE_ONE)};

	/**
	 *
	 * @param a 被根开的数
	 * @param b 被开的根数幂次(b-th root)
	 * @return the result
	 */
	emlOperator(root) {
		return exp(exp(unsafe_minus(ln(ln(a)), ln(b))));
	}

	emlFunction(sqrt) {
		return root(x, TWO);
	}

	///应该是小写，为了方便还是用 I
	const auto I = sqrt(NEGATIVE_ONE);

	/**
	 * (i - b) - (i - a) = a - b
	 * @param a
	 * @param b b != i
	 */
	emlOperator(minus) {
		return unsafe_minus(unsafe_minus(I, b), unsafe_minus(I, a));
	}

	// emlFunction(opposite) {//T O D O : organize this
	// 	return minus(ZERO, x);
	// }

	// a - (- b)
	emlOperator(plus) {
		return minus(a, opposite(b));
	}

	/***
	 * @param a ab != 0
	 * @param b ab != 0
	 */
	emlOperator(unsafe_times) {
		return exp(plus(ln(a), ln(b)));
	}
	/***
	 * @param a a != 0
	 */
	emlOperator(unsafe_divide) {
		return exp(minus(ln(a), ln(b)));
	}

	const auto HALF_I = unsafe_divide(I, TWO);
	const auto QUARTER = unsafe_divide(exp(opposite(ln(TWO))), TWO);

	// (i/2) * (a + i/2) + 1 / 4 = ai/2
	emlFunction(half_i_t) {
		return plus(unsafe_times(HALF_I, plus(x, HALF_I)), QUARTER);
	}

	/***
	 * (a + i/2) * (b + i/2)  - ai/2 - bi/2 + 1 / 4 = ab
	 * @param a a != - i / 2
	 * @param b b != - i / 2
	 */
	emlOperator(times) {
		return plus(minus(minus(unsafe_times(plus(a, HALF_I), plus(b, HALF_I)), half_i_t(a)), half_i_t(b)),QUARTER);
	}

	/**
	 * (a + i) / b - i / b = a / b
	 * @param a a != - i
	 */
	emlOperator(divide) {
		return minus(unsafe_divide(plus(a, I), b), unsafe_divide(I, b));
	}

	emlOperator(power) {
		return exp(exp(plus(ln(ln(a)), ln(b))));
	}

#undef emlOperator
#undef emlFunction
}
#endif //EML_RESEARCH_EML_H
