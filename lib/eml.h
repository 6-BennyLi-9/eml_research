#ifndef EML_RESEARCH_EML_H
#define EML_RESEARCH_EML_H
#include <cstdio>
#include <map>
#include <memory>
#include <utility>

#include "integer.h"

namespace eml {
	static std::map<int, std::string> algebra;

	class eml {
	public:
		std::shared_ptr<eml> lValue, rValue;
		//0 -- normal expression
		//1,2,3,... --- algebra
		int type;


		eml(const std::shared_ptr<eml> &leftValue, const std::shared_ptr<eml> &rightValue) : lValue(leftValue),
			rValue(rightValue), type(0) {
		}

		eml() : eml(nullptr, nullptr) {
		}

		explicit eml(const int &type) : lValue(nullptr), rValue(nullptr), type(type) {
		}

		eml(const eml &leftValue, const eml &rightValue) : eml(std::make_shared<eml>(leftValue),
																std::make_shared<eml>(rightValue)) {
		}

		eml(const std::shared_ptr<eml> &leftValue, const eml &rightValue) : eml(
			leftValue, std::make_shared<eml>(rightValue)) {
		}

		eml(const eml &leftValue, const std::shared_ptr<eml> &rightValue) : eml(
			std::make_shared<eml>(leftValue), rightValue) {
		}

		[[nodiscard]] std::string to_string() const {
			if (type) {
				return algebra[type];
			}
			std::string str;

			if (lValue) {
				str += "e^(";
				str += lValue->to_string();
				str += ')';
			} else {
				str += 'e';
			}

			if (rValue) {
				str += " - ln(";
				str += rValue->to_string();
				str += ')';
			}

			return str;
		}

		[[nodiscard]] std::string to_string0() const {
			if (type) {
				return algebra[type];
			}
			std::string str = "eml(";

			if (lValue) {
				str += lValue->to_string0();
			} else {
				str += '1';
			}

			str += ", ";
			if (rValue) {
				str += rValue->to_string0();
			} else {
				str += '1';
			}

			str += ')';
			return str;
		}

		void print() const {
			printf("%s", to_string().c_str());
		}

		void println() const {
			print();
			printf("\n");
		}

		void print0() const {
			printf("%s", to_string0().c_str());
		}

		void println0() const {
			print0();
			printf("\n");
		}
	};

	inline acc::integer emllib(const eml &);

	inline eml emldecode(const acc::integer &);

	inline acc::integer emllibS(int, const eml &);

	inline eml emldecodeS(int, const acc::integer &);

	inline eml emlexplict(int, const eml &, const std::vector<eml> &);

	inline eml emlexplict(const int p1, const acc::integer &acc, const std::vector<eml> &p3) {
		return emlexplict(p1, emldecode(acc), p3);
	}

	inline eml emlexplict(const int p1, const int acc, const std::vector<eml> &p3) {
		return emlexplict(p1, emldecode(acc::integer(acc)), p3);
	}

#define _eml_function(name) inline eml name(const eml &x)
#define _eml_operator(name) inline eml name(const eml &a, const eml &b)
#define _operator_override(raw, op) inline eml operator op(const eml &a, const eml &b) { return raw(a, b); }

	const auto X = eml(1);
	const auto E = eml();

	_eml_function(ln) {
		// return eml(nullptr, eml(eml(nullptr, e), nullptr));
		return eml{nullptr, eml{eml{nullptr, x}, nullptr}};
	}

	_eml_function(exp) {
		return eml{x, nullptr};
	}

	const auto ONE = ln(E);
	// const auto ZERO = eml{nullptr,eml{eml{nullptr,nullptr},nullptr}};
	const auto ZERO = emldecodeS(0, acc::integer(7));
	/// WARNING: USE IT CAREFULLY
	const auto NEGATIVE_INF = ln(ZERO);

	//使用负无穷消去第一项
	_eml_function(opposite) {
		return {NEGATIVE_INF, exp(x)};
	}

	_eml_function(inv) {
		return {{NEGATIVE_INF, x}, nullptr};
	}

	_eml_operator(minus) {
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
	_eml_operator(root) {
		return exp(exp(minus(ln(ln(a)), ln(b))));
	}

	_eml_function(sqrt) {
		return root(x, TWO);
	}

	_eml_function(half) {
		return exp(minus(ln(x), ln(TWO)));
	}

	///应该是小写，为了方便还是用 I
	const auto I = exp(half(ln(NEGATIVE_ONE)));

	// a - (- b)
	_eml_operator(plus) {
		return minus(a, opposite(b));
	}

	/***
	 * exp(ln a + ln b)
	 */
	_eml_operator(times) {
		return emlexplict(
			2, emldecodeS(2, acc::integer("1006223783010386972525519400225122423494749603838855805076470783074657")),
			{a, b});
	}

	/***
	 * exp(ln a - ln b)
	 */
	_eml_operator(divide) {
		return exp(minus(ln(a), ln(b)));
	}

	_eml_operator(power) {
		return exp(exp(plus(ln(ln(a)), ln(b))));
	}

	_eml_function(square) {
		return power(x, TWO);
	}

	_eml_operator(avg) {
		return half(plus(a, b));
	}

	/**
	 *
	 * @param a 底数
	 * @param b 真数
	 * @return log_a(b)
	 */
	_eml_operator(log) {
		return divide(ln(b), ln(a));
	}

	const auto PI = times(opposite(I), ln(NEGATIVE_ONE));

	_eml_operator(hypot) {
		return sqrt(plus(square(a), square(b)));
	}

	_eml_function(sigmoid) {
		return inv(plus(ONE, exp(opposite(x))));
	}

	_eml_function(cosh) {
		return avg(exp(x), exp(opposite(x)));
	}

	_eml_function(sinh) {
		return half(minus(exp(x), exp(opposite(x))));
	}

	_eml_function(tanh) {
		return divide(minus(exp(x), exp(opposite(x))), plus(exp(x), exp(opposite(x))));
	}

	_eml_function(rot) {
		return times(x, I);
	}

	_eml_function(arot) {
		return opposite(rot(x));
	}

	_eml_function(sin) {
		return opposite(rot(sinh(rot(x))));
	}

	_eml_function(cos) {
		return cosh(rot(x));
	}

	///不要用 sin/cos， 会严重增加复杂度
	_eml_function(tan) {
		return arot(tanh(rot(x)));
	}

	_eml_function(arsinh) {
		return ln(plus(x, hypot(x, ONE)));
	}

	_eml_function(arcosh0) {
		return ln(plus(x, hypot(x, I)));
	}

	_eml_function(arcosh) {
		return ln(plus(x, times(plus(x, ONE), minus(x, ONE))));
	}

	_eml_function(artanh) {
		return half(ln(divide(plus(ONE, x), minus(ONE, x))));
	}

	_eml_function(arcsin) {
		return arot(arsinh(rot(x)));
	}

	_eml_function(arccos) {
		return arot(arcosh(x));
	}

	_eml_function(arctan) {
		return arot(arctan(rot(x)));
	}

	_operator_override(plus, +)
	_operator_override(minus, -)
	_operator_override(times, *)
	_operator_override(divide, /)
	_operator_override(power, ^)
#undef _eml_operator
#undef _eml_function
#undef _operator_override
}
#endif //EML_RESEARCH_EML_H
