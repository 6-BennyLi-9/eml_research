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

	emlOperator(minus) {
		return eml{ln(a), exp(b)};
	}

	//(e - 1) - e
	const auto NEGATIVE_ONE = minus(eml{nullptr, E}, E);
	//1 - ( -1 )
	const auto TWO = eml{ZERO, exp(NEGATIVE_ONE)};

	/**
	 *
	 * @param a 被根开的数
	 * @param b 被开的根数幂次(b-th root)
	 * @return the result
	 */
	emlOperator(root) {
		return exp(exp(minus(ln(ln(a)), ln(b))));
	}

	emlFunction(sqrt) {
		return root(x, TWO);
	}

	emlFunction(half) {
		return exp(minus(ln(x), ln(TWO)));
	}

	///应该是小写，为了方便还是用 I
	const auto I = exp(half(ln(NEGATIVE_ONE)));

	// a - (- b)
	emlOperator(plus) {
		return minus(a, opposite(b));
	}

	/***
	 * exp(ln a + ln b)
	 */
	emlOperator(times) {
		return emlexplict(2, emldecodeS(2, acc::integer("1006223783010386972525519400225122423494749603838855805076470783074657")), {a,b});
	}

	/***
	 * exp(ln a - ln b)
	 */
	emlOperator(divide) {
		return exp(minus(ln(a), ln(b)));
	}

	emlOperator(power) {
		return exp(exp(plus(ln(ln(a)), ln(b))));
	}

	emlFunction(square) {
		return power(x, TWO);
	}

	emlOperator(mid) {
		return half(plus(a, b));
	}

	/**
	 *
	 * @param a 底数
	 * @param b 真数
	 * @return log_a(b)
	 */
	emlOperator(log) {
		return divide(ln(b), ln(a));
	}

	const auto PI = times(opposite(I), ln(NEGATIVE_ONE));

	emlOperator(norm) {
		return sqrt(plus(square(a), square(b)));
	}

	emlFunction(sigmoid) {
		return inv(plus(ONE, exp(opposite(x))));
	}

	emlFunction(cosh) {
		return mid(exp(x), exp(opposite(x)));
	}

	emlFunction(sinh) {
		return half(minus(exp(x), exp(opposite(x))));
	}

	emlFunction(tanh) {
		return divide(minus(exp(x), exp(opposite(x))), plus(exp(x), exp(opposite(x))));
	}

	emlFunction(rot) {
		return times(x, I);
	}

	emlFunction(arot) {
		return opposite(rot(x));
	}

	emlFunction(sin) {
		return opposite(rot(sinh(rot(x))));
	}

	emlFunction(cos) {
		return cosh(rot(x));
	}

	///不要用 sin/cos， 会严重增加复杂度
	emlFunction(tan) {
		return arot(tanh(rot(x)));
	}

	emlFunction(arsinh) {
		return ln(plus(x, norm(x, ONE)));
	}

	emlFunction(arcosh0) {
		return ln(plus(x, norm(x, I)));
	}

	emlFunction(arcosh) {
		return ln(plus(x, times(plus(x, ONE), minus(x, ONE))));
	}

	emlFunction(artanh) {
		return half(ln(divide(plus(ONE, x), minus(ONE, x))));
	}

	emlFunction(arcsin) {
		return arot(arsinh(rot(x)));
	}

	emlFunction(arccos) {
		return arot(arcosh(x));
	}

	emlFunction(arctan) {
		return arot(arctan(rot(x)));
	}
#undef emlOperator
#undef emlFunction
}
#endif //EML_RESEARCH_EML_H
