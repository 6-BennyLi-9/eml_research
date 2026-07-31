#ifndef EML_RESEARCH_EML_H
#define EML_RESEARCH_EML_H
#include <cstdio>
#include <map>
#include <memory>
#include <utility>

#include "integer.h"

namespace eml {
	static std::map<signed, std::string> algebra;
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
				printf("%s", algebra[type].c_str());
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
				printf("%s", algebra[type].c_str());
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

	inline acc::integer emllib(const eml &);
	inline eml emldecode(const acc::integer &);
	inline acc::integer emllibS(int , const eml &);
	inline eml emldecodeS(int , const acc::integer &);

	inline eml emlexplict(int , const eml &, const std::vector<eml> &);

	inline eml emlexplict(const int  p1, const acc::integer & acc, const std::vector<eml> & p3) {
		return emlexplict(p1, emldecode(acc), p3);
	}
	inline eml emlexplict(const int  p1, const int  acc, const std::vector<eml> & p3) {
		return emlexplict(p1, emldecode(acc::integer(acc)), p3);
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
	const auto ZERO = emldecodeS(0, acc::integer(7));
	/// WARNING: USE IT CAREFULLY
	const auto NEGATIVE_INF = ln(ZERO);

	//使用负无穷消去第一项
	emlFunction(opposite) {
		return {NEGATIVE_INF, exp(x)};
	}

	emlFunction(inv) {
		return {{NEGATIVE_INF, x}, nullptr};
	}

	emlOperator(minus0) {
		return eml{ln(a), exp(b)};
	}

	//(e - 1) - e
	const auto NEGATIVE_ONE = minus0(eml{nullptr, E}, E);
	//1 - ( -1 )
	const auto TWO = eml{ZERO, exp(NEGATIVE_ONE)};

	/**
	 *
	 * @param a 被根开的数
	 * @param b 被开的根数幂次(b-th root)
	 * @return the result
	 */
	emlOperator(root) {
		return exp(exp(minus0(ln(ln(a)), ln(b))));
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
		return minus0(minus0(I, b), minus0(I, a));
	}

	// emlFunction(opposite) {//T O D O : organize this
	// 	return minus(ZERO, x);
	// }

	// a - (- b)
	emlOperator(plus) {
		return minus(a, opposite(b));
	}

	/***
	 * exp(ln a + ln b)
	 * @param a ab > 0
	 * @param b ab > 0
	 */
	emlOperator(times0) {
		// return exp(plus(ln(a), ln(b)));
		return emlexplict(2, emldecodeS(2, acc::integer("1006223783010386972525519400225122423494749603838855805076470783074657")), {a,b});
	}

	/***
	 * @param a a > 0
	 */
	emlOperator(divide0) {
		return exp(minus(ln(a), ln(b)));
	}

	const auto HALF_I = divide0(I, TWO);
	const auto QUARTER = divide0(exp(opposite(ln(TWO))), TWO);

	// (i/2) * (a + i/2) + 1 / 4 = ai/2
	emlFunction(half_i_t) {
		return plus(times0(HALF_I, plus(x, HALF_I)), QUARTER);
	}

	/***
	 * (a + i/2) * (b + i/2)  - ai/2 - bi/2 + 1 / 4 = ab
	 * @param a a != - i / 2
	 * @param b b != - i / 2
	 */
	emlOperator(times) {
		return plus(minus(minus(times0(plus(a, HALF_I), plus(b, HALF_I)), half_i_t(a)), half_i_t(b)),QUARTER);
	}

	/**
	 * (a + i) / b - i / b = a / b
	 * @param a a != - i
	 */
	emlOperator(divide) {
		return minus(divide0(plus(a, I), b), divide0(I, b));
	}

	emlOperator(power) {
		return exp(exp(plus(ln(ln(a)), ln(b))));
	}

#undef emlOperator
#undef emlFunction
}
#endif //EML_RESEARCH_EML_H
